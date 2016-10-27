#include "test_helpers.h"
#define RAND_TESTS 100


bool nsort_test5_1() {
    std::vector<int> data    = {5, -1, 3, 10, 2};
    std::vector<int> sorted  = {-1, 2, 3, 5, 10};

    nsort_5(data);

    return (is_sorted(data) && is_equal(data, sorted));
}
bool nsort_test5_2() {
    std::vector<int> data    = {5, 4, 3, 2, 1};
    std::vector<int> sorted  = {1, 2, 3, 4, 5};

    nsort_5(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool nsort_test6_1() {
    std::vector<int> data    = {0, 5, -1, 3, 10, 2};
    std::vector<int> sorted  = {-1, 0, 2, 3, 5, 10};

    nsort_6(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool nsort_test6_2() {
    std::vector<int> data    = {5, 4, 3, 2, 1, 0};
    std::vector<int> sorted  = {0, 1, 2, 3, 4, 5};

    nsort_6(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool nsort_test7_1() {
    std::vector<int> data    = {0, 5, -1, 2 ,3, 10, 2};
    std::vector<int> sorted  = {-1, 0, 2, 2 ,3, 5, 10};

    nsort_7(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool nsort_test7_2() {
    std::vector<int> data    = {11, 5, -1, 2 ,3, 10, 2};
    std::vector<int> sorted  = {-1, 2, 2 ,3, 5, 10, 11};

    nsort_7(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool nsort_test8_1() {
    std::vector<int> data    = {11, 5, -1, 2 ,3, 10, 2, -5};
    std::vector<int> sorted  = {-5, -1, 2, 2 ,3, 5, 10, 11};

    nsort_8(data);

    return (is_sorted(data) && is_equal(data, sorted));
}
bool nsort_test8_2() {
    std::vector<int> data    = {9, 8, 7, 6, 5, 4, 3, 2};
    std::vector<int> sorted  = {2, 3, 4, 5, 6, 7, 8, 9};

    nsort_8(data);

    return (is_sorted(data) && is_equal(data, sorted));
}
bool nsort_test9_1() {
    std::vector<int> data    = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> sorted  = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    nsort_9(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool nsort_test9_2() {

    for (int i = 0; i < RAND_TESTS; i++) {
        std::vector<int> data;
        push_random(data, 9);

        auto orig = data;

        nsort_9(data);
        if (!is_sorted(data)) {
            printf("nsort9 failed on:\n");
            print_vector(orig);
            print_vector(data);
            return false;
        }
    }

    return true;
}

bool nsort_test10_1() {
    std::vector<int> data    = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> sorted  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    nsort_10(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool nsort_test10_2() {

    for (int i = 0; i < RAND_TESTS; i++) {
        std::vector<int> data;
        push_random(data, 10);

        auto orig = data;

        nsort_10(data);
        if (!is_sorted(data)) {
            printf("nsort10 failed on:\n");
            print_vector(orig);
            print_vector(data);
            return false;
        }
    }

    return true;
}

bool nsort_test11_1() {
    std::vector<int> data    = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> sorted  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    nsort_11(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool nsort_test11_2() {

    for (int i = 0; i < RAND_TESTS; i++) {
        std::vector<int> data;
        push_random(data, 11);

        auto orig = data;

        nsort_11(data);
        if (!is_sorted(data)) {
            printf("nsort11 failed on:\n");
            print_vector(orig);
            print_vector(data);
            return false;
        }
    }

    return true;
}

bool nsort_test12_1() {
    std::vector<int> data    = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> sorted  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    nsort_12(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool nsort_test12_2() {

    for (int i = 0; i < RAND_TESTS; i++) {
        std::vector<int> data;
        push_random(data, 12);

        auto orig = data;

        nsort_12(data);
        if (!is_sorted(data)) {
            printf("nsort12 failed on:\n");
            print_vector(orig);
            print_vector(data);
            return false;
        }
    }

    return true;
}

bool nsort_test16_1() {
    std::vector<int> data    = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> sorted  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    nsort_16(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool nsort_test16_2() {

    for (int i = 0; i < RAND_TESTS; i++) {
        std::vector<int> data;
        push_random(data, 16);

        auto orig = data;

        nsort_16(data);
        if (!is_sorted(data)) {
            printf("nsort16 failed on:\n");
            print_vector(orig);
            print_vector(data);
            return false;
        }
    }

    return true;
}


bool complete_test(std::vector<int> &data, int len, int n,
        std::function<void(std::vector<int>&)> s)
{
    if (n < len) {
        //printf("%i, %i\n", len, n);
        for (int i = 0; i < (len - n); i++) {
            data[n] = n + i * len;
            if (!complete_test(data, len, n+1, s)) {
                return false;
            }
        }
        return true;
    } else {
        auto copy = data;
        s(copy);
        return is_sorted(copy);
    }
}

bool test_all_permutations(int inputs) {

    for (s_nsort nsort : nsorts) {
        if (inputs == nsort.inputs) {
            bool res[inputs];
#pragma omp parallel for
            for (int i = 0; i < inputs; i++) {
                std::vector<int> data;
                push_random(data, inputs);
                data[0] = i * inputs;
                res[i] = complete_test(data, inputs, 1, nsort.func);
            }
            for (int i = 0; i < inputs; i++) {
                if (!res[i])
                    return false;
            }
            return true;
        }
    }
    std::cout << "Sorting network of size: " << inputs << " not found" << std::endl;
    return false;
}