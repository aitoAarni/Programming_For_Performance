#pragma once
#include <iostream>
#include <cstdint>

using ui = uint64_t;

class BitArray {
    ui* data;
    ui size;
    ui* interval_sums;

    void build_interval_sums() {
        interval_sums = new ui[size];
        if (size > 0) interval_sums[0] = __builtin_popcountl(data[0]);
        for (int i {0}; i < size; i++) {
            interval_sums[i] = interval_sums[i-1] + __builtin_popcountl(data[i]);
        }
    }

    public:
    BitArray(ui m) : data(new ui[(63+m)/64]()), size((63+m)/64), interval_sums(nullptr) {}
    ~BitArray() {
        delete[] data;
    }

    void set(ui index) {
        auto array_index {index / 64};
        auto bit_index {index % 64};
        auto& number {data[array_index]};
        ui modifier {ui(1) << (bit_index )};
        number |=  modifier;
    }



    bool get(ui index) {

        auto array_index {index / 64};
        auto bit_index {index % 64};

        auto& number {data[array_index]};
        ui modifier {ui(1) << (bit_index )};
        return (modifier & number) != 0;
    }

    


    ui sum(ui index) {
        if (interval_sums == nullptr) {
            build_interval_sums();
        }
        return index;
    }
};