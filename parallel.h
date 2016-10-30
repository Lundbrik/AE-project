#include <vector>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <queue>

/**
 * Helper functions
 */
template <class T>
int qs_split(T *data, int start, int end) {
    int pivot = rand() % (end - start) + start;
    std::swap(data[start], data[pivot]); // Move pivot to start
    int i = start + 1, j = end;
    while (i < j) {
        if (data[i] > data[start]) {
            std::swap(data[i], data[j]);
            j--;
        } else {
            i++;
        }
    }
    if (data[start] > data[i]) {
        pivot = i;
    } else {
        pivot = i-1;
    }
    std::swap(data[start], data[pivot]); // Move pivot back
    return pivot;
}

template <class T>
T qs_split_sep(T *data, int start, int end,
        std::vector<T> &less, std::vector<T> &more) {
    int pivot_ind = rand() % (end - start) + start;
    T pivot = data[pivot_ind];
    int i = start;
    while (i <= end) {
        if (i != pivot) {
            if (data[i] < pivot) {
                less.push_back(data[i]);
            } else {
                more.push_back(data[i]);
            }
        }
    }
    return pivot;
}

template <class T>
bool check_small(T *data, int start, int end) {
    if (end - start < 2) { // 2 elements
        if (start >= 0
                && start < end && data[start] > data[end]) {
            std::swap(data[start], data[end]);
        }
        return true;
    }
    return false;
}

/**
 * Sequential inplace quicksort
 */
template <class T>
void qs(T *data, int start, int end) {
    if (check_small(data, start, end)) return;
    int pivot = qs_split(&data[0], start, end);
    qs(data, start, pivot-1);
    qs(data, pivot+1, end);
}

template <class T>
void qs(std::vector<T> &data) {
    qs(&data[0], 0, data.size()-1);
}

/**
 * Naive parallel quicksort
 */
template <class T>
void qs_nav(T *data, int start, int end) {
    if (check_small(data, start, end)) return;
    int pivot = qs_split(data, start, end);
    std::thread t1(qs_nav<T>, data, start, pivot-1);
    std::thread t2(qs_nav<T>, data, pivot+1, end);
    t1.join();
    t2.join();
}

template <class T>
void qs_nav(std::vector<T>& data, int start, int end) {
    qs_nav<T>(&data[0], start, end);
}

/**
 * Thoughtfull with global integer indicating threads available
 */
template <class T>
void qs_num_thr2(T* data, int start, int end, int* cores, std::mutex &mtx) {
    if (check_small(data, start, end)) return;
    int pivot = qs_split(data, start, end);
    mtx.lock();
    if (cores[0] <= 1) {
        mtx.unlock();
        qs_num_thr2(data, start, pivot-1, cores, mtx);
        qs_num_thr2(data, pivot+1, end, cores, mtx);
    } else {
        cores[0] -= 2;
        mtx.unlock();
        std::thread t1(qs_num_thr2<T>, data, start, pivot-1, cores, std::ref(mtx));
        std::thread t2(qs_num_thr2<T>, data, pivot, end, cores, std::ref(mtx));
        t1.join();
        t2.join();
        mtx.lock();
        cores[0] += 2;
        mtx.unlock();
    }
}

template <class T>
void qs_num_thr2(std::vector<T> &data, int cores) {
    std::mutex mtx;
    qs_num_thr2<T>(&data[0], 0, data.size()-1, &cores, mtx);
}

/**
 * More thoughtfull approach. Only creates as many threads as the machine has
 * cores.
 * Prone to be bad on unstable splits, and as such, idle threads
 */
template <class T>
void qs_num_thr(T *data, int start, int end, int cores) {
    if (check_small(data, start, end)) return;
    int pivot = qs_split(data, start, end);
    if (cores == 1) {
        qs(data, start, pivot-1);
        qs(data, pivot+1, end);
    } else {
        std::thread t1(qs_num_thr<T>, data, start, pivot-1, cores/2);
        std::thread t2(qs_num_thr<T>, data, pivot+1, end, cores/2);
        t1.join();
        t2.join();
    }

}

template <class T>
void qs_num_thr(std::vector<T>& data, int cores) {
    qs_num_thr<T>(&data[0], 0, data.size()-1, cores);
}

/**
 * Thread pool approach
 * I do think its bad performance is due to memory management
 * Does work ok on large input
 */
template <class T>
void qs_pool_worker(T* data, std::queue<int*> &queue, std::mutex &mutex,
        bool &bottom_reached) {
    int *index;
    while (true) {
        if (mutex.try_lock()) {
            if (queue.empty()) {
                if (bottom_reached) {
                    mutex.unlock();
                    return;
                }
                mutex.unlock();
            } else {
                index = queue.front();
                queue.pop();
                mutex.unlock();
                if (!check_small(data, index[0], index[1])) {
                    int pivot = qs_split(data, index[0], index[1]);
                    int *tmpl = (int*) malloc(2 * sizeof(int));
                    tmpl[0] = index[0];
                    tmpl[1] = pivot-1;
                    int *tmpr = (int*) malloc(2 * sizeof(int));
                    tmpr[0] = pivot+1;
                    tmpr[1] = index[1];
                    mutex.lock();
                    queue.push(tmpl);
                    queue.push(tmpr);
                    mutex.unlock();
                    free(index);
                } else {
                    mutex.lock();
                    bottom_reached = true;
                    mutex.unlock();
                    free(index);
                }
            }
        }
    }
}

template <class T>
void qs_pool(T* data, int start, int end, int cores) {
    // Initialize the queue and put the initial element
    std::queue<int*> qu;
    int* tmp = (int*) malloc(2 * sizeof(int));
    tmp[0] = start;
    tmp[1] = end;
    qu.push(tmp);

    // Declare the mutex, stopping condition and initialize the threads
    std::mutex mtx;
    bool bottom_reached = false;
    std::thread threads[cores];
    for (int i = 0; i < cores; i++) {
        threads[i] = std::thread(qs_pool_worker<T>, data, std::ref(qu),
                std::ref(mtx), std::ref(bottom_reached));
    }

    // Join the threads
    for (int i = 0; i < cores; i++) {
        threads[i].join();
    }
}

template <class T>
void qs_pool(std::vector<T> &data, int cores) {
    qs_pool(&data[0], 0, data.size()-1, cores);
}

/**
 * Mergesort
 */
template <class T>
void merge(T *data, int l1, int l2, int end) {
    std::vector<T> tmp;
    int size = l2 - l1 + 1;
    tmp.reserve(size);
    for (int i = l1; i < l2; i++) {
        tmp.push_back(data[i]);
    }
    int i = 0, j = l2, cur = l1;
    while (i+l1 < l2 && j <= end) {
        if (tmp[i] < data[j]) {
            data[cur] = tmp[i];
            i++;
        } else {
            data[cur] = data[j];
            j++;
        }
        cur++;
    }
    if (i == l2) {
        // move remaining j's. Should already be in the right place
    } else if (j > end) {
        for (; i < tmp.size(); i++) {
            data[cur] = tmp[i];
            cur++;
        }
    }
    tmp.clear();
    tmp.shrink_to_fit();
}

template <class T>
void mergesort(T* data, int start, int end) {
    if (start == end) {
        return;
    }
    int mid = ((end - start) / 2) + start;
    mergesort(data, start, mid);
    mergesort(data, mid+1, end);
    merge(data, start, mid+1, end);
}

template <class T>
void mergesort(std::vector<T> &data) {
    mergesort<T>(&data[0], 0, data.size()-1);
}

/**
 * Mergesort independant memory
 */
template <class T>
void merge_mem(std::vector<T> &left, std::vector<T> &right, std::vector<T> &res) {
    int i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            res.push_back(left[i++]);
        } else {
            res.push_back(right[j++]);
        }
    }
    if (i == left.size()) {
        for (; j < right.size(); j++) {
            res.push_back(right[j]);
        }
    } else {
        for (; i < left.size(); i++) {
            res.push_back(left[i]);
        }
    }
}

template <class T>
void mergesort_mem(std::vector<T> &data) {
    if (data.size() <= 1) {
        return;
    }
    int mid = data.size() / 2;
    std::vector<T> left;
    std::vector<T> right;
    left.reserve(mid);
    right.reserve(mid);
    left.insert(left.begin(), data.begin(), data.begin()+mid);
    right.insert(right.begin(), data.begin()+mid+1, data.end());
    mergesort_mem(left);
    mergesort_mem(right);
    data.clear();
    merge_mem(left, right, data);
    left.clear();
    left.shrink_to_fit();
    right.clear();
    right.shrink_to_fit();
}

/**
 * Parallel mergesort
 * Follows the thoughtfull parallel quicksort
 */
template <class T>
void mergesort_par(T* data, int start, int end, int cores) {
    if (start == end) {
        return;
    }
    int mid = ((end - start) / 2) + start;
    if (cores == 1) {
        mergesort(data, start, mid);
        mergesort(data, mid+1, end);
    } else {
        std::thread t1(mergesort_par<T>, data, start, mid, cores/2);
        std::thread t2(mergesort_par<T>, data, mid+1, end, cores/2);
        t1.join();
        t2.join();
    }
    merge(data, start, mid+1, end);
}

template <class T>
void mergesort_par(std::vector<T> &data, int cores) {
    mergesort_par<T>(&data[0], 0, data.size()-1, cores);
}

/**
 * Parellel mem mergesort
 */
template <class T>
void mergesort_par_mem(std::vector<T> &data, int cores) {
    if (data.size() <= 1) {
        return;
    }
    int mid = data.size() / 2;
    std::vector<T> left;
    std::vector<T> right;
    left.reserve(mid);
    right.reserve(mid);
    left.insert(left.begin(), data.begin(), data.begin()+mid);
    right.insert(right.begin(), data.begin()+mid+1, data.end());
    if (cores == 1) {
        mergesort_mem(left);
        mergesort_mem(right);
    } else {
        std::thread t1(mergesort_par_mem<T>, std::ref(left), cores/2);
        std::thread t2(mergesort_par_mem<T>, std::ref(right), cores/2);
        t1.join();
        t2.join();
    }
    data.clear();
    merge_mem(left, right, data);
    left.clear();
    left.shrink_to_fit();
    right.clear();
    right.shrink_to_fit();
}

/**
 * QuickMerge!
 */
template <class T>
void quickmerge(T* data, int start, int end, int cores) {
    int mid = ((end - start) / 2) + start;
    if (cores == 1) {
        qs(data, start, mid);
        qs(data, mid+1, end);
    } else {
        std::thread t1(quickmerge<T>, data, start, mid, cores/2);
        std::thread t2(quickmerge<T>, data, mid+1, end, cores/2);
        t1.join();
        t2.join();
    }
    merge(data, start, mid+1, end);
}

template <class T>
void quickmerge(std::vector<T> &data, int cores) {
    quickmerge<T>(&data[0], 0, data.size()-1, cores);
}

/**
 * Quickmerge mem!
 */
template <class T>
void quickmerge_mem(std::vector<T> &data, int cores) {
     if (data.size() <= 1) {
        return;
    }
    int mid = data.size() / 2;
    std::vector<T> left;
    std::vector<T> right;
    left.reserve(mid);
    right.reserve(mid);
    left.insert(left.begin(), data.begin(), data.begin()+mid);
    right.insert(right.begin(), data.begin()+mid+1, data.end());
    if (cores == 1) {
        qs(left);
        qs(right);
    } else {
        std::thread t1(mergesort_par_mem<T>, std::ref(left), cores/2);
        std::thread t2(mergesort_par_mem<T>, std::ref(right), cores/2);
        t1.join();
        t2.join();
    }
    data.clear();
    merge_mem(left, right, data);
    left.clear();
    left.shrink_to_fit();
    right.clear();
    right.shrink_to_fit();

}
