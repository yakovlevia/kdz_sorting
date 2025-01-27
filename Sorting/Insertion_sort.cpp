#pragma once
#include "Sort.cpp"
#include <vector>

template <typename T>
class InsertionSort : public Sort<T> {
public:

    InsertionSort() {
        this->set_name("Insertion Sort");
    }

    int my_sort(std::vector<T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) override {
        int z = 0;
        for (int i = 1; i < vec.size(); i++) {
            int k = i;

            while (k > 0) {
                z++;
                if (cmp(vec[k], vec[k - 1])) {
                    std::swap(vec[k - 1],  vec[k]);
                    k--;
                }
                else { 
                    break; 
                }
            }
        }
        std::cout << z << "\n";
        return std::is_sorted(vec.begin(), vec.end(), cmp);
    }

};
