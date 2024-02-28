#ifndef SIMILARITY_MEARSURE_HPP 
#define SIMILARITY_MEARSURE_HPP

#include "data_structure.hpp"

float similarity_hyperedge(const WeightedHypergraph& hg, int a, int b);

float similarity_vertex(const WeightedHypergraph& hg, int a , int b);

#endif // SIMILARITY_MEARSURE_HPP