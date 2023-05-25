//
// Created by sulb49494 on 2023-05-25.
//

#ifndef CURVEQUANTIZATION_CQ_BASIC_TYPES_H
#define CURVEQUANTIZATION_CQ_BASIC_TYPES_H

#include <cstdio>
#include <vector>

namespace curve_quantization {

struct ChartNode {
  double x;
  double y;
  double z;
  size_t id;

  ChartNode() { x = y = z = 0, id = -1; }
  ChartNode(double x, double y, double z) : x(x), y(y), z(z), id(-1) {}
  ChartNode(double x, double y, double z, size_t id) : x(x), y(y), z(z), id(id) {}
};

struct ChartSubside {
  std::vector<ChartNode> vertices;  //分区线的离散点
  size_t start;                     //起始点编号
  size_t end;                       //终止点编号
  ChartSubside() { start = end = -1; }
};

struct ChartSide {
  std::vector<size_t> subsides;          //相关的子边编号
  std::vector<bool> reversed_subside;     //该子边在这条边上是否逆转
};

struct Chart {
  std::vector<ChartSide> sides;     //分区边结构
};

struct ChartData {
  std::vector<ChartNode> nodes;      //所有分区节点信息
  std::vector<ChartSubside> subsides;     //所有分区子边
  std::vector<Chart> charts;              //所有分区信息
};
}


#endif //CURVEQUANTIZATION_CQ_BASIC_TYPES_H
