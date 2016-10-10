#include "nsort.h"
#include <stdio.h>
#include <functional>
#include <string>
#include "test_helpers.h"

#define gtest(name) s_test {name, "name"}


struct s_test {
    std::function<bool()> func;
    std::string name;
};


bool test5_1() {
    std::vector<int> data    = {5, -1, 3, 10, 2};
    std::vector<int> sorted  = {-1, 2, 3, 5, 10};

    nsort_5(data);

    return (is_sorted(data) && is_equal(data, sorted));
}
bool test5_2() {
    std::vector<int> data    = {5, 4, 3, 2, 1};
    std::vector<int> sorted  = {1, 2, 3, 4, 5};

    nsort_5(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool test6_1() {
    std::vector<int> data    = {0, 5, -1, 3, 10, 2};
    std::vector<int> sorted  = {-1, 0, 2, 3, 5, 10};

    nsort_6(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool test6_2() {
    std::vector<int> data    = {5, 4, 3, 2, 1, 0};
    std::vector<int> sorted  = {0, 1, 2, 3, 4, 5};

    nsort_6(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool test7_1() {
    std::vector<int> data    = {0, 5, -1, 2 ,3, 10, 2};
    std::vector<int> sorted  = {-1, 0, 2, 2 ,3, 5, 10};

    nsort_7(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool test7_2() {
    std::vector<int> data    = {11, 5, -1, 2 ,3, 10, 2};
    std::vector<int> sorted  = {-1, 2, 2 ,3, 5, 10, 11};

    nsort_7(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool test8_1() {
    std::vector<int> data    = {11, 5, -1, 2 ,3, 10, 2, -5};
    std::vector<int> sorted  = {-5, -1, 2, 2 ,3, 5, 10, 11};

    nsort_8(data);

    return (is_sorted(data) && is_equal(data, sorted));
}
bool test8_2() {
    std::vector<int> data    = {9, 8, 7, 6, 5, 4, 3, 2};
    std::vector<int> sorted  = {2, 3, 4, 5, 6, 7, 8, 9};

    nsort_8(data);

    return (is_sorted(data) && is_equal(data, sorted));
}
bool test9_2() {
    std::vector<int> data    = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> sorted  = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    nsort_9(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

bool test9_3() {
    std::vector<int> data;
    push_random(data, 9);

    nsort_9(data);

    return is_sorted(data);
}

int main() {
    std::vector<s_test> tests =
        {   gtest(test5_1), gtest(test5_2), gtest(test6_1), gtest(test6_2),
            gtest(test7_1), gtest(test7_2), gtest(test8_1), gtest(test8_2),
            gtest(test9_2), gtest(test9_3)
        };

    int passed = 0;
    int failed = 0;

    for (auto test : tests) {
        if ((test.func)()) {
            passed++;
        } else {
            failed++;
            printf("Test failed: %s\n", test.name);
        }
    }

    printf("Passed: %i, failed: %i\n", passed, failed);
}
