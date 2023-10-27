#include <vector>
#include <string>
#include <iostream>
#include "Sorting/Sort.cpp"
#include "Sorting/Heap_sort.cpp"
#include "Sorting/Guaranteed_quick_sort.cpp"
#include "Sorting/Insertion_sort.cpp"
#include "Sorting/Merge_sort.cpp"
#include "Sorting/Quick_sort.cpp"

int main() {
    QuickSort<int> my_sort;
    std::vector <int> vec = {7 ,7 ,7, 100, 100, 12, -1, -1};
    my_sort.sort(vec);
    my_sort.print(vec);
}