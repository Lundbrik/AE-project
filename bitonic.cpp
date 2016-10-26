#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <algorithm>
#include <vector>
#include "test_helpers.h"

//#define cmp_swap(a, b) printf("%i, %i\n", a, b); if (data[a]>data[b]) std::swap(data[a],data[b])
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

int timeval_subtract(	struct timeval* result,
			struct timeval* t2, struct timeval* t1) {
	unsigned int resolution=1000000;
	long int diff = (t2->tv_usec + resolution * t2->tv_sec) -
			(t1->tv_usec + resolution * t1->tv_sec);
	result->tv_sec = diff / resolution;
	result->tv_usec = diff % resolution;
	return (diff<0);
}

bool is_sortedc(int data[], int n) {
    for (int i = 0; i < n-1; i++) {
        if (!(data[i] <= data[i+1]))
            return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 42;
    }
    int n = atoi(argv[1]);
    int size = atoi(argv[2]);

    std::vector<int> test[n];


    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        //test[i] = (int*) malloc(size * sizeof(int));
        test[i] = std::vector<int>();
        push_random(test[i], size);
    }

    struct timeval t_start, t_end, t_diff;
    gettimeofday(&t_start, NULL);

    for (int i = 0; i < n; i++) {
        bitonic_sort(test[i], log2(size));
    }

    gettimeofday(&t_end, NULL);
    timeval_subtract(&t_diff, &t_end, &t_start);
    int elapsed = t_diff.tv_sec * 1e6 + t_diff.tv_usec;

    for (int i = 0; i < n; i++) {
        if (!is_sorted(test[i])) {
            print_vector(test[i]);
            printf("Fail\n");
            return 21;
        }
    }

    printf("Time (us): %i\n", elapsed/n);

}

