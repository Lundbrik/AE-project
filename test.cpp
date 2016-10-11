#include "nsort.h"
#include <stdio.h>
#include <functional>
#include <string>
#include "nsort_tests.h"
#include "test_helpers.h"

#define gtest(name) s_test {name, "name"}


struct s_test {
    std::function<bool()> func;
    std::string name;
};


int main() {
    std::vector<s_test> tests =
        {   gtest(nsort_test5_1), gtest(nsort_test5_2), gtest(nsort_test6_1),
            gtest(nsort_test6_2), gtest(nsort_test7_1), gtest(nsort_test7_2),
            gtest(nsort_test8_1), gtest(nsort_test8_2), gtest(nsort_test9_1),
            gtest(nsort_test9_2), gtest(nsort_test10_1), gtest(nsort_test10_2),
            gtest(nsort_test11_1), gtest(nsort_test11_2), gtest(nsort_test12_1),
            gtest(nsort_test12_2)
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
