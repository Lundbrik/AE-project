template <class T>
bool is_sorted(std::vector<T> &data) {
    for (int i = 0; i < data.size()-1; i++) {
        if (data[i] > data[i+1])
            return false;
    }
    return true;
}

template <class T>
bool is_equal(std::vector<T> &a, std::vector<T> &b) {
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}
