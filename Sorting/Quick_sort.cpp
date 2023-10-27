#pragma once
#include "Sort.cpp"
#include <vector>
#include <random>
#include <iostream>

std::mt19937 rnd(139251);

template <typename T>
class QuickSort : public Sort<T> {
private:
public:

    int sort(std::vector<T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) override {
        quick_sort(vec, 0, (int)vec.size() - 1, cmp);
        return std::is_sorted(vec.begin(), vec.end(), cmp);
    }

    void quick_sort(std::vector <int> &vec, int l, int r, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if (l >= r) {
            return;
        }
        int q = partition(vec, l, r, cmp);
        quick_sort(vec, l, q, cmp);
        quick_sort(vec, q + 1, r, cmp);
    }

    int partition(std::vector<T> &vec, int l, int r, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        int rnd_pos = l + (rnd() % (r - l + 1));
        T el = vec[rnd_pos];
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

};

