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
    std::mt19937 rnd;
    std::random_device randD;
    Sort<T> *srt;

public:
    Benchmark(std::string name) {
        rnd.seed(randD());
        small_test_sizes = {20, 50, 100, 500, 1000, 5000, 10000};
        big_test_sizes = {100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000};
        
        std::map<std::string, int> my_map;
        std::vector<std::string> names = {"Heap Sort", "Guaranteed Quick Sort", "Insertion Sort", "Quick Sort", "Merge Sort"};
        for (int i = 0; i < names.size(); i++) {
            my_map[names[i]] = i + 1;
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

    std::vector<T> make_random_test(int n, int str_size = -1){
        std::vector <T> test(n);

        if (std::is_same_v<T, int>) {
            std::uniform_int_distribution<int> gen(INT_MIN, INT_MAX);
            for (int i = 0; i < n; i++) {
                test[i] = gen(rnd);
            }
        }
        else if (std::is_same_v<T, long long>) {
            std::uniform_int_distribution<long long> gen(LONG_LONG_MIN, LONG_LONG_MAX);
            for (int i = 0; i < n; i++) {
                test[i] = gen(rnd);
            }
        }
        else if (std::is_same_v<T, std::string>) {
            std::uniform_int_distribution<int> gen(0, 25);
            for (int i = 0; i < n; i++) {
                test[i].resize(str_size);
                for (int j = 0; j < str_size; j++) {
                    test[i][j] = 'a' + gen(rnd);
                }
            }
        }
        
        return test;
    }

    auto run_1_test(int size, int str_size = -1) {
        std::vector <T> tmp = make_random_test(size, str_size);
        auto c_start = std::chrono::high_resolution_clock::now();
        if (!srt->sort(tmp)) {
            std::cout << "The array is sorted incorrectly\n";
            exit(-1);
        }
        auto c_end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(c_end - c_start).count();
    }

    auto run_n_int_tests(int size, int n, int str_size = -1) {
        auto time = 0;
        for (int i = 0; i < n; i++) {
            time += run_1_test(size, str_size);
        }
        time /= n;
    }

    int sort(std::vector<T> &vec) {
        return srt->sort(vec);
    }

    void print(std::vector<T> &vec) {
        return srt->print(vec);
    }

    ~Benchmark() = default;
    
};

