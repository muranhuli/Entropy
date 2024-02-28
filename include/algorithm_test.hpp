#ifndef ALGORITHM_TEST_HPP
#define ALGORITHM_TEST_HPP
#include "data_structure.hpp"

double bfs(const WeightedHypergraph &hg1, int v_id);

double dfs(const WeightedHypergraph &hg1, int v_id);

double kcoredecomposition(const WeightedHypergraph &hg, unordered_map<int, int> &core);

#endif // ALGORITHM_TEST_HPP
