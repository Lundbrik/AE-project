#include "nsort.h"
#include <stdio.h>
#include <functional>
#include <string>
#include <algorithm>
#include "test_helpers.h"
#include <chrono>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 42;
    } else {
        int inputs = atoi(argv[1]);
        int runs = atoi(argv[2]);
        std::vector<std::vector<int>> inputs1;

        for (int i = 0; i < runs; i++) {
            std::vector<int> tmp;
            push_random(tmp, inputs);
            inputs1.push_back(tmp);
        }
        auto inputs2 = inputs1;

        auto st1 = std::chrono::steady_clock::now();

        for (auto vec : inputs1) {
            std::sort(vec.begin(), vec.end());
        }
        auto st2 = std::chrono::steady_clock::now();

        {
            using namespace std::chrono;
            nanoseconds std_time = duration_cast<nanoseconds>(st2 - st1);

            std::cout << (std_time.count() / runs) << std::endl;
        }

        bool found = false;
        std::chrono::steady_clock::time_point nt1, nt2;
        for (auto nsort : nsorts) {
            if (nsort.inputs == inputs) {
                nt1 = std::chrono::steady_clock::now();
                for (auto vec : inputs2) {
                    nsort.func(vec);
                }
                nt2 = std::chrono::steady_clock::now();
                found = true;
                break;
            }
        }
        if (!found) {
            printf("nsort%i() not available\n", inputs);
        } else {
            using namespace std::chrono;
            nanoseconds nsort_time = duration_cast<nanoseconds>(nt2 - nt1);

            std::cout << (nsort_time.count() / runs) << std::endl;
        }

    }
}
