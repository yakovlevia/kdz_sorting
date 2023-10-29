#include <vector>
#include <string>
#include <iostream>
#include "Benchmark.cpp"

int main() {
    Benchmark<std::string> bench("Skip List Sort");
    //bench.get_cur_time_for_small_numeric_type_tests();
    std::cout << "--------------------------------------------------\n";
    //bench.get_cur_time_for_big_numeric_type_tests();
    std::cout << "--------------------------------------------------\n";
    bench.get_cur_time_for_string_tests();
    std::cout << "--------------------------------------------------\n";
}