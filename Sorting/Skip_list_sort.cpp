#pragma once
#include "Sort.cpp"
#include <vector>
#include <concepts>
#include <cmath>

template <typename T>
struct SLNode {
    SLNode<T> *next, *down;
    T value;

    SLNode(SLNode<T> *_next, SLNode<T> *_down, T _value) : next(_next), down(_down), value(_value) {}

    ~SLNode() {
        // SLNode<T> *cur = this;
        // while (cur) {
        //     SLNode<T> *tmp = cur;
        //     cur = cur->down;
        //     delete tmp;
        // }
    }
};


template <typename T>
class SkipList {
private:
    std::mt19937 rnd;
    std::random_device randD;
    int max_level;
    SLNode<T> *start;
    bool (*cmp)(const T &, const T &);

public:

    SkipList(std::vector <T> &vec, bool _cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        max_level = std::round(std::log2(vec.size()));
        rnd.seed(randD());
        cmp = _cmp;
        build(vec);
    }

    void build(std::vector <T> &vec) {
        start = new SLNode<T>(nullptr, nullptr, NULL);
        SLNode<T> *cur = start;
        for (int i = 1; i < max_level; i++) {
            cur->down = new SLNode<T>(nullptr, nullptr, NULL);
            cur = cur->down;
        }

        for (int i = 0; i < vec.size(); i++) {
            insert(start, vec[i]);
        }
    }

    void insert(SLNode<T> *node, T value) {
        while (node->next && cmp(node->next->value, value)) {
            node = node->next;
        }

        if (node->down) {
            insert(node->down, value);
        }
        else {
            node->next = new SLNode<T>(node->next, nullptr, value);
        }
    }

    void get_sorted(std::vector <T> &vec) {
        int i = 0;
        SLNode<T> *cur = start;
        while (cur->down) {
            cur = cur->down;
        }

        while (cur->next) {
            vec[i] = cur->next->value;
            cur = cur->next;
            i++;
        }
    }

    ~SkipList() {
        // SLNode<T> *cur = start;
        // while (cur) {
        //     SLNode<T> *tmp = cur;
        //     cur = cur->next;
        //     delete tmp;
        // }
    }


};

template <typename T>
class SkipListSort : public Sort<T> {
private:
public:

    SkipListSort() {
        this->set_name("Skip List Sort");
    }

    int my_sort(std::vector<T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) override {
        SkipList<T> skip_list(vec, cmp);
        skip_list.get_sorted(vec);
        return std::is_sorted(vec.begin(), vec.end(), cmp);
    }

};

