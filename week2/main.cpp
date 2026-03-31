#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "include/bit_array.hpp"
#include "include/variable_length_bit_array.hpp"
#include <string_view>
#include <chrono>
#include <bitset>

uint64_t read_num(std::istream& is) {
    uint64_t num {0};
    is.read(reinterpret_cast<char*>(&num), sizeof(num));
    return num;
}

template <typename callable>
void read_input(std::istream& is, uint64_t n, callable func) {
    for (; n > 0; n--) {
        func(read_num(is));
    }
}


template <typename func>
void run_query(func query_func, std::istream& is, uint64_t n) {
    for (uint64_t i = 0; i < n; i++) {
        auto num = read_num(is);
        // std::cout << "querying num: " << num << ", answer is: ";
        auto result = query_func(num);
        std::cout << result << "\n";
    }
}

enum class Task {task1, task2, task3, task4};
template <typename Array>
void execute_program(Array& array, Task task, bool output_timings, std::istream& is, uint64_t n) {

    std::chrono::high_resolution_clock::time_point t1, t2;
    if (output_timings) {
        t1 = std::chrono::high_resolution_clock().now();
    } 
    read_input(is, n, [&array](uint64_t val) {return array.set(val);});
    if (output_timings) {
        t2 = std::chrono::high_resolution_clock().now();
        std::cerr << "Construction time: " <<
        std::chrono::duration_cast<std::chrono::microseconds>(t2-t1) << "\n";
    }
    
    
    if (output_timings) {
        t1 = std::chrono::high_resolution_clock().now();
    } 
    
    switch (task) {
        case Task::task1: 
        run_query([&array](uint64_t num){return array.get(num);}, is, n);
        break;
        
        case Task::task2: 
        // array.build_interval_sums();  // commented out cuz of task A23
        // run_query([&array](uint64_t num){return array.sum(num);}, is, n);
        break;
        
        case Task::task3:
        // array.build_search_indexes(); // commented out cuz of task A23
        // run_query([&array](uint64_t num){return array.location(num);}, is, n);
        break;

        case Task::task4:
        std::cout << array;
        std::cout << "right spot";
        run_query([&array](uint64_t num){return array.get(num);}, is, n);
    }
    if (output_timings) {
        t2 = std::chrono::high_resolution_clock().now();
        std::cerr << "query time: " <<
        std::chrono::duration_cast<std::chrono::microseconds>(t2-t1) << "\n";
    } 
}
    
    int main(int argc, const char* argv[]) {
    std::string filename;
    bool output_timings {false};
    Task task {Task::task1};
    for (int i = 1; i < argc; i++) {
        std::string_view arg {argv[i]};
        if (arg == "-t") {
            output_timings = true;
        } else if (arg == "-b") {
            task = Task::task1;
        } else if (arg == "-s") {
            task = Task::task2;
        } else if (arg == "-l") {
            task = Task::task3;
        } else if (arg == "-i") {
            task = Task::task4;
        } else {
            filename = argv[i];
        }
    }
    std::ifstream file;

    if (filename != "") {
        file.open(filename, std::ifstream::binary);
        if (!file) {
            std::cerr << "File ain't opening\n";
            return 1;
        }
    }

    std::istream& is = file.is_open() ? file : std::cin;
    auto n {read_num(is)};
    auto m {read_num(is)};
    
    if (task == Task::task4) {
        IntArray array {m, n};
        execute_program(array, task, output_timings, is, n);
    } else {
        BitArray array {m};
        execute_program(array, task, output_timings, is, n);
    }
    // BaseArray array = task == Task::task4 ? IntArray{m, n} : BitArray{m};


    return 0;
}
