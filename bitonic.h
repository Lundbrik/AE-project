#ifndef bitonic
#define bitonic

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <algorithm>
#include <vector>
#include "test_helpers.h"

//#define cmp_swap(a, b) if (a>b) std::swap(a,b)

#define COND(c, x, y) { x = (c) ? y : x; }
#define cmp_swap(x, y) { int ax = x; COND(y < ax, x, y); \
                                      COND(y < ax, y, ax); }

//#define cmp_swap(x, y) { if (x > y) {int tmp = x; x = y; y = tmp;} }


// Assume n = 2^x for some x
// Assumes than data is of size 2^(log_n)
template <class T>
void bitonic_sort(std::vector<T> &data, int log_n) {
    //int elems = pow(2, log_n);
    int elems = 2 << (log_n - 1);
    int ff = 0;

    // Horizontal layers
    for (int layer = 1; layer <= log_n; layer++) { // Sequencial
        int log_nk = log_n - layer; // Logarithm of number of vert blocks
        int vert_blocks = std::max(2 << (log_nk - 1), 1);

        int k = layer;
        int elems_block = 2 << (k-1);

        // Vectical layers (blocks)
#pragma omp parallel for
        for (int lay = 0; lay < vert_blocks; lay++) { // Should be parallel
            int offset = lay * (elems / vert_blocks);

            // Orange (from wiki) blocks
            for (int i = 0; i < elems_block/2; i++) {
                int z = elems_block - 1;
                int a = (i + offset);
                int b = z - i + offset;
                cmp_swap(data[a], data[b]);
            }
            // Red blocks
            for (int i = 1; i < k; i++) {
                int j = 2 << ((k-i)-1); // Previously int j = pow(2, (k-i));
                ff++;
                for (int n = 0; n < elems_block / j; n++) {
                    int j2 = j / 2;
                    for (int m = 0; m < j2; m++) {
                        int z = n * j;
                        int a = z + m + offset;
                        int b = z + m + j2 + offset;
                        cmp_swap(data[a], data[b]);
                    }
                }
            }
        }
    }
}

#endif
