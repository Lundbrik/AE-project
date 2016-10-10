#include "test_helpers.h"

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

    for (int i = 0; i < 10; i++) {
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

    for (int i = 0; i < 10; i++) {
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

    for (int i = 0; i < 10; i++) {
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

