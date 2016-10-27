#ifndef test_helpers
#define test_helpers

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <functional>
#include "nsort.h"

// Semi easy way to choose from the available nsort functions.
#define NTYPE <int>
#define gnsort(inputs) s_nsort {nsort_ ## inputs NTYPE , inputs}

struct s_nsort {
    std::function<void(std::vector<int>&)> func;
    int inputs;
};

s_nsort nsorts[] = { gnsort(2), gnsort(3), gnsort(4), gnsort(5), gnsort(6),
    gnsort(7), gnsort(8), gnsort(9), gnsort(10), gnsort(11), gnsort(12),
    gnsort(13), gnsort(14), gnsort(15), gnsort(16) };


template <class T>
bool is_sorted(std::vector<T> &data) {
    for (int i = 0; i < data.size()-1; i++) {
        if (data[i] > data[i+1])
            return false;
    }
    return true;
}

template <class T>
bool is_equal(std::vector<T> &a, std::vector<T> &b) {
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

void push_random(std::vector<int> &data, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        data.push_back(rand() % 10000);
    }
}

void print_vector(std::vector<int> &data) {
    std::cout << "[";
    for (int x : data) {
        std::cout << x << ", ";
    }
    std::cout << "]" << std::endl;
}
#endif
