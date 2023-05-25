//
// Created by sulb49494 on 2023-05-25.
//
#include "cq_interface.h"

#include <string>
#include <map>

void LoadPatches(const std::string &filename, curve_quantization::ChartData &chart_data) {
  FILE *fp = fopen(filename.c_str(), "r");
  if (fp == nullptr)return;
  int n_nodes, n_subsides, n_patches;
  fscanf(fp, "%d%d%d\n", &n_nodes, &n_subsides, &n_patches);
  std::map<size_t, int> node_mp;
  for (int i = 0; i < n_nodes; ++i) {
    curve_quantization::ChartNode node;

    fscanf(fp, "%zd%lf%lf%lf", &node.id, &node.x, &node.y, &node.z);
    node_mp[node.id] = i;

    chart_data.nodes.emplace_back(node);
  }

  for (int i = 0; i < n_subsides; ++i) {
    curve_quantization::ChartSubside subside;
    int n_mid;
    fscanf(fp, "%zd%zd%d", &subside.start, &subside.end, &n_mid);
    subside.vertices.push_back(chart_data.nodes[node_mp[subside.start]]);
    for (int j = 0; j < n_mid; ++j) {
      curve_quantization::ChartNode node;
      fscanf(fp, "%lf%lf%lf", &node.x, &node.y, &node.z);
      subside.vertices.emplace_back(node);
    }
    subside.vertices.push_back(chart_data.nodes[node_mp[subside.end]]);
    chart_data.subsides.emplace_back(subside);
  }

  for (int i = 0; i < n_patches; ++i) {
    curve_quantization::Chart chart;
    int n_sides;
    fscanf(fp, "%d", &n_sides);
    chart.sides.resize(n_sides);
    for (int j = 0; j < n_sides; ++j) {
      int n_subsides_j;
      fscanf(fp, "%d", &n_subsides_j);
      chart.sides[j].subsides.resize(n_subsides_j);
      chart.sides[j].reversed_subside.resize(n_subsides_j);
    }
    for (int j = 0; j < n_sides; ++j) {
      for (int k = 0; k < chart.sides[j].subsides.size(); ++k) {
        int subside_id, reversed;
        fscanf(fp, "%d%d", &subside_id, &reversed);
        chart.sides[j].subsides[k] = subside_id;
        chart.sides[j].reversed_subside[k] = reversed;
      }
    }
    chart_data.charts.emplace_back(chart);
  }
  fclose(fp);
}



void SavePatches(const std::string &filename, curve_quantization::ChartData &chart_data) {
  FILE *fp = fopen(filename.c_str(), "w");
  if (fp == nullptr)return;
  fprintf(fp, "%zu %zu %zu\n", chart_data.nodes.size(), chart_data.subsides.size(), chart_data.charts.size());

  for (auto &node : chart_data.nodes) {
    fprintf(fp, "%zd %lf %lf %lf\n", node.id, node.x, node.y, node.z);
  }

  for (auto subside : chart_data.subsides) {
    int n_mid = static_cast<int>(subside.vertices.size()) - 2;
    fprintf(fp, "%zd %zd %zu\n", subside.start, subside.end, subside.vertices.size() - 2);

    for (int j = 0; j < n_mid; ++j) {
      auto &node = subside.vertices[j + 1];
      fprintf(fp, "%lf% lf %lf\n", node.x, node.y, node.z);
    }
  }

  for (auto &chart : chart_data.charts) {
    fprintf(fp, "%zu ", chart.sides.size());
    for (auto &side : chart.sides) {
      fprintf(fp, "%zu ", side.subsides.size());
    }
    fprintf(fp, "\n");
    for (auto &side : chart.sides) {
      for (int k = 0; k < side.subsides.size(); ++k) {
        fprintf(fp, "%llu %d\n", side.subsides[k], static_cast<int>(side.reversed_subside[k]));
      }
    }
  }
  fclose(fp);
}


int main(){


  std::string in_file = "../gear.chart";
  std::string out_file = "../gear_cq.chart";

  curve_quantization::ChartData chart_data;

  LoadPatches(in_file,chart_data);

  curve_quantization::CurveQuantization(chart_data,curve_quantization::ChartMode::SPLIT);

  SavePatches(out_file,chart_data);

  return 0;
}
