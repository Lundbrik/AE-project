#include <vector>

template <class T>
void nsort_7(std::vector<T> &data) {
    if (data[0] > data[1])
        std::swap(data[0], data[1]);

    if (data[2] > data[3])
        std::swap(data[2], data[3]);

    if (data[4] > data[5])
        std::swap(data[4], data[5]);

    if (data[0] > data[6])
        std::swap(data[0], data[6]);

    if (data[2] > data[4])
        std::swap(data[2], data[4]);

    if (data[0] > data[2])
        std::swap(data[0], data[2]);

    if (data[1] > data[3])
        std::swap(data[1], data[3]);

    if (data[5] > data[6])
        std::swap(data[5], data[6]);

    if (data[1] > data[4])
        std::swap(data[1], data[4]);

    if (data[2] > data[5])
        std::swap(data[2], data[5]);

    if (data[1] > data[2])
        std::swap(data[1], data[2]);

    if (data[4] > data[5])
        std::swap(data[4], data[5]);

    if (data[2] > data[4])
        std::swap(data[2], data[4]);

    if (data[3] > data[6])
        std::swap(data[3], data[6]);

    if (data[3] > data[5])
        std::swap(data[3], data[5]);

    if (data[3] > data[4])
        std::swap(data[3], data[4]);
    return;
}
