#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "include/bit_array.hpp"
#include <string_view>
#include <chrono>

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



int main(int argc, const char* argv[]) {
    std::string filename;
    bool output_timings {false};
    int task_number {1};
    for (int i = 1; i < argc; i++) {
        std::string_view arg {argv[i]};
        if (arg == "-t") {
            output_timings = true;
        } else if (arg == "-b") {
            task_number = 1;
        } else {
            filename = argv[i];
        }
    }
    std::ifstream file;

    if (filename != "") {
        file.open(filename, std::ifstream::binary);
        if (!file) {
            std::cerr << "file ain't opening\n";
            return 1;
        }
    }

    std::istream& is = file.is_open() ? file : std::cin;
    auto n {read_num(is)};
    auto m {read_num(is)};
    BitArray bit_arr {m};
    std::chrono::high_resolution_clock::time_point t1, t2;
    if (output_timings) {
        t1 = std::chrono::high_resolution_clock().now();
    } 
    read_input(is, n, [&bit_arr](uint64_t val) {return bit_arr.set(val);});
    if (output_timings) {
        t2 = std::chrono::high_resolution_clock().now();
        std::cerr << "Construction time: " <<
        std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1) << "\n";
    }

    // std::cout << "num: " << bit_arr.get_num(0) << "\n";
    
    if (output_timings) {
        t1 = std::chrono::high_resolution_clock().now();
    } 
    for (uint64_t i = 0; i < n; i++) {
        auto num = read_num(is);
        auto result = bit_arr.get(num);
        std::cout << result << "\n";
        
    }
    if (output_timings) {
        t2 = std::chrono::high_resolution_clock().now();
        std::cerr << "query time: " <<
        std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1) << "\n";
    } 
    if (file.is_open()) file.close();

    return 0;
}