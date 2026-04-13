#include <iostream>
#include <cstdint>
#include <string_view>
#include "include/standard_vbyte.hpp"

uint64_t read_binary_number(std::istream& is) {
    uint64_t num; 
    is.read(reinterpret_cast<char*>(&num), sizeof(num));
    return num;
}



int main(int argc, const char* argv[]) {
    std::cout << "output test\n";
    std::cerr << "error test\n";
    uint64_t n = read_binary_number(std::cin);
    
    std::string_view arg {};
    if (argc > 1) {
        arg = argv[1];
    }
    if (arg == "-s") {
        SortedVByte vbyte{n};
        for (; n > 0; n--) {
            vbyte.read_int(read_binary_number(std::cin));
        }
        std::cerr << vbyte.get_blocks() << "\n";
        vbyte.output_ints(std::cout);
    } else {

        StandardVByte vbyte{n};
        for (; n > 0; n--) {
            vbyte.read_int(read_binary_number(std::cin));
        }
        std::cerr << vbyte.get_blocks() << "\n";
        vbyte.output_ints(std::cout);
    }
}