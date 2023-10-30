#pragma once
#include "Sort.cpp"
#include <vector>
#include <algorithm>

template <typename T>
class GuaranteedQuickSort : public Sort<T> {
protected:

    void quick_sort(std::vector <T> &vec, int l, int r, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if (l >= r) {
            return;
        }
        int q = partition(vec, l, r, cmp);
        quick_sort(vec, l, q, cmp);
        quick_sort(vec, q + 1, r, cmp);
    }

    int partition(std::vector<T> &vec, int l, int r, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        T el = get_median(vec, l, r, cmp);
        int i = l;
        int j = r;
        while (i <= j) {
            while (cmp(vec[i], el)) {
                i++;
            }
            while (cmp(el, vec[j])) {
                j--;
            }
            if (i >= j) {
                break;
            }
            std::swap(vec[i++], vec[j--]);
        }
        return j;
    }

    T get_median(std::vector<T> &vec, int l, int r, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if (r - l  + 1 <= 5) {
            return median_of_5_elements(vec, l, r, cmp);
        }

        std::vector <T> tmp;

        for (int i = l; i <= r; i += 5) {
            int pos = i +  4;
            if (pos > r) {
                pos = r;
            }
            tmp.push_back(median_of_5_elements(vec, i, pos, cmp));
        }
        
        return get_median(tmp, 0, tmp.size() - 1, cmp);
    }

    void simple_sort(std::vector <T> &vec, int l, int r, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        for (int i = l + 1; i <= r; i++) {
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
    }

    T median_of_5_elements(std::vector <T> &vec, int l, int r, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {   
        if (r - l < 4) {
            simple_sort(vec, l, r, cmp);
        }
        else {
            if (cmp(vec[l + 1], vec[l + 0])) std::swap(vec[l + 1], vec[l + 0]);  // vec[0] <= vec[1]
            if (cmp(vec[l + 2], vec[l + 3])) std::swap(vec[l + 2], vec[l + 3]);  // vec[2] <= vec[3] && vec[0] <= vec[1]
            if (cmp(vec[l + 0], vec[l + 2])) {                                   // vec[0] <= vec[1] <= vec[2] && vec[0] <= vec[3]
                std::swap(vec[l + 1], vec[l + 2]);
                std::swap(vec[l + 2], vec[l + 3]);
            }
            else {
                std::swap(vec[l + 0], vec[l + 2]);
                std::swap(vec[l + 1], vec[l + 2]);
            }
            
            if (cmp(vec[l + 4], vec[l + 1])) {                                   // vec[0] <= vec[1] <= vec[2] <= vec[3] && vec[0] <= vec[4]
                if (cmp(vec[l + 4], vec[l + 0])) {
                    std::swap(vec[l + 0], vec[l + 4]);
                    std::swap(vec[l + 1], vec[l + 4]);
                    std::swap(vec[l + 2], vec[l + 4]);
                    std::swap(vec[l + 3], vec[l + 4]);
                }
                else {
                    std::swap(vec[l + 1], vec[l + 4]);
                    std::swap(vec[l + 2], vec[l + 4]);
                    std::swap(vec[l + 3], vec[l + 4]);
                }
            }
            else {
                if (cmp(vec[l + 4], vec[l + 2])) {
                    std::swap(vec[l + 2], vec[l + 4]);
                    std::swap(vec[l + 3], vec[l + 4]);
                }
                else {
                    std::swap(vec[l + 3], vec[l + 4]);
                }
            }

            if (cmp(vec[l + 4], vec[l + 2])) {                                    // vec[0] <= vec[1] <= vec[2] <= vec[3] <= vec[4]
                if (cmp(vec[l + 4], vec[l + 1])) {
                    std::swap(vec[l + 1], vec[l + 4]);
                    std::swap(vec[l + 2], vec[l + 4]);
                    std::swap(vec[l + 3], vec[l + 4]);
                }
                else {
                    std::swap(vec[l + 2], vec[l + 4]);
                    std::swap(vec[l + 3], vec[l + 4]);
                }
            }
            else {
                if (cmp(vec[l + 4], vec[l + 3])) {
                    std::swap(vec[l + 3], vec[l + 4]);
                }
            }
        }
        
        return vec[l + (r - l) / 2];
    }

public:

    GuaranteedQuickSort() {
        this->set_name("Guaranteed Quick Sort");
    }

    int my_sort(std::vector<T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) override {
        quick_sort(vec, 0, (int)vec.size() - 1, cmp);
        return std::is_sorted(vec.begin(), vec.end(), cmp);
    }

};

