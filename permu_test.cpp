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


int main(int argc, char *argv[]) {
    if (argc < 2)
        return 42;

    int ind = atoi(argv[1]);

    if (test_all_permutations(ind)) {
        printf("nsort_%i() passed all permutations\n", ind);
        return 0;
    } else {
        printf("nsort_%i() failed for some permutations\n", ind);
        return 1;
    }
}
