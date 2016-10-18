#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <time.h>

#define COND(c, x, y) { x = (c) ? y : x; }
/*#define comp_swap(x, y) { int ax = x; COND(y < ax, x, y); \
                                      COND(y < ax, y, ax); }*/

#define comp_swap(x, y) { if (x < y) {int tmp = x; x = y; y = tmp;} }
void nsort_16(int data[]) {
    // Layer 1
    comp_swap(data[0], data[1]);
    comp_swap(data[2], data[3]);
    comp_swap(data[4], data[5]);
    comp_swap(data[6], data[7]);
    comp_swap(data[8], data[9]);
    comp_swap(data[10], data[11]);
    comp_swap(data[12], data[13]);
    comp_swap(data[14], data[15]);

    // Layer 2
    comp_swap(data[1], data[3]);
    comp_swap(data[5], data[7]);
    comp_swap(data[9], data[11]);
    comp_swap(data[13], data[15]);

    // Layer 3
    comp_swap(data[0], data[2]);
    comp_swap(data[4], data[6]);
    comp_swap(data[8], data[10]);
    comp_swap(data[12], data[14]);

    // Layer 4
    comp_swap(data[3], data[7]);
    comp_swap(data[11], data[15]);

    // Layer 5
    comp_swap(data[2], data[6]);
    comp_swap(data[10], data[14]);

    // Layer 6
    comp_swap(data[1], data[5]);
    comp_swap(data[9], data[13]);

    // Layer 7
    comp_swap(data[0], data[4]);
    comp_swap(data[8], data[12]);

    // Layer 8
    comp_swap(data[7], data[15]);

    // Layer 9
    comp_swap(data[6], data[14]);

    // Layer 10
    comp_swap(data[5], data[13]);

    // Layer 11
    comp_swap(data[4], data[12]);

    // Layer 12
    comp_swap(data[3], data[11]);

    // Layer 13
    comp_swap(data[2], data[10]);

    // Layer 14
    comp_swap(data[1], data[9]);

    // Layer 15
    comp_swap(data[0], data[8]);

    // Layer 16
    comp_swap(data[5], data[10]);

    // Layer 17
    comp_swap(data[6], data[9]);

    // Layer 18
    comp_swap(data[1], data[2]);
    comp_swap(data[3], data[12]);

    // Layer 19
    comp_swap(data[4], data[8]);

    // Layer 20
    comp_swap(data[7], data[11]);
    comp_swap(data[13], data[14]);

    // Layer 21
    comp_swap(data[2], data[8]);
    comp_swap(data[11], data[14]);

    // Layer 22
    comp_swap(data[1], data[4]);
    comp_swap(data[7], data[13]);

    // Layer 23
    comp_swap(data[2], data[4]);
    comp_swap(data[5], data[6]);
    comp_swap(data[9], data[10]);
    comp_swap(data[11], data[13]);

    // Layer 24
    comp_swap(data[7], data[12]);

    // Layer 25
    comp_swap(data[3], data[8]);

    // Layer 26
    comp_swap(data[3], data[5]);
    comp_swap(data[7], data[9]);

    // Layer 27
    comp_swap(data[6], data[8]);
    comp_swap(data[10], data[12]);

    // Layer 28
    comp_swap(data[3], data[4]);
    comp_swap(data[5], data[6]);
    comp_swap(data[7], data[8]);
    comp_swap(data[9], data[10]);
    comp_swap(data[11], data[12]);

    // Layer 29
    comp_swap(data[6], data[7]);
    comp_swap(data[8], data[9]);
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 42;
    }
    int n = atoi(argv[1]);

    int* test[n];


    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        test[i] = (int*) malloc(16 * sizeof(int));
        for (int j = 0; j < 16; j++) {
            test[i][j] = rand() % 931;
        }
    }

    struct timeval t_start, t_end, t_diff;
    gettimeofday(&t_start, NULL);

    for (int i = 0; i < n; i++) {
        nsort_16(test[i]);
    }

    gettimeofday(&t_end, NULL);
    timeval_subtract(&t_diff, &t_end, &t_start);
    int elapsed = t_diff.tv_sec * 1e6 + t_diff.tv_usec;

    printf("Time (us): %i\n", elapsed);

}
