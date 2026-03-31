#pragma once
#include <iostream>
#include <cstdint>
#include <iostream>

using ul = uint64_t;


class BitArray {
    ul* data;
    ul size;
    long count_1_bits {0};
    unsigned int* interval_sums;
    unsigned int* search_indexes = nullptr;
    
    
    public:
    BitArray(ul m) : data(new ul[(63+m)/64]()), size((63+m)/64), interval_sums(nullptr) {}
    ~BitArray() {
        delete[] data;
        delete[] interval_sums;
        delete[] search_indexes;
    }
    
    void build_search_indexes() {
        search_indexes = new unsigned int[count_1_bits+1];
        interval_sums = new unsigned int[size];
        ul bit_sum {0};
        unsigned int search_index {1};
        for (unsigned int index {0}; index < size; index++) {
            interval_sums[index] = bit_sum;
            bit_sum += __builtin_popcountl(data[index]);
            
            while (bit_sum >= search_index) {
                search_indexes[search_index] = index;
                ++search_index;
            }
        }
    }
    
    void build_interval_sums() {
        interval_sums = new unsigned int[size-1];
        if (size > 1) interval_sums[0] = __builtin_popcountl(data[0]);
        for (ul i {1}; i < (size-1); i++) {
            interval_sums[i] = interval_sums[i-1] + __builtin_popcountl(data[i]);
        }
    }
    void set(ul index) {
        auto array_index {index / 64};
        auto bit_index {index % 64};
        auto& number {data[array_index]};
        ul bit_mask {ul(1) << (bit_index )};
        if ((number & bit_mask) == 0) {
            count_1_bits++;
        }
        number |=  bit_mask;
    }
    
    
    bool get(ul index) {
        
        auto array_index {index / 64};
        auto bit_index {index % 64};
        
        auto& number {data[array_index]};
        ul bit_mask {ul(1) << (bit_index )};
        return (bit_mask & number) != 0;
    }
    
    
    
    
    ul sum(ul idx) {
        if (idx == 0) return 0;
        ul index = idx - 1;
        ul array_index {index / 64};
        ul bit_index {index % 64};
        
        ul return_val {};
        if (idx > 64) {
            return_val = interval_sums[array_index-1];
        }
        
        if (__builtin_ctzl(data[array_index]) > bit_index) {
            return return_val;
        } else if (64 - __builtin_clzl(data[array_index] - 1) <= bit_index) {
            return return_val + static_cast<ul>(__builtin_popcountl(data[array_index]));
        } else {
            ul shift {63-bit_index};
            ul shifted_bits = data[array_index] << shift;
            return return_val + static_cast<ul>(__builtin_popcountl(shifted_bits));
        }
    }
    
    friend std::ostream& operator<<(std::ostream& os, const BitArray& array) {
        return os;
    } 
    ul get_data() {
        return data[0];
    }

    int location(ul sum) {
        if (sum == 0) {
            return -1;
        }
        unsigned int array_index {search_indexes[sum]};
        ul right_chunck {data[array_index]};
        unsigned int bit_count {interval_sums[array_index]};
        auto index {array_index * 64};
        ul bit_index {0};
        while (bit_count != sum) {
            if (((static_cast<ul>(1)<<bit_index) & right_chunck) != 0) {
                bit_count++; 
            }
            bit_index++;
        }
        return index + bit_index;

    }
};
