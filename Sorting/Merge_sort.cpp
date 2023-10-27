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

    void merge_sort(std::vector <T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if (vec.size() <= 1) {
            return;
        }

        int r = (int)vec.size() - 1;
        int mid = r >> 1;
        std::vector <T> left(mid + 1);
        std::vector <T> right(r - mid);

        for (int i = 0; i <= mid; i++) {
            left[i] = vec[i];
        }
        for (int i = mid + 1; i <= r; i++) {
            right[i - mid - 1] = vec[i];
        }

        merge_sort(left, cmp);
        merge_sort(right, cmp);

        int cnt_l, cnt_r;
        cnt_l = cnt_r = 0;

        for (int i = 0; i <= r; i++) {
            if (cnt_l > mid) {
                vec[i] = right[cnt_r];
                cnt_r++;
            }
            else if (cnt_r > r - mid - 1) {
                vec[i] = left[cnt_l];
                cnt_l++;
            }
            else if (cmp(left[cnt_l], right[cnt_r])) {
                vec[i] = left[cnt_l];
                cnt_l++;
            }
            else {
                vec[i] = right[cnt_r];
                cnt_r++;
            }
        }
    }

};

