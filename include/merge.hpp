#ifndef MERGE_HPP
#define MERGE_HPP
#include <random>
#include "data_structure.hpp"
#include "similarity_mearsure.hpp"

// Generate a set of candidate vertices for selecting vertices to merge
std::vector<int> genCandidateVertex(WeightedHypergraph &hypergraph);

std::vector<int> genCandidateHyperedge(WeightedHypergraph &hypergraph);

int randomSelect(std::unordered_set<int> &S, int seed);

void mergeVertexWithMaxSimarity(WeightedHypergraph &hg, int cnt, int seed);

std::unordered_map<int, std::unordered_set<int>> singleVertexMerge(WeightedHypergraph &hg, float similarity, int seed = 1);

std::unordered_map<int, std::unordered_set<int>> singleHyperedgeMerge(WeightedHypergraph &hg, float similarity, int seed = 1);

#endif