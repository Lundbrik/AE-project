#include <stdlib.h>
#include <iostream>
#include <time.h>

#ifndef test_helpers
#define test_helpers
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
