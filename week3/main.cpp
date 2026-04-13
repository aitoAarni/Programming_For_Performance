#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "include/standard_vbyte.hpp"
#include "include/generilized_vbyte.hpp"
#include <string_view>
#include <chrono>


uint64_t read_num(std::istream& is) {
    uint64_t num {0};
    if (!is.read(reinterpret_cast<char*>(&num), sizeof(num))) return 0;
    return num;
}

int main(int argc, const char* argv[]) {
    std::string filename = "";
    bool is_sorted = false;
    int k_value = 7;

    for (int i = 1; i < argc; i++) {
        std::string_view arg {argv[i]};
        if (arg == "-s") {
            is_sorted = true;
        } else if (arg == "-k" && i + 1 < argc) {
            k_value = std::stoi(argv[i + 1]);
            i++;
        } else if (arg != "-t" && arg != "-b" && arg != "-l" && arg != "-i") {
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
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    auto n {read_num(is)};
    if (n == 0) return 0;
    

    if (is_sorted) {
        GenSortedVByte vbyte{n, k_value};
        for (uint64_t i = 0; i < n; i++) {
            vbyte.read_int(read_num(is));
        }
        std::cout << vbyte.get_blocks() << "\n";
        vbyte.output_ints(std::cout);
    } else {
        GenStandardVByte vbyte{n, k_value};
        for (uint64_t i = 0; i < n; i++) {
            vbyte.read_int(read_num(is));
        }
        std::cout << vbyte.get_blocks() << "\n";
        vbyte.output_ints(std::cout);
    }

    return 0;
}