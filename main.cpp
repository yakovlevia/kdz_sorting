#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Benchmark.cpp"

int main() {
    Benchmark<int> bench("Binary Search Insertion Sort");
    bench.get_all_time_for_small_numeric_type_tests();
    std::cout << "--------------------------------------------------\n";
    //bench.get_cur_time_for_big_numeric_type_tests();
    std::cout << "--------------------------------------------------\n";
    //bench.get_cur_time_for_string_tests();
    std::cout << "--------------------------------------------------\n";
}