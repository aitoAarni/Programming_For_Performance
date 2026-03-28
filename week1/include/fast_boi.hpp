#include <array>

/**
 * You can use this for programming task 3 of set 1 
*/


constexpr int size {4'194'304};
std::array<int, size> container;

#pragma once

namespace pfp {

template <class dtype>
class fast_boi {
  bool zero_in {false};
  int mask {size - 1};
  public:

    void insert(dtype value) {
      if (value == 0) zero_in = true;
      int hash {value & mask};
      while (container[hash]) {
          hash = hash < size ? hash + 1 : 0;
        }
        container[hash] = value;
        }

    int count(dtype value) const {
      if (value == 0) return zero_in ? 1 : 0;
        int hash {value & mask};
        while (container[hash] != value) {
          if (container[hash] == 0) return 0;
          hash = hash < size ? hash + 1 : 0;
        }
        return 1;
    }
};
} // namespace pfp