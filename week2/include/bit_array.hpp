#pragma once
#include <iostream>
#include <cstdint>

using ul = uint64_t;

class BitArray {
    ul* data;
    ul size;
    ul* interval_sums;

    void build_interval_sums() {
        interval_sums = new ul[size-1];
        if (size > 1) interval_sums[0] = __builtin_popcountl(data[0]);
        for (ul i {1}; i < (size-1); i++) {
            interval_sums[i] = interval_sums[i-1] + __builtin_popcountl(data[i]);
        }
    }

    public:
    BitArray(ul m) : data(new ul[(63+m)/64]()), size((63+m)/64), interval_sums(nullptr) {}
    ~BitArray() {
        delete[] data;
        delete[] interval_sums;
    }

    void set(ul index) {
        auto array_index {index / 64};
        auto bit_index {index % 64};
        auto& number {data[array_index]};
        ul modifier {ul(1) << (bit_index )};
        number |=  modifier;
    }



    bool get(ul index) {

        auto array_index {index / 64};
        auto bit_index {index % 64};

        auto& number {data[array_index]};
        ul modifier {ul(1) << (bit_index )};
        return (modifier & number) != 0;
    }

    


    ul sum(ul idx) {
        ul index = idx - 1;
        if (interval_sums == nullptr) {
            build_interval_sums();
        }
        ul array_index {index / 64};
        ul bit_index {index % 64};

        ul return_val {};
        if (index > 63) {
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
        // return return_val;
    }
};