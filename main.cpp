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
    Benchmark<int> bench;
    bench.get_all_time_for_small_numeric_type_tests();
    //std::cout << std::is_same_v<long long, int>;
}