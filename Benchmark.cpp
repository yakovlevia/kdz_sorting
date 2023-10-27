#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <map>
#include "Sorting/Sort.cpp"
#include "Sorting/Heap_sort.cpp"
#include "Sorting/Guaranteed_quick_sort.cpp"
#include "Sorting/Insertion_sort.cpp"
#include "Sorting/Merge_sort.cpp"
#include "Sorting/Quick_sort.cpp"

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
    Benchmark() {
        rnd.seed(randD());
        small_test_sizes = {20, 50, 100, 500, 1000, 5000, 10000};
        big_test_sizes = {100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000};
        string_test_sizes = {10, 50, 100, 500, 1000, 5000, 10000};
        sort_names = {"Heap Sort", "Guaranteed Quick Sort", "Insertion Sort", "Quick Sort", "Merge Sort"};
        srt = nullptr;
        chage_sort("Insertion Sort");
    }
    
    Benchmark(std::string name) {
        rnd.seed(randD());
        small_test_sizes = {20, 50, 100, 500, 1000, 5000, 10000};
        big_test_sizes = {100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000};
        string_test_sizes = {10, 50, 100, 500, 1000, 5000, 10000};
        sort_names = {"Heap Sort", "Guaranteed Quick Sort", "Insertion Sort", "Quick Sort", "Merge Sort"};
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
                for (int j = 0; j < str_size; j++) {
                    tmp_str.push_back(char('a' + gen(rnd)));
                }
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
        if (!srt->sort(tmp, cmp)) {
            std::cout << "The array is sorted incorrectly\n";
            exit(-1);
        }
        auto c_end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(c_end - c_start).count();
    }

    long long run_n_tests(int size, int n, int str_size = -1, bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        long long time = 0;
        for (int i = 0; i < n; i++) {
            time += run_1_test(size, str_size, cmp);
        }
        time /= n;
        return time;
    }

    void get_cur_time_for_small_numeric_type_tests(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        std::cout << srt->get_name() << "\n";
        for (auto &g : small_test_sizes) {
            std::cout << g << " | " << run_n_tests(g, 10, -1, cmp) << " nanoseconds\n";
        }
        std::cout << "\n";
    }

    void get_all_time_for_small_numeric_type_tests(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        for (int i = 0; i < sort_names.size(); i++) {
            chage_sort(sort_names[i]);
            get_cur_time_for_small_numeric_type_tests(cmp);
        }
    }

    void get_cur_time_for_big_numeric_type_tests(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        std::cout << srt->get_name() << "\n";
        for (auto &g : big_test_sizes) {
            std::cout << g << " | " << run_n_tests(g, 10, -1, cmp) << " nanoseconds\n";
        }
        std::cout << "\n";
    }

    void get_all_time_for_big_numeric_type_tests(bool cmp (const T &a, const T &b) = [](const T &a, const T &b) {return a < b;}) {
        for (int i = 0; i < sort_names.size(); i++) {
            if (sort_names[i] == "Insertion Sort") continue;
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
        for (int i = 0; i < string_test_sizes.size(); i++) {
            std::cout << " | " << string_test_sizes[i];
        }
        std::cout << '\n';
        for (auto &g : small_test_sizes) {
            std::cout << g;
            for (auto &q :string_test_sizes) {
                std::cout << " | " << run_n_tests(g, 10, q, cmp) << " nanoseconds";
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
            if (sort_names[i] == "Insertion Sort") continue;
            chage_sort(sort_names[i]);
            get_cur_time_for_string_tests(cmp);
        }
    }


    int sort(std::vector<T> &vec) {
        return srt->sort(vec);
    }

    void print(std::vector<T> &vec) {
        return srt->print(vec);
    }

    long long get_n_operation_per_second() {
        std::vector <long long> pos(1e7, 0);
        std::vector <long long> temp(1e7, 0);
        srand(time(NULL));
        for (int i = 0; i < 1e7; i++) {
            pos[i] = rand() % (long long)1e7;
        }
        auto c_start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1e7; i++) {
            temp[pos[i]]++;
        }
        auto c_end = std::chrono::high_resolution_clock::now();
        return round(1e7 / ((long long) std::chrono::duration_cast<std::chrono::nanoseconds>(c_end - c_start).count()) * 1e9);
    }

    ~Benchmark(){
        delete srt;
    }
    
};