#pragma once
#include <cstdint>
#include <iostream>
#include <bitset>

using ul = uint64_t;


class IntArray {
    ul int_size; 
    ul* data;
    // ul index {0};
    ul bit_index {0};
    ul array_index {0};
    
    public:
    IntArray(ul sz, ul n) : int_size(sz), data(new ul[(sz * n + 63) / 64]()) {}
    
    void set(ul num) {
        ul offset {bit_index};
        std::cout << "num: " << std::bitset<10>(num) << "\n";
        int i {0};
        for (; i < int_size; i++) {
            data[array_index] |= ((ul)1 << bit_index++) & (num << offset);
            if ((bit_index) >= 64) {
                bit_index = 0;
                array_index++;
                i++;
                offset = i;
                for (; i < int_size; i++) {
                    data[array_index] |= ((ul)1 << bit_index++) & (num >> (offset));
                }
                break;
            }
        


        }
    }
    
    ul get(ul index) {
        return index;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const IntArray& array) {
        for (int i = 0; i < ((array.int_size * 10 + 63) / 64); i++) {
            os << "data[" << i << "]" << std::bitset<64>(array.data[i]) << "\n";
        }
        return os << "int_size: " << array.int_size << "\n";
    }
};