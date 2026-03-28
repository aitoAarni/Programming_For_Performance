#pragma once
#include <cstdint>
#include <array>

class BitArray {
    uint64_t* data;

    public:
    BitArray(uint64_t m) : data(new uint64_t[(63+m)/64]()) {}
    ~BitArray() {
        delete[] data;
    }
    void set(uint64_t index) {
        // std::cout << "indx: " << index << "\n";
        auto array_index {index / 64};
        auto bit_index {index % 64};
        auto& number {data[array_index]};
        uint64_t modifier {uint64_t(1) << bit_index};
        if ((modifier & bit_index) == (uint64_t)(0)) {
            number += modifier;
        }
    }

    bool get(uint64_t index) {

        auto array_index {index / 64};
        auto bit_index {index % 64};

        auto& number {data[array_index]};
        uint64_t modifier {uint64_t(1) << bit_index};
        return (modifier & number) != 0;
    }
};