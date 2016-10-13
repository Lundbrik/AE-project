#include "nsort.h"
#include <stdio.h>
#include <functional>
#include <string>
#include "nsort_tests.h"
#include "test_helpers.h"

#define gtest(name) s_test {name, #name}


struct s_test {
    std::function<bool()> func;
    std::string name;
};


int main(int argc, char* argv[]) {
    std::vector<s_test> tests =
        {   gtest(nsort_test5_1), gtest(nsort_test5_2), gtest(nsort_test6_1),
            gtest(nsort_test6_2), gtest(nsort_test7_1), gtest(nsort_test7_2),
            gtest(nsort_test8_1), gtest(nsort_test8_2), gtest(nsort_test9_1),
            gtest(nsort_test9_2), gtest(nsort_test10_1), gtest(nsort_test10_2),
            gtest(nsort_test11_1), gtest(nsort_test11_2), gtest(nsort_test12_1),
            gtest(nsort_test12_2), gtest(nsort_test16_1), gtest(nsort_test16_2)
        };

    if (argc < 2) {
        int passed = 0;
        int failed = 0;

        for (auto test : tests) {
            if ((test.func)()) {
                passed++;
            } else {
                failed++;
                std::cout << "Test failed: " << test.name << std::endl;
            }
        }

        printf("Passed: %i, failed: %i\n", passed, failed);
    } else {
        int ind = atoi(argv[1]);

        if (test_all_permutations(ind)) {
            printf("nsort_%i() passed all permutations\n", ind);
            return 0;
        } else {
            printf("nsort_%i() failed for some permutations\n", ind);
            return 1;
        }
    }
}
