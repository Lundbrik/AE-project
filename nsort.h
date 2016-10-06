#include <vector>

#define comp_swap(a, b) if (a>b) std::swap(a,b)


template <class T>
void nsort_8(std::vector<T> &data) {
    // Layer 1
    comp_swap(data[0], data[1]);
    comp_swap(data[2], data[3]);
    comp_swap(data[4], data[5]);
    comp_swap(data[6], data[7]);

    // Layer 2
    comp_swap(data[0], data[2]);
    comp_swap(data[4], data[6]);

    // Layer 3
    comp_swap(data[1], data[3]);

    // Layer 4
    comp_swap(data[0], data[4]);
    comp_swap(data[5], data[7]);

    // Layer 5
    comp_swap(data[3], data[7]);

    // Layer 6
    comp_swap(data[1], data[5]);

    // Layer 7
    comp_swap(data[3], data[5]);

    // Layer 8
    comp_swap(data[2], data[6]);

    // Layer 9
    comp_swap(data[2], data[4]);

    // Layer 10
    comp_swap(data[1], data[2]);
    comp_swap(data[3], data[6]);

    // Layer 11
    comp_swap(data[2], data[4]);
    comp_swap(data[5], data[6]);

    // Layer 12
    comp_swap(data[3], data[4]);
}



template <class T>
void nsort_7(std::vector<T> &data) {
    // Layer 1
    comp_swap(data[0], data[1]);
    comp_swap(data[2], data[3]);
    comp_swap(data[4], data[5]);

    // Layer 2
    comp_swap(data[0], data[6]);

    // Layer 3
    comp_swap(data[2], data[4]);

    // Layer 4
    comp_swap(data[0], data[2]);

    // Layer 5
    comp_swap(data[1], data[3]);
    comp_swap(data[5], data[6]);

    // Layer 6
    comp_swap(data[1], data[4]);

    // Layer 7
    comp_swap(data[2], data[5]);

    // Layer 8
    comp_swap(data[1], data[2]);
    comp_swap(data[4], data[5]);

    // Layer 9
    comp_swap(data[2], data[4]);

    // Layer 10
    comp_swap(data[3], data[6]);

    // Layer 11
    comp_swap(data[3], data[5]);

    // Layer 12
    comp_swap(data[3], data[4]);
}


template <class T>
void nsort_6(std::vector<T> &data) {
    // Layer 1
    comp_swap(data[0], data[1]);
    comp_swap(data[2], data[3]);
    comp_swap(data[4], data[5]);

    // Layer 2
    comp_swap(data[0], data[2]);

    // Layer 3
    comp_swap(data[0], data[4]);

    // Layer 4
    comp_swap(data[1], data[3]);

    // Layer 5
    comp_swap(data[1], data[5]);

    // Layer 6
    comp_swap(data[2], data[4]);

    // Layer 7
    comp_swap(data[1], data[2]);
    comp_swap(data[3], data[5]);

    // Layer 8
    comp_swap(data[3], data[4]);

    // Layer 9
    comp_swap(data[2], data[3]);
}

template <class T>
void nsort_5(std::vector<T> &data) {
    // Layer 1
    comp_swap(data[0], data[1]);
    comp_swap(data[2], data[3]);

    // Layer 2
    comp_swap(data[0], data[2]);

    // Layer 3
    comp_swap(data[1], data[3]);

    // Layer 4
    comp_swap(data[1], data[2]);
    comp_swap(data[3], data[4]);

    // Layer 5
    comp_swap(data[1], data[3]);

    // Layer 6
    comp_swap(data[0], data[1]);
    comp_swap(data[2], data[4]);
}
