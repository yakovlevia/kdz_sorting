#pragma once
#include "Sort.cpp"
#include <vector>
#include <concepts>

template <typename T>
class Heap {
private:

    std::vector <T> heap;
    bool (*cmp)(const T &, const T &);

public:

    Heap(std::vector <T> &vec, bool _cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        cmp = _cmp;
        build(vec);
    }

    void build(std::vector <T> &vec) {
        heap = vec;
        for (int i = vec.size() - 1; i >= 0; --i) {
            sift_down(i);
        }
    }

    void sift_up(int vert) {
        while (vert > 1 && cmp(heap[vert], heap[(vert + 1) / 2 - 1])) {
            std::swap(heap[vert], heap[(vert + 1) / 2 - 1]);
            vert = (vert + 1) / 2 - 1;
        }
    }


    void sift_down(int vert) {
        while (2 * vert + 1 < heap.size()) {
            int l = 2 * vert + 1;
            int r = 2 * vert + 2;
            int u = (r < heap.size() && cmp(heap[r], heap[l]) ? r : l);
            if (heap[vert] <= heap[u]) {
                break;
            }
            std::swap(heap[vert], heap[u]);
            vert = u;
        }
    }

    T get_min() const {
        return heap[0];
    }

    void del_min() {
        std::swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        sift_down(0);
    }

    void print() {
        for (int i = 0; i < heap.size(); i++) {
            std::cout << heap[i] << " ";
        }
        std::cout << "\n";
    }

    ~Heap() = default;


};

template <typename T>
class HeapSort : public Sort<T> {
public:

    HeapSort() {
        this->set_name("Heap Sort");
    }

    int my_sort(std::vector<T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) override {
        Heap<T> obj(vec, cmp);
        obj.build(vec);


        for (int i = 0; i < vec.size(); i++) {
            vec[i] = obj.get_min();
            obj.del_min();
        }

        return std::is_sorted(vec.begin(), vec.end(), cmp);
    }

};

