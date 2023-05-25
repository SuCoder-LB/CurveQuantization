//
// Created by sulb49494 on 2023-05-25.
//
#include "cq_interface.h"

#include <vector>

namespace curve_quantization {

int CurveQuantizationSplit(ChartData &chart_data) {
  for (auto &subside : chart_data.subsides) {
    std::vector<ChartNode> new_subside;
    new_subside.push_back(subside.vertices[0]);
    for (int i = 1; i < subside.vertices.size(); ++i) {
      new_subside.emplace_back((subside.vertices[i - 1].x + subside.vertices[i].x) / 2,
                               (subside.vertices[i - 1].y + subside.vertices[i].y) / 2,
                               (subside.vertices[i - 1].z + subside.vertices[i].z) / 2);
      new_subside.push_back(subside.vertices[i]);
    }
    subside.vertices = new_subside;
  }
  return 0;
}

int CurveQuantization(ChartData &chart_data, const ChartMode &mode) {
  if (mode == SPLIT) {
    return CurveQuantizationSplit(chart_data);
  } else {
    return -1;
  }

  return 0;
}

}