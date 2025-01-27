#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "Benchmark.cpp"

int main() {
    Benchmark<std::string> bench("Insertion Sort");
    //bench.test_str();
    //std::cout << bench.get_n_operation_per_second();
    std::cout << "--------------------------------------------------\n";
    //bench.get_cur_time_for_big_numeric_type_tests();
    std::cout << "--------------------------------------------------\n";
    //bench.get_cur_time_for_string_tests();
    std::cout << "--------------------------------------------------\n";

    std::vector <std::string> vec;
    std::vector <std::string> vec1;
    for (int i = 0; i < 10000; i++) {
        std::string tmp;
        for (int j = 0; j < 10000; j++) {
            tmp.push_back('a' + std::rand() % 26);
        }
        //tmp.push_back('a' + std::rand() % 26);
        vec.push_back(tmp);
        vec1.push_back(tmp);
    }

    BinarySearchInsertionSort<std::string> srt1;
    InsertionSort<std::string> srt2;
    
    auto c_start1 = std::chrono::high_resolution_clock::now();
    if (!srt1.my_sort(vec)) {
        std::cout << "The array is sorted incorrectly\n";
        srt1.print(vec);
        exit(-1);      
    }
    auto c_end1 = std::chrono::high_resolution_clock::now();
    long long time1 = std::chrono::duration_cast<std::chrono::nanoseconds>(c_end1 - c_start1).count();
    //std::cout << vec[0] << "\n\n" << vec[10000 - 1] << "\n\n";   
    //std::cout << time1;
    auto c_start2 = std::chrono::high_resolution_clock::now();
    if (!srt2.my_sort(vec1)) {
        std::cout << "The array is sorted incorrectly\n";
        srt1.print(vec1);
        exit(-1);      
    }
    //std::cout << vec1[0] << "\n\n" << vec1[10000 - 1] << "\n\n";   
    auto c_end2 = std::chrono::high_resolution_clock::now();
    long long time2 = std::chrono::duration_cast<std::chrono::nanoseconds>(c_end2 - c_start2).count();    
    std::cout << time1 << " " << time2 << "\n";

}