#include <array>

/**
 * You can use this for programming task 3 of set 1 
*/

std::array<int, 5'000'000> container;

#pragma once

namespace pfp {

template <class dtype>
class fast_boi {
  int size {5'000'000};
  bool zero_in {false};
  public:

    void insert(dtype value) {
      if (value == 0) zero_in = true;
      int hash {value % size};
      while (container[hash]) {
          hash = hash < size ? hash + 1 : 0;
        }
        container[hash] = value;
        }

    int count(dtype value) const {
      if (value == 0) return zero_in ? 1 : 0;
        int hash {value % size};
        while (container[hash] != value) {
          if (container[hash] == 0) return 0;
          hash = hash < size ? hash + 1 : 0;
        }
        return 1;
    }
};
} // namespace pfp