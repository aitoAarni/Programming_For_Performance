#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
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
    void insert(dtype val) {
      container.push_back(val);
      query_mode = true;
    }

    int count(dtype val) {
      if (query_mode) {
        std::sort(container.begin(),container.end());
        query_mode = false;
      }
      int left {0};
      if (ontainer.empty()) return 0;
      int right {static_cast<int>(container.size())-1};
      int mid {0};
      while (left <= right) {
        mid = (right-left)/2 + left;
        if (container[mid] == val) return 1;
        if (container[mid] > val) {
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      } 
      return 0;
    }
};

}  // namespace pfp
