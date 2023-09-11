#include "exercise_81.h"
#include <algorithm>
#include <vector>
#include <numeric>


float MSE(const std::vector<float>& ground_truth,
          const std::vector<float>& prediction) {
    unsigned long N = ground_truth.size();
    std::vector<float> tmpVec(N);
    std::transform(ground_truth.begin(), ground_truth.end(),
                   prediction.begin(),
                   tmpVec.begin(),
                   [](const float a, const float b){return (a-b)*(a-b);});
    return std::accumulate(tmpVec.begin(), tmpVec.end(), 0.0f) 
         / static_cast<float>(N);
}

float MAE(const std::vector<float>& ground_truth,
          const std::vector<float>& prediction) {
    unsigned long N = ground_truth.size();
    std::vector<float> tmpVec(N);
    std::transform(ground_truth.begin(), ground_truth.end(),
                   prediction.begin(),
                   tmpVec.begin(),
                   [](const float a, const float b){return std::abs(a-b);});
    return std::accumulate(tmpVec.begin(), tmpVec.end(), 0.0f) 
         / static_cast<float>(N);
}

std::vector<int> range(int start, int end) {
  if(start >= end) return std::vector<int>(0);
  std::vector<int> tmpVec(end - start);
  std::generate(tmpVec.begin(), tmpVec.end(),
      [start]() mutable {return start++;});
  return tmpVec;
}

