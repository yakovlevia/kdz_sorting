#pragma once
#include "Sort.cpp"
#include <vector>

template <typename T>
class MergeSort : public Sort<T> {
public:

    MergeSort() {
        this->set_name("Merge Sort");
    }

    int my_sort(std::vector<T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) override {
        merge_sort(vec, cmp);
        return std::is_sorted(vec.begin(), vec.end(), cmp);
    }

    void merge(std::vector <T> &vec, int left, int mid, int right, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        int it_l = 0;
        int it_r = 0;
        std::vector <T> tmp(right - left);
  
        while (left + it_l < mid && mid + it_r < right) {
            if (cmp(vec[left + it_l], vec[mid + it_r])) {
                tmp[it_l + it_r] = vec[left + it_l];
                it_l++;
            }
            else {
                tmp[it_l + it_r] = vec[mid + it_r];
                it_r++;
            }
        }
  
        while (left + it_l < mid) {
            tmp[it_l + it_r] = vec[left + it_l];
            it_l++;
        }
  
        while (mid + it_r < right) {
            tmp[it_l + it_r] = vec[mid + it_r];
            it_r++;
        }
  
        for (int i = left; i < right; i++) {
            vec[i] = tmp[i - left];
        }
    }

    void merge_sort(std::vector <T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        for (int i = 1; i < vec.size(); i *= 2) {
            for (int j = 0; j < vec.size() - i; j += 2 * i) {
                merge(vec, j, j + i, std::min(j + 2 * i, (int)vec.size()), cmp);
            }
        }
    }

};

