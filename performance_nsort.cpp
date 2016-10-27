#include "nsort.h"
#include <stdio.h>
#include <functional>
#include <string>
#include <algorithm>
#include "test_helpers.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include "fordjohnson.h"
#include "fordjohnsonbo.h"
#include "small.cpp"

using namespace std::chrono;

void stdsort(std::vector<int> &vec) {
	std::sort(vec.begin(), vec.end());
}

void fjsort(std::vector<int> &vec) {
	fj::sort<int>(vec, 1);
}

void fjbosort(std::vector<int> &vec) {
	fjbo::sort<int>(vec, 1);
}

void nsort(std::vector<int> &vec) {
	for (auto nsort : nsorts) {
		if (nsort.inputs == vec.size()) {
			nsort.func(vec);
			return;
		}
	}
}

#define RUNS 100
std::vector<int> sizes = {2, 4, 6, 8, 10, 12, 14, 16};
std::vector<std::string> sorternames = {"std::sort", "Sorting networks", "ford johnson", "fj branch optimized"};
std::vector<void (*)(std::vector<int>&)> sorters;

void initsorters() {
	sorters.push_back(stdsort);
	sorters.push_back(nsort);
	sorters.push_back(fjsort);
	sorters.push_back(fjbosort);
}

void expoutput() {
	initsorters();
	std::ofstream myfile;
	myfile.open("smalltable.tex");
	std::vector<std::vector<int>> inputs1, inputs2;
	time_point<steady_clock> start, end;
	nanoseconds time;
	int i,j;
	myfile << "\\begin{tabular}{|l|";
	for (std::string n : sorternames) {
		myfile << "l|";
	}
	myfile << "}\\hline\n\t";
	myfile << "size";
	for (i=0; i < sorternames.size(); i++) {
		myfile << "&" << sorternames[i];
	}
	myfile << "\\hline\\\\\n";
	for (int s : sizes) {
	    inputs1 = {};
	    for (i = 0; i < RUNS; i++) {
                std::vector<int> tmp;
                push_random(tmp, s);
                inputs1.push_back(tmp);
            }
            inputs2 = inputs1;
            myfile << "\t" << s;
            for (void (*f)(std::vector<int>&) : sorters) {
                start = steady_clock::now();
                for (auto vec : inputs1) {
                        f(vec);
                }
                end = steady_clock::now();
                time = duration_cast<nanoseconds>(end - start);
                inputs1 = inputs2;
                myfile << "&" << (time.count()/RUNS);
            }
            myfile << "\\hline\\\\\n";
	}
	myfile << "\\end{tabular}";
	myfile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        expoutput();
        return 42;
    } else {
        nanoseconds fs_time;
        nanoseconds std_time;
        nanoseconds nsort_time;
        nanoseconds fj_time;
        nanoseconds fjbo_time;
        int inputs = atoi(argv[1]);
        int runs = atoi(argv[2]);
        std::vector<std::vector<int>> inputs1;

        for (int i = 0; i < runs; i++) {
            std::vector<int> tmp;
            push_random(tmp, inputs);
            inputs1.push_back(tmp);
        }
        auto inputs2 = inputs1;
        auto inputs3 = inputs1;
        auto inputs4 = inputs1;
        auto inputs5 = inputs1;
        auto inputs6 = inputs1;

        bool fs = false;
        if (inputs > 3 && inputs < 9) {
            std::function<void(std::vector<int>&)> fsort;
            switch(inputs) {
                case 8:
                    fsort = fsort_8<int>;
                    break;
                case 7:
                    fsort = fsort_7<int>;
                    break;
                case 6:
                    fsort = fsort_6<int>;
                    break;
                case 5:
                    fsort = fsort_5<int>;
                    break;
                case 4:
                    fsort = fsort_4<int>;
                    break;
            }
            auto fst1 = steady_clock::now();

            for (auto &vec : inputs5) {
                fsort(vec);
            }
            auto fst2 = steady_clock::now();
            fs_time = duration_cast<nanoseconds>(fst2 - fst1);
            fs = true;

            for (auto vec : inputs5) {
                if (!is_sorted(vec)) {
                    std::cout << "fsort() failed to sort" << std::endl;
                    print_vector(inputs6[0]);
                    print_vector(vec);
                    break;
                }
            }
        }


        auto st1 = steady_clock::now();

        for (auto &vec : inputs1) {
            std::sort(vec.begin(), vec.end());
        }
        auto st2 = steady_clock::now();

        {
            std_time = duration_cast<nanoseconds>(st2 - st1);

            //std::cout << (std_time.count() / runs) << std::endl;
        }

        bool found = false;
        steady_clock::time_point nt1, nt2;
        for (auto nsort : nsorts) {
            if (nsort.inputs == inputs) {
                nt1 = steady_clock::now();
                for (auto &vec : inputs2) {
                    nsort.func(vec);
                }
                nt2 = steady_clock::now();
                found = true;

                for (auto vec : inputs2) {
                    if (!is_sorted(vec)) {
                        std::cout << "nsort() failed to sort" << std::endl;
                    }
                }
                break;
            }
        }
        if (!found) {
            printf("nsort%i() not available\n", inputs);
        } else {
            nsort_time = duration_cast<nanoseconds>(nt2 - nt1);

            //std::cout << (nsort_time.count() / runs) << std::endl;
        }


        // Ford Johnson
        auto ft1 = steady_clock::now();

        for (auto &vec : inputs3) {
            fj::sort<int>(vec, 1);
        }
        auto ft2 = steady_clock::now();
        for (auto vec : inputs3) {
            if (!is_sorted(vec)) {
                std::cout << "fj::sort() failed to sort" << std::endl;
                print_vector(vec);
                break;
            }
        }

        {
            fj_time = duration_cast<nanoseconds>(ft2 - ft1);

            //std::cout << (fj_time.count() / runs) << std::endl;
        }

        // BO Ford Johnson
        auto fbot1 = steady_clock::now();

        for (auto vec : inputs4) {
            fjbo::sort<int>(vec);
        }
        auto fbot2 = steady_clock::now();

        {
            fjbo_time = duration_cast<nanoseconds>(fbot2 - fbot1);

            //std::cout << (fj_time.count() / runs) << std::endl;
        }

        // Writing out
        //std::cout << std::endl << std::endl << std::endl;
        std::cout << "std sort took " << (std_time.count() / runs) << std::endl;
        std::cout << "nsort took " << (nsort_time.count() / runs) << std::endl;
        if (fs) std::cout << "fsort took " << (fs_time.count() / runs) << std::endl;
        std::cout << "fj sort took " << (fj_time.count() / runs) << std::endl;
        std::cout << "fjbo sort took " << (fjbo_time.count() / runs) << std::endl;
    }
}
