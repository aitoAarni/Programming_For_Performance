#include <vector>

/**
 * You can use this for programming task 2 of set 1 
*/

#pragma once

namespace pfp {

template <class dtype>
class bv {
  std::vector<bool> container;
  public:
    bv(dtype limit) : container(limit) {}

    void insert(dtype value) {
      container[value] = true;
    }

    int count(dtype value) const {
        return container[value] ? 1 : 0;
    }
};

} // namespace pfp