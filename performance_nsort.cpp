#include "nsort.h"
#include <stdio.h>
#include <functional>
#include <string>
#include <algorithm>
#include "test_helpers.h"
#include <chrono>
#include "fordjohnson.h"
#include <iostream>
#include <fstream>

using namespace std::chrono;

void stdsort(std::vector<int> &vec) {
	std::sort(vec.begin(), vec.end());
}

void fjsort(std::vector<int> &vec) {
	fj::sort<int>(vec, 1);
}

#define RUNS 10
std::vector<int> sizes = {2, 4, 6, 8, 10, 12, 14, 16};
std::vector<std::string> sorternames = {"std::sort", "ford johnson"};
std::vector<void (*)(std::vector<int>&)> sorters;

void initsorters() {
	sorters.push_back(stdsort);
	sorters.push_back(fjsort);
}

void expoutput() {
	initsorters();
	std::ofstream myfile;
	myfile.open("table.tex");
	std::vector<std::vector<int>> inputs1, inputs2;
	time_point<steady_clock> start, end;
	nanoseconds time;
	int i,j;
	myfile << "\\begin{tabular}{|l|";
	for (std::string n : sorternames) {
		myfile << "l|";
	}
	myfile << "}\n\t";
	myfile << "size";
	for (i=0; i < sorternames.size(); i++) {
		myfile << "&" << sorternames[i];
	}
	myfile << "\\\\\n\t";
	for (int s : sizes) {
		inputs1 = {};
		for (i = 0; i < RUNS; i++) {
            std::vector<int> tmp;
            push_random(tmp, s);
            inputs1.push_back(tmp);
        }
		inputs2 = inputs1;
		myfile << s;
		for (void (*f)(std::vector<int>&) : sorters) {
			start = steady_clock::now();
			for (auto vec : inputs1) {
				f(vec);
			}
			end = steady_clock::now();
			time = duration_cast<nanoseconds>(end - start);
			myfile << "&" << (time.count()/RUNS);
		}
		myfile << "\\\\\n\t";
	}
	myfile << "\\end{tabular}";
	myfile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
		expoutput();
        return 42;
    } else {
		nanoseconds std_time;
		nanoseconds nsort_time;
		nanoseconds fj_time;
        int inputs = atoi(argv[1]);
        int runs = atoi(argv[2]);
        std::vector<std::vector<int>> inputs1;

        for (int i = 0; i < runs; i++) {
            std::vector<int> tmp;
            push_random(tmp, inputs);
            inputs1.push_back(tmp);
        }
        auto inputs2 = inputs1;
		auto inputs3 = inputs2;

        auto st1 = steady_clock::now();

        for (auto vec : inputs1) {
            std::sort(vec.begin(), vec.end());
        }
        auto st2 = steady_clock::now();

        {
            std_time = duration_cast<nanoseconds>(st2 - st1);

            std::cout << (std_time.count() / runs) << std::endl;
        }

        bool found = false;
        steady_clock::time_point nt1, nt2;
        for (auto nsort : nsorts) {
            if (nsort.inputs == inputs) {
                nt1 = steady_clock::now();
                for (auto vec : inputs2) {
                    nsort.func(vec);
                }
                nt2 = steady_clock::now();
                found = true;
                break;
            }
        }
        if (!found) {
            printf("nsort%i() not available\n", inputs);
        } else {
            nsort_time = duration_cast<nanoseconds>(nt2 - nt1);

            std::cout << (nsort_time.count() / runs) << std::endl;
        }
		
		
		// Ford Johnson
		auto ft1 = steady_clock::now();

        for (auto vec : inputs3) {
            fj::sort<int>(vec);
        }
        auto ft2 = steady_clock::now();

        {
            fj_time = duration_cast<nanoseconds>(ft2 - ft1);

            std::cout << (fj_time.count() / runs) << std::endl;
        }
		
		// Writing out
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "std sort took " << (std_time.count() / runs) << std::endl;
		std::cout << "nsort took " << (nsort_time.count() / runs) << std::endl;
		std::cout << "fj sort took " << (fj_time.count() / runs) << std::endl;
    }
}
