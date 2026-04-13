#pragma once
#include <cstdint>
#include <deque>
#include <iostream>

using ui = uint64_t;

class GenStandardVByte {
protected:
    std::deque<ui> data;
    ui current_word {0};
    int current_bits {0};
    ui total_blocks {0};
    int k;
    ui payload_mask;
    ui continue_bit;

    void push_bits(ui val, int width) {
        current_word |= (val << current_bits);
        current_bits += width;
        if (current_bits >= 64) {
            data.push_back(current_word);
            current_bits -= 64;
            current_word = 0;
            if (current_bits > 0) {
                current_word = (val >> (width - current_bits));
            }
        }
    }

    ui read_bits(int width, size_t& deq_idx, int& bit_offset) {
        if (deq_idx >= data.size() && current_bits == 0) return 0;
        
        ui word = (deq_idx < data.size()) ? data[deq_idx] : current_word;
        ui result = word >> bit_offset;
        
        int bits_left_in_word = 64 - bit_offset;
        
        if (width <= bits_left_in_word) {
            bit_offset += width;
            if (bit_offset >= 64) {
                bit_offset -= 64;
                deq_idx++;
            }
        } else {
            deq_idx++;
            ui next_word = (deq_idx < data.size()) ? data[deq_idx] : current_word;
            int remaining_width = width - bits_left_in_word;
            result |= (next_word << bits_left_in_word);
            bit_offset = remaining_width;
        }
        
        return result & ((1ULL << width) - 1);
    }

public:
    GenStandardVByte(ui n, int k_val) : k(k_val) {
        payload_mask = (1ULL << k) - 1;
        continue_bit = (1ULL << k);
    }

    void read_int(ui num) {
        while (num > payload_mask) {
            ui block = (num & payload_mask) | continue_bit;
            push_bits(block, k + 1);
            num >>= k;
            total_blocks++;
        }
        push_bits(num & payload_mask, k + 1);
        total_blocks++;
    }

    ui get_blocks() {
        return total_blocks;
    }

    void output_ints(std::ostream& os) {
        ui accumulator = 0;
        ui shift_amount = 0;
        
        size_t read_idx = 0;
        int read_offset = 0;

        for (ui i = 0; i < total_blocks; i++) {
            ui block = read_bits(k + 1, read_idx, read_offset);
            
            if (block & continue_bit) {
                accumulator |= ((block & payload_mask) << shift_amount);
                shift_amount += k;
            } else {
                accumulator |= ((block & payload_mask) << shift_amount);
                os << accumulator << "\n";
                
                accumulator = 0;
                shift_amount = 0;
            }
        }
    }
};

class GenSortedVByte : public GenStandardVByte {
    ui previous {0};

public:
    GenSortedVByte(ui n, int k_val) : GenStandardVByte(n, k_val) {}

    void read_int(ui num) {
        ui delta = num - previous;
        GenStandardVByte::read_int(delta);
        previous = num;
    }

    void output_ints(std::ostream& os) {
        ui delta_accumulator = 0;
        ui shift_amount = 0;
        ui actual_value = 0;
        
        size_t read_idx = 0;
        int read_offset = 0;

        for (ui i = 0; i < total_blocks; i++) {
            ui block = read_bits(k + 1, read_idx, read_offset);
            
            if (block & continue_bit) {
                delta_accumulator |= ((block & payload_mask) << shift_amount);
                shift_amount += k;
            } else {
                delta_accumulator |= ((block & payload_mask) << shift_amount);
                
                actual_value += delta_accumulator;
                os << actual_value << "\n";
                
                delta_accumulator = 0;
                shift_amount = 0;
            }
        }
    }
};