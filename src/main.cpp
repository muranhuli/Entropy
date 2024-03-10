#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <map>
#include "data_structure.hpp"
#include "file_IO.hpp"
#include "similarity_mearsure.hpp"
#include "merge.hpp"
#include "basic_properity.hpp"
#include "algorithm_test.hpp"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "spdlog/sinks/basic_file_sink.h"
#include "tools.hpp"

int main(int argc, char *argv[])
{
    std::string folder = argv[1];
    std::string dataName = argv[2];
    std::string filename = folder + "/" + dataName;

    // Log initialization
    std::string logFileName = "logs/log_" + dataName + ".log";
    initLog(logFileName);

    std::vector<int> vertex;
    std::vector<std::vector<int>> hyperedge;
    read_hypergraph(filename, vertex, hyperedge);
    WeightedHypergraph hg1;
    hg1.InitialVertex(vertex);
    hg1.InitialHyperedge(hyperedge);
    WeightedHypergraph hg2;
    hg2.InitialVertex(vertex);
    hg2.InitialHyperedge(hyperedge);

    spdlog::info("The entropy of the original hypergraph is {}", hg2.ComputeHypergraphEntropy());
    spdlog::info("The size of vertices: {}, the size of hyperedges: {}", hg2.GetVertexList().size(), hg2.GetHyperedgeList().size());
    spdlog::info("The size of original hypergraph is {}", hg2.GetHypergraphSize());

    // mergeVertexWithMaxSimarity(hg2, 1000, 1);
    std::unordered_map<int, std::unordered_set<int>> idV = mergeVertex(hg2, 0.80, 100, 1);
    std::unordered_map<int, std::unordered_set<int>> idE = mergeHyperedge(hg2, 0.80, 2000, 1);

    spdlog::info("The entropy of the compressed hypergraph is {}", hg2.ComputeHypergraphEntropy());
    spdlog::info("The size of vertices: {}, the size of hyperedges: {}", hg2.GetVertexList().size(), hg2.GetHyperedgeList().size());
    spdlog::info("The size of compressed hypergraph is {}", hg2.GetHypergraphSize());
}