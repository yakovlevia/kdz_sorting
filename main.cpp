#include <vector>
#include <string>
#include <iostream>
#include "Benchmark.cpp"

int main() {
    Benchmark<long long> bench("Skip List Sort");
    bench.get_all_time_for_small_numeric_type_tests();
    std::cout << "--------------------------------------------------\n";
    bench.get_all_time_for_big_numeric_type_tests();
    std::cout << "--------------------------------------------------\n";
}