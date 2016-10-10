#include "nsort.h"
#include <stdio.h>
#include "test_helpers.h"


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

int main() {
    printf("Test nsort5_1(): %s\n", test5_1() ? "Passed" : "Failed");
    printf("Test nsort5_2(): %s\n", test5_2() ? "Passed" : "Failed");

    printf("Test nsort6_1(): %s\n", test6_1() ? "Passed" : "Failed");

    printf("Test nsort7_1(): %s\n", test7_1() ? "Passed" : "Failed");
    printf("Test nsort7_2(): %s\n", test7_2() ? "Passed" : "Failed");

    printf("Test nsort8_1(): %s\n", test8_1() ? "Passed" : "Failed");
    printf("Test nsort8_2(): %s\n", test8_2() ? "Passed" : "Failed");

    printf("Test nsort9_2(): %s\n", test9_2() ? "Passed" : "Failed");
}
