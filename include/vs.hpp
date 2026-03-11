#include <iostream>
#include <set>
/**
 * You can use this file for programmign task 1 of set 1.
*/

#pragma once

namespace pfp {

template <class dtype>
class vs {
  private:
    std::set<dtype> container;
  public:
    void insert(dtype val) {
      container.insert(val);
    }

    int count(dtype val) {
        auto result = container.count(val);
        return result;
    }
};

}  // namespace pfp
