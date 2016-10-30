#include <vector>
#include <iostream>
#include <chrono>
#include <assert.h>
#include <algorithm>
#include <functional>
#include <string>
#include "parallel.h"
#include "test_helpers.h"

template <class T>
void validate(std::vector<T>& data) {
    std::cout << (is_sorted(data) ? "VALID" : "NOT VALID") << std::endl;
}

int main() {
    // Initialize test data
    std::vector<int> a = { 2, 3, 7, 6, 1 };
    int num_cores = std::thread::hardware_concurrency();
    int num_elements = 10000000;
    int num_tests = 5;
    unsigned long total = 0L;

    // Test known input
    qs(a);
    assert(is_sorted(a));

    std::cout << "Testing " << num_tests << " iterations on " << num_elements
        << " elements" << std::endl;

    // Test random input on sequential
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        qs(input);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average sequential"
        << std::endl;

    // Test random input on std sort
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(input.begin(), input.end());
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average std"
        << std::endl;

    /*
    // Test random input on naive parallel implementation
    total = 0L;
    for (int i = 0; i < num_tests; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        qs_nav_sep(copy1, 0, copy1.size()-1);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average naive parallel"
        << std::endl;
    assert(is_sorted(copy1));
    */

    // Test random input on pooled parallel
    total = 0L;
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        qs_pool(input, num_cores);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average pooled parallel"
        << std::endl;

    // Test random input on thoughtfull parallel implementation
    total = 0L;
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        qs_num_thr(input, num_cores);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average thoughtful parallel"
        << std::endl;

    // Test random input on thoughtfull parallel implementation 2
    total = 0L;
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        qs_num_thr2(input, num_cores);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average thoughtful parallel2"
        << std::endl;

    // Test random input on mergesort
    total = 0L;
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        mergesort(input);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average mergesort"
        << std::endl;

    // Test random input on mergesort mem
    total = 0L;
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        mergesort_mem(input);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average mergesort mem"
        << std::endl;

    // Test random input on thoughtful parallel mergesort
    total = 0L;
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        mergesort_par(input, num_cores);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements <<
        " ns : Average thoughtful parallel mergesort"
        << std::endl;

    // Test random input on parallel mergesort mem
    total = 0L;
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        mergesort_par_mem(input, num_cores);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average parallel mergesort mem"
        << std::endl;

    // Test random input on parallel quickmerge
    total = 0L;
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        quickmerge(input, num_cores);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average quickmerge"
        << std::endl;

    // Test random input on parallel quickmerge
    total = 0L;
    for (int i = 0; i < num_tests; i++) {
        std::vector<int> input;
        input.reserve(num_elements);
        push_random(input, num_elements);
        auto start = std::chrono::high_resolution_clock::now();
        quickmerge_mem(input, num_cores);
        auto end = std::chrono::high_resolution_clock::now();
        total +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end-start)
            .count();
        assert(is_sorted(input));
        input.clear();
        input.shrink_to_fit();
    }
    std::cout << (total / num_tests) / num_elements << " ns : Average quickmerge mem"
        << std::endl;

}
