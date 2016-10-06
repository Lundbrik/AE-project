#include "nsort.h"
#include <stdio.h>
#include "test_helpers.h"

bool test7_1() {
    std::vector<int> data    = {0, 5, -1, 2 ,3, 10, 2};
    std::vector<int> sorted  = {-1, 0, 2, 2 ,3, 5, 10};

    nsort_7(data);

    return (is_sorted(data) && is_equal(data, sorted));
}

int main() {
    printf("Test nsort7_1(): %s\n", test7_1() ? "Passed" : "Failed");
}
