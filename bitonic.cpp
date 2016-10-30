#include "bitonic.h"
int timeval_subtract(	struct timeval* result,
			struct timeval* t2, struct timeval* t1) {
	unsigned int resolution=1000000;
	long int diff = (t2->tv_usec + resolution * t2->tv_sec) -
			(t1->tv_usec + resolution * t1->tv_sec);
	result->tv_sec = diff / resolution;
	result->tv_usec = diff % resolution;
	return (diff<0);
}

bool is_sortedc(int data[], int n) {
    for (int i = 0; i < n-1; i++) {
        if (!(data[i] <= data[i+1]))
            return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 42;
    }
    int n = atoi(argv[1]);
    int size = atoi(argv[2]);

    std::vector<std::vector<int>> test;


    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        //test[i] = (int*) malloc(size * sizeof(int));
        test.push_back(std::vector<int>());
        push_random(test[i], size);
    }

    struct timeval t_start, t_end, t_diff;
    gettimeofday(&t_start, NULL);

    for (auto &vec : test) {
        bitonic_sort(vec, log2(size));
    }

    gettimeofday(&t_end, NULL);
    timeval_subtract(&t_diff, &t_end, &t_start);
    int elapsed = t_diff.tv_sec * 1e6 + t_diff.tv_usec;

    for (auto vec : test) {
        if (!is_sorted(vec)) {
            //print_vector(vec);
            printf("Fail\n");
            return 21;
        }
    }


    gettimeofday(&t_start, NULL);

    for (auto &vec : test) {
        std::sort(vec.begin(), vec.end());
    }

    gettimeofday(&t_end, NULL);
    timeval_subtract(&t_diff, &t_end, &t_start);
    int std_elapsed = t_diff.tv_sec * 1e6 + t_diff.tv_usec;



    printf("std::sort (us) per n: %i\n", std_elapsed/n);
    printf("Time (us) per n: %i\n", elapsed/n);

}
