#pragma once
#include "Sort.cpp"
#include "Quick_sort.cpp"
#include <vector>

template <typename T>
class GuaranteedQuickSort : public QuickSort<T> {
public:

    GuaranteedQuickSort() {
        this->set_name("Guaranteed Quick Sort");
    }

    int partition(std::vector<T> &vec, int l, int r, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        T el = get_median(vec, l, r);
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

    int get_median(std::vector<T> &vec, int l, int r, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        
        std::vector <T> tmp;
        tmp.reserve((r - l) / 5 + 1);

        for (int i = l; i <= r; i += 5) {
            tmp.push_back(median_of_5_elements(vec, i, std::min(i + 4, vec.size() - 1), cmp));
        }

        if (vec.size() <= 5) {
            return median_of_5_elements(vec);
        }
        
        return partition(tmp, 0, tmp.size() - 1, cmp);
    }

    T median_of_5_elements(std::vector <T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {   
        std::vector <T> tmp;
        for (T &q : vec) {
            tmp.push_back(q);
        }
        std::sort(tmp.begin(), tmp.end(), cmp);
        return tmp[tmp.size() / 2];
    }

};

