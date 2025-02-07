#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <map>
#include <iomanip>
#include "Sorting/Sort.cpp"
#include "Sorting/Heap_sort.cpp"
#include "Sorting/Guaranteed_quick_sort.cpp"
#include "Sorting/Insertion_sort.cpp"
#include "Sorting/Merge_sort.cpp"
#include "Sorting/Quick_sort.cpp"
#include "Sorting/Skip_list_sort.cpp"
#include "Sorting/Binary_search_insertion_sort.cpp"

template <typename T>
class Benchmark {
private:
    std::vector <int> small_test_sizes;
    std::vector <int> big_test_sizes;
    std::vector <int> string_test_sizes;
    std::mt19937 rnd;
    std::random_device randD;
    std::vector<std::string> sort_names;
    Sort<T> *srt;

public:
    
    Benchmark(std::string name = "Insertion Sort") {
        rnd.seed(randD());
        small_test_sizes = {10, 50, 100, 500, 1000, 5000, 10000};
        big_test_sizes = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000};
        //big_test_sizes = {5000000};
        string_test_sizes = {10, 50, 100, 500, 1000, 5000, 10000};
        sort_names = {"Heap Sort", "Guaranteed Quick Sort", "Insertion Sort", "Quick Sort", "Merge Sort", "Binary Search Insertion Sort", "Skip List Sort"};
        srt = nullptr;
        chage_sort(name);
    }

    void chage_sort(std::string name) {
        delete srt;
        std::map<std::string, int> my_map;
        for (int i = 0; i < sort_names.size(); i++) {
            my_map[sort_names[i]] = i + 1;
        }

        switch (my_map[name]) {
            case 1:
                srt = new HeapSort<T>;
                break;
            case 2:
                srt = new GuaranteedQuickSort<T>;
                break;
            case 3:
                srt = new InsertionSort<T>;
                break;
            case 4:
                srt = new QuickSort<T>;
                break;
            case 5:
                srt = new MergeSort<T>;
                break;
            case 6:
                srt = new BinarySearchInsertionSort<T>;
                break;
            case 7:
                srt = new SkipListSort<T>;
                break;
            default:
                std::cout << "No such sorting\n";
                exit(-1);
        }  
    }

    std::vector<T> make_random_test(int n, int str_size = -1) {
        std::vector <T> test(n);

        if constexpr (std::is_same_v<T, int>) {
            std::uniform_int_distribution<int> gen(INT_MIN, INT_MAX);
            for (int i = 0; i < n; i++) {
                test[i] = gen(rnd);
            }
        }
        else if constexpr (std::is_same_v<T, long long>) {
            std::uniform_int_distribution<long long> gen(LONG_LONG_MIN, LONG_LONG_MAX);
            for (int i = 0; i < n; i++) {
                test[i] = gen(rnd);
            }
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            std::uniform_int_distribution<int> gen(0, 25);
            for (int i = 0; i < n; i++) {
                std::string tmp_str;
                for (int j = 0; j < str_size - 1; j++) {
                    tmp_str.push_back(char('a'));
                }
                tmp_str.push_back(char('a' + gen(rnd)));
                test[i] = tmp_str;
            }
        }
        else {
            std::cout << "Can't generate tests for this type\n";
            exit(-1); 
        }
        
        return test;
    }

    long long run_1_test(int size, int str_size = -1, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        std::vector <T> tmp = make_random_test(size, str_size);
        auto c_start = std::chrono::high_resolution_clock::now();
        if (!srt->my_sort(tmp, cmp)) {
            std::cout << "The array is sorted incorrectly\n";
            print(tmp);
            exit(-1);
        }
        auto c_end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(c_end - c_start).count();
    }

    long long run_n_tests(int size, int n, int str_size = -1, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        long long time = 0;
        for (int i = 0; i < n; i++) {
            //long long t = time;
            time += run_1_test(size, str_size, cmp);
            //std::cout << std::endl;
            //std ::cout << time - t << std::endl;
        }
        time /= n;
        return time;
    }
    
    double run_1_str_test(int size, int str_size = -1, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        std::vector <T> tmp = make_random_test(size, str_size);
        std::vector <T> tt = tmp;
        chage_sort("Insertion Sort");
        auto c_start = std::chrono::high_resolution_clock::now();
        if (!srt->my_sort(tt, cmp)) {
            std::cout << "The array is sorted incorrectly\n";
            print(tt);
            exit(-1);

        }
        auto c_end = std::chrono::high_resolution_clock::now();
        long long time1 = std::chrono::duration_cast<std::chrono::nanoseconds>(c_end - c_start).count();
        chage_sort("Binary Search Insertion Sort");
        auto c_start1 = std::chrono::high_resolution_clock::now();
        if (!srt->my_sort(tmp, cmp)) {
            std::cout << "The array is sorted incorrectly\n";
            print(tmp);
            exit(-1);
            
        }
        auto c_end1 = std::chrono::high_resolution_clock::now();
        long long time2 = std::chrono::duration_cast<std::chrono::nanoseconds>(c_end1 - c_start1).count();
        //std::cout << time2 << " " << time1 << " " << time2 / double(time1) << "\n";
        return time2 / double(time1);
    }




    double run_n_str_tests(int size, int n, int str_size = -1, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        double time = 0;
        for (int i = 0; i < n; i++) {
            //long long t = time;
            time += run_1_str_test(size, str_size, cmp);
            //std::cout << std::endl;
            //std ::cout << time - t << std::endl;
        }
        time /= n;
        return time;
    }

    void get_cur_time_for_small_numeric_type_tests(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if constexpr (!std::is_integral_v<T>) {
            std:: cout << "The Bechmark is not number\n";
            exit(-1);
        }

        std::cout << srt->get_name() << "\n";
        for (auto &g : small_test_sizes) {
            std::cout << run_n_tests(g, 10, -1, cmp) << ", ";
        }
        std::cout << "\n";

        /*std::cout << srt->get_name() << "\n";
        for (auto &g : small_test_sizes) {
            std::cout << std::setw(10) << g << " | " << std::setw(11) << run_n_tests(g, 10, -1, cmp) << " nanoseconds\n";
        }
        std::cout << "\n";
        */
    }

    void get_all_time_for_small_numeric_type_tests(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if constexpr (!std::is_integral_v<T>) {
            std:: cout << "The Bechmark is not number\n";
            exit(-1);
        }
        for (int i = 0; i < sort_names.size(); i++) {
            chage_sort(sort_names[i]);
            get_cur_time_for_small_numeric_type_tests(cmp);
        }
    }

    void get_cur_time_for_big_numeric_type_tests(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if constexpr (!std::is_integral_v<T>) {
            std:: cout << "The Bechmark is not number\n";
            exit(-1);
        }

        std::cout << srt->get_name() << "\n";
        for (auto &g : big_test_sizes) {
            std::cout << run_n_tests(g, 2, -1, cmp) << ", ";
        }
        std::cout << "\n";

        // std::cout << srt->get_name() << "\n";
        // for (auto &g : big_test_sizes) {
        //     std::cout << std::setw(10) << g << " | " << std::setw(11) << run_n_tests(g, 10, -1, cmp) << " nanoseconds\n";
        // }
        // std::cout << "\n";
    }

    void get_all_time_for_big_numeric_type_tests(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if constexpr (!std::is_integral_v<T>) {
            std:: cout << "The Bechmark is not number\n";
            exit(-1);
        }
        for (int i = 0; i < sort_names.size(); i++) {
            if (sort_names[i] == "Insertion Sort") continue;
            if (sort_names[i] == "Binary Search Insertion Sort") continue;
            chage_sort(sort_names[i]);
            get_cur_time_for_big_numeric_type_tests(cmp);
        }
    }

    void get_cur_time_for_string_tests(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if constexpr (!std::is_same_v<T, std::string>) {
            std:: cout << "The Bechmark is not string\n";
            exit(-1);
        }
        std::cout << srt->get_name() << "\n";
        std::cout << std::setw(11) << "N \\ M";
        for (int i = 0; i < string_test_sizes.size(); i++) {
            //std::cout << "|" << std::setw(25) << string_test_sizes[i];
        }
        std::cout << '\n';
        for (auto &g : small_test_sizes) {
            //std::cout << std::setw(10) << g;
            for (auto &q :string_test_sizes) {
                std::cout << run_n_tests(g, 10, q, cmp) << ", ";
                //std::cout << " | " << std::setw(11) << run_n_tests(g, 10, q, cmp) << " nanoseconds";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }


    void test_str(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if constexpr (!std::is_same_v<T, std::string>) {
            std:: cout << "The Bechmark is not string\n";
            exit(-1);
        }

        for (auto &g : small_test_sizes) {
            for (auto &q :string_test_sizes) {
                std::cout << std::fixed << std::setprecision(4) << run_n_str_tests(g, 10, q, cmp) << ", ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void test_str1(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if constexpr (!std::is_same_v<T, std::string>) {
            std:: cout << "The Bechmark is not string\n";
            exit(-1);
        }

        for (auto &g : small_test_sizes) {
            for (auto &q :string_test_sizes) {
                chage_sort("Insertion Sort");
                long long tt = run_n_tests(g, 10, q, cmp);
                chage_sort("Binary Search Insertion Sort");
                long long ttt = run_n_tests(g, 10, q, cmp);
                std::cout << std::fixed << std::setprecision(4) << ttt / double(tt) << ", ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void get_all_time_for_string_tests(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        if constexpr (!std::is_same_v<T, std::string>) {
            std:: cout << "The Bechmark is not string\n";
            exit(-1);
        }
        for (int i = 0; i < sort_names.size(); i++) {
            chage_sort(sort_names[i]);
            get_cur_time_for_string_tests(cmp);
        }
    }


    int my_sort(std::vector<T> &vec) {
        return srt->my_sort(vec);
    }

    void print(std::vector<T> &vec) {
        return srt->print(vec);
    }

    long long get_n_operation_per_second() {
        std::vector <long long> pos(1e9, 0);
        std::vector <long long> temp(1e9, 0);
        srand(time(NULL));
        for (int i = 0; i < 1e9; i++) {
            pos[i] = rand() % (long long)1e9;
        }
        auto c_start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1e9; i++) {
            temp[pos[i]]++;
        }
        auto c_end = std::chrono::high_resolution_clock::now();
        return round(1e9 / ((long long) std::chrono::duration_cast<std::chrono::nanoseconds>(c_end - c_start).count()) * 1e9);
    }

    ~Benchmark(){
        delete srt;
    }
    
};