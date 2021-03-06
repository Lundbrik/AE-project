#ifndef FORDJOHNSON_H
#define FORDJOHNSON_H

#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>

namespace fj {

	template<typename T, class C = std::vector<T>>
	static void printvec(C &vec, int J=1) {
		int j=J;
		for (int e : vec) {
			j--;
			if (j < 1) {
				//std::cout << e << ", ";
				j=J;
			}
		}
		//std::cout << "\n";
		return;
	}

	template<typename T, class C = std::vector<T>>
	static void swap(C &vec, int a, int b){
		T temp = vec[b];
		vec[b] = vec[a];
		vec[a] = temp;
	}

	template<typename T, class C = std::vector<T>>
	static void lcomp(C &vec, int b, long J=1) {
		int a = b-J;
		if(vec[a] - vec[b] > 0) {
			// element a > element b
			for (int i=a; b > a;b--, i--) {
				swap<T, C>(vec, i, b);
			}
		}
	}

	template<typename T, class C = std::vector<T>>
	static int binarySearch(C &vec, int i, int j, int J) {
		int numofelements = (j-i)/J+1;
		int a = vec.size()-1;

		//std::cout << "  noe = " << numofelements;
		
		if (numofelements == 1) {
			//std::cout << "\n";
			if (vec[a] - vec[i] > 0) {
				return i+J;
			} else {
				return i;
			}
		}
		
		int ind = i + floor(numofelements/2)*J;
		//std::cout << "  ind = " << ind << "\n";
		if (vec[a] - vec[ind] > 0) {
			ind += J;
			if (j < ind) {
				ind = j;
			}
			return binarySearch<T, C>(vec, ind, j, J);
		}
		else {
			ind -= J;
			if (ind < i) {
				ind = i;
			}
			return binarySearch<T, C>(vec, i, ind, J);
		}
	}

	template<typename T, class C = std::vector<T>>
	static void shift(C &vec, int a, int i, int J) {
		if (a < i) {
			for (int t = a; t>=a-(J-1); t--) {
				T temp = vec[t];
				for (int j = t+1 ; j <= i ; j++) {
					vec[j-1] = vec[j];
				}
				vec[i] = temp;
				i--;
			}
		} else {
			i -= (J-1);
			for (int t = a-(J-1); t<=a; t++) {            
				T temp = vec[t];
				for (int j = t-1 ; j >= i ; j--) {
					vec[j+1] = vec[j];
				}
				vec[i] = temp;
				i++;
			}
		}
	}

	template<typename T, class C = std::vector<T>>
	static void sort(C &vec, long J=1) {
		int size = vec.size();
		if (J > floor(size/2)) { 	// Corresponds to a size of 1,
			return; 		// hence we return
		}
		
		//std::cout << "iteration = " << J << "\n";
		int i;
		
		//Phase 1 - sort groups of two
		for (i=2*J-1		// Start from second element
			;i<size 		// As long as there are elements
			;i += 2*J) {	// Step for every second element
				lcomp<T, C>(vec, i, J);
		}
		//printvec<T, C>(vec);
		
		//Phase 2 - sort the larger elements of the groups
		sort<T, C>(vec, J*2); // Recurse on twice as big groupings
		
		//printvec<T, C>(vec);
		//Phase 3 - sort the rest
		std::vector<int> bindex;
		int j;
		int curlog = 1;
		int nei = 0;
		for (i=2; i*J - 1 < size/2+1; i++) {
			if (log2(i+1+nei) >= curlog+1 || !((i+1)*J - 1 < size/2+1)) {
				for (j=i-1; j > nei; j--) {
					bindex.push_back((2*j+1)*J - 1 - nei*J);
				}
				nei += (i - 1) - nei;
				curlog = floor(log2(i+1+nei));
			}
		}
		
		//std::cout << "bindex for " << J << ":\n";
		//printvec<T>(bindex);
		
		//std::cout << "\n";
		int end = size-1;
		int prev = NULL;
		for (i=0; i < bindex.size(); i++) {
			//std::cout << "Shifted " << bindex[i] << " to " << end << "\n";
			bindex[i] -= (bindex[i]>end);
			shift<T,C>(vec, bindex[i], end, J);
			end -= J;
			for (j=i-1 ; j>=0 && bindex[i] < bindex[j]; j--) {
				bindex[j] -= J;
			}
		}
		
		//printvec<T>(vec);
		
		end = size-1;
		nei = 0;
		for (int e : bindex) {
			//std::cout << "e = " << e << ", nei = " << nei << ", J = " << 1 << "\n";
			int t = (e-J)+nei*J;
			int ind = binarySearch<T, C>(vec, (J-1), t, J);
			//std::cout << "ind = " << ind << " t = " << t << "\n";
			shift<T, C>(vec, end, ind, J);
			nei++;
			//printvec<T>(vec);
		}
		
		//printvec<T>(vec, J);
		return;
	}

	/*int main (int argc, char *argv[])
	{
		const int HIGHNUM = 50;
		int i;
		std::vector<int> vec;
		
		if (argc < 2) {
			std::cout << "Usage: FordJohnson int";
			return 0;
		}
		int numofelements = atoi(argv[1]);
		srand(time(NULL));
		for (i = 0; i < numofelements; i++) {
			vec.push_back(rand() % HIGHNUM + 1);
		}
		std::cout << "Initial vector\n";
		printvec<int>(vec);
		
		sort<int>(vec);
		std::cout << "Finished sorting\n";
		printvec<int>(vec);
		return 0;
	}*/
}
#endif