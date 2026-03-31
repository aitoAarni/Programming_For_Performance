#pragma once
#include <cstdint>
#include <iostream>
#include <bitset>

using ul = uint64_t;


class IntArray {
    ul int_size; 
    ul* data;
    ul bit_index {0};
    ul array_index {0};
    ul bit_mask {0};
    
    public:
    IntArray(ul sz, ul n) : int_size(sz), data(new ul[(sz * n + 63) / 64]()) {
        for (int i = 0; i < int_size; i++) {
            bit_mask |= 1ul << i;
        }
    }
    
    void set(ul num) {
        data[array_index] |= num << bit_index;
        bit_index += int_size;
        if (bit_index >= 64) {
            bit_index -= 64;
            array_index++;
            data[array_index] |= num >> (int_size - bit_index);
        }


    }
    
    ul get(ul index) {
        ul value {0};
        ul arr_index {index*int_size/64};
        ul b_index {index*int_size % 64};

        value |= data[arr_index] >> b_index;
        long overflow = (b_index+int_size) - 64;
        if (overflow > 0) {
            value |= (data[arr_index+1] << (int_size - overflow));
        }
        
        return value&bit_mask;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const IntArray& array) {
        for (int i = 0; i < ((array.int_size * 10 + 63) / 64); i++) {
            os << "data[" << i << "]" << std::bitset<64>(array.data[i]) << "\n";
        }
        return os << "int_size: " << array.int_size << "\n";
    }
};