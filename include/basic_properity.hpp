#ifndef BASIC_PROPERTY_HPP
#define BASIC_PROPERTY_HPP

#include <vector>
#include "data_structure.hpp"

std::vector<double> get_degree_distribution(const WeightedHypergraph &hg);

std::vector<double> get_cardi_distribution(const WeightedHypergraph &hg);

std::vector<double> get_intersection_distribution(const WeightedHypergraph &hg);

std::vector<double> get_pairdeg_distribution(const WeightedHypergraph &hg);

std::vector<double> get_core_distribution(const WeightedHypergraph &hg, std::unordered_map<int, int> &core);

double kl_divergence(const WeightedHypergraph &hg1, const WeightedHypergraph &hg2);

double js_divergence(const WeightedHypergraph &hg1, const WeightedHypergraph &hg2);

int hamming_distance(const WeightedHypergraph &hg1, const WeightedHypergraph &hg2,
                     std::unordered_map<int, std::unordered_set<int>> &id1, std::unordered_map<int, std::unordered_set<int>> &id2);

#endif // BASIC_PROPERTY_HPP