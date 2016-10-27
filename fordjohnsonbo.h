#ifndef FORDJOHNSONBO_H
#define FORDJOHNSONBO_H

namespace fjbo {

	#include <stdio.h>
	#include <stdlib.h> 
	#include <iostream>
	#include <vector>
	#include <math.h>
	#include <time.h>

	template<typename T, class C = std::vector<T>>
	static void printvec(C &vec, int J=1) {
		int j=J;
		for (int e : vec) {
			j--;
			if (j < 1) {
				std::cout << e << ", ";
				j=J;
			}
		}
		std::cout << "\n";
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
		
		//std::cout << "Entering with (" << i << ", " << j << ")\n";

		//std::cout << "  noe = " << numofelements;
		
		if (numofelements == 1) {
			//std::cout << "\n";
			/*if (vec[a] - vec[i] > 0) {
				return i+J;
			} else {
				return i;
			}*/
			// Branchless version
			return i + (vec[a] - vec[i] > 0)*J;
		}
		
		int ind = i + floor(numofelements/2)*J;
		//std::cout << "  ind = " << ind << "\n";
		/*if (vec[a] - vec[ind] > 0) {
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
		}*/
		
		// Branchless version
		//std::cout << ind << "\n";
		bool test = (vec[a] - vec[ind] > 0);
		ind += test*J;
		ind -= (1-test)*J;
		//std::cout << ind << " " << test << " " << J << "\n";
		bool testi = (ind < i);
		bool testj = (ind > j);
		ind = testi*i + testj*j + (1 - (testi || testj))*ind;
		int start = (1-test)*i + test*ind;
		int end = test*j + (1-test)*ind;
		//std::cout << "Recursing on (" << start << ", " << end << ", " << ind << ")\n";
		return binarySearch<T, C>(vec, start, end, J);
	}

	template<typename T, class C = std::vector<T>>
	static void shift(C &vec, int a, int i, int J) {
		printvec<int>(vec, 1);
		std::cout << "shifting(" << a << ", " << i << ")\n";
		bool test = a < i;
		i -= (J-1)*(1-test);
		for (int t = a-(J-1)*(1-test); (1-(1-test)*2)*t >= (a-(J-1))*(test) - a*(1-test); t += (1-test*2)) {
			T temp = vec[t];
			for (int j = t + (1 - (1-test)*2) ; (1 - (1-test)*2)*j <= (1 - (1-test)*2)*i ; j += (1-(1-test)*2)) {
				vec[j + (1 - test*2)] = vec[j];
			}
			vec[i] = temp;
			i += (1 - test*2);
		}
		printvec<int>(vec, 1);
		
		/*if (a < i) {
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
		}*/
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
			/*if (log2(i+1+nei) >= curlog+1 || !((i+1)*J - 1 < size/2+1)) {
				for (j=i-1; j > nei; j--) {
					bindex.push_back((2*j+1)*J - 1 - nei*J);
				}
				nei += (i - 1) - nei;
				curlog = floor(log2(i+1+nei));
			}*/
			// Branchless version
			bool test = (log2(i+1+nei) >= curlog+1 || !((i+1)*J - 1 < size/2+1));
			for (j=i-1; j > nei && test; j--) {
				bindex.push_back((2*j+1)*J - 1 - nei*J);
			}
			nei += ((i - 1) - nei)*test;
			curlog = (floor(log2(i+1+nei)))*test;
		}
		
		//std::cout << "bindex for " << J << ":\n";
		//printvec<T>(bindex);
		
		//std::cout << "\n";
		int end = size-1;
		int prev = NULL;
		for (i=0; i < bindex.size(); i++) {
			bindex[i] -= (bindex[i]>end);
			//std::cout << "Shifted " << bindex[i] << " to " << end << "\n";
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
}
#endif