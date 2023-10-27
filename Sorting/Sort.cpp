#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>


template <typename T>
class Sort {
private:
    std::string sort_name;
    
public:

    virtual int sort(std::vector<T> &vec, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) = 0;

    void set_name(std::string &name) {
        sort_name = name;
    }

    std::string get_name() const {
        return sort_name;
    }

    void print(std::vector<T> &vec) {
        for (int i = 0; i < vec.size(); i++) {
            std::cout << vec[i] << " ";
        }
        std::cout << "\n";
    }

    ~Sort() = default;

};