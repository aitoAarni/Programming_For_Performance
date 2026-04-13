#pragma once
#include <cstdint>
#include <vector>
#include <iostream>

using ui = uint64_t;
using uc = uint8_t;

class StandardVByte {
    std::vector<uc> data;

public:
    StandardVByte(ui n) { data.reserve(std::min<size_t>(5*100'000'000, n * 2)); }

    void read_int(ui num) {
        while (num > 127) {
            data.push_back((num & 127) | 128);
            num >>= 7;
        }
        data.push_back(num & 127);
    }

    int get_blocks() {
        return data.size();
    }
    void output_ints(std::ostream& os) {
        ui accumulator = 0;
        ui shift_amount = 0;

        for (const uc& vbyte : data) {
            if (vbyte & 128) {
                accumulator |= (static_cast<ui>(vbyte & 127) << shift_amount);
                shift_amount += 7;
            } else {
                accumulator |= (static_cast<ui>(vbyte & 127) << shift_amount);
                os << accumulator << "\n";
                
                accumulator = 0;
                shift_amount = 0;
            }
        }
    }
};

class SortedVByte {
    ui n; 
    std::vector<uc> data;
    ui previous {0};
    public:
    SortedVByte(ui u_count) : n(u_count)  {data.reserve(std::min<size_t>(5*100'000'000, n * 10));}

    void read_int(ui num) {
        ui delta {num - previous};

         
        while (delta > 127) {
            data.push_back((delta & 127) | 128);
            delta >>= 7;
        }

        data.push_back(delta & 127);
        previous = num;
    }
    int get_blocks() {
        return data.size();
    }

void output_ints(std::ostream& os) {
        ui delta_accumulator = 0;
        ui shift_amount = 0;
        ui actual_value = 0;

        for (const uc& vbyte : data) {
            if (vbyte & 128) {
                delta_accumulator |= (static_cast<ui>(vbyte & 127) << shift_amount);
                shift_amount += 7;
            } else {
                delta_accumulator |= (static_cast<ui>(vbyte & 127) << shift_amount);
                
                actual_value += delta_accumulator;
                os << actual_value << "\n";

                delta_accumulator = 0;
                shift_amount = 0;
            }
        }
    }
};