#pragma once
#include "Sort.cpp"
#include <vector>
#include <iostream>

template <typename T>
class BinarySearchInsertionSort : public Sort<T> {
public:

    BinarySearchInsertionSort() {
        this->set_name("Binary Search Insertion Sort");
    }

    int my_sort(std::vector<T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) override {
        for (int i = 1; i < vec.size(); i++) {
            int k = 1;
            int l = 0;
            int pos = std::lower_bound(vec.begin(), vec.begin() + i, vec[i], cmp) - vec.begin();
            for (int j = i; j > pos; j--) {
                std::swap(vec[j], vec[j - 1]);
            }
        }

        return std::is_sorted(vec.begin(), vec.end(), cmp);
    }

};
