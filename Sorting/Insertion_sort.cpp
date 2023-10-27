#pragma once
#include "Sort.cpp"
#include <vector>

template <typename T>
class InsertionSort : public Sort<T> {
public:

    int sort(std::vector<T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) override {
        for (int i = 1; i < vec.size(); i++) {
            int k = i;

            while (k > 0) {
                if (cmp(vec[k], vec[k - 1])) {
                    std::swap(vec[k - 1],  vec[k]);
                    k--;
                }
                else { 
                    break; 
                }
            }
        }

        return std::is_sorted(vec.begin(), vec.end(), cmp);
    }

};
