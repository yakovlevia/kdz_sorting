#include <vector>
#include <string>
#include <iostream>
#include "Sorting/Sort.cpp"
#include "Sorting/Heap_sort.cpp"
#include "Sorting/Guaranteed_quick_sort.cpp"
#include "Sorting/Insertion_sort.cpp"
#include "Sorting/Merge_sort.cpp"
#include "Sorting/Quick_sort.cpp"
#include "Benchmark.cpp"

int main() {
    Benchmark<std::string> bench("Quick Sort");
    std::vector <long long> vec = {-1, -2, -3, -4};
    std::cout << bench.run_1_test(2, 20);
}