#include <iostream>
#include <algorithm>
#include <vector>
/**
 * You can use this file for programmign task 1 of set 1.
*/

#pragma once

namespace pfp {

template <class dtype>
class vs {
  private:
    std::vector<dtype> container;
    bool query_mode {true};


  public:
    vs() {
      container.reserve(10'000'000);
    }
    void insert(dtype val) {
      container.push_back(val);
      query_mode = true;
    }

    int count(dtype val) {
      if (query_mode) {
        std::sort(container.begin(),container.end());
        auto new_end = std::unique(container.begin(), container.end());
        container.erase(new_end, container.end());

        
        query_mode = false;
      }
      if (std::binary_search(container.begin(), container.end(), val)) {
        return 1;
    }
    return 0;
  }
};

}  // namespace pfp
