//
// Created by sulb49494 on 2023-05-25.
//

#ifndef CURVEQUANTIZATION_CQ_INTERFACE_H
#define CURVEQUANTIZATION_CQ_INTERFACE_H

#include "cq_basic_types.h"

namespace curve_quantization {

enum ChartMode {
  SPLIT = 1,
};

int CurveQuantization(ChartData &chart_data, const ChartMode &mode);

}

#endif //CURVEQUANTIZATION_CQ_INTERFACE_H
