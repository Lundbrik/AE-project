#include <algorithm>
#include <vector>
#include <stdio.h>
#include "nsort.h"


template <class T>
void fsort(std::vector<T> &data) {
    switch (data.size()) {
        case 7:
            nsort_7<T>(data);
            break;
        default:
            std::sort(data.begin(), data.end());
    }
}



int main() {
    std::vector<int> test = {2, 9, 3, 5, 0, -1, 10};
    fsort(test);
    for (int i : test) {
        printf("%i, ", i);
    }
    return 0;
}
