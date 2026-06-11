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
#include "algo.hpp"

int main(int argc, char *argv[])
{
    std::string folder = argv[1];
    std::string dataName = argv[2];
    std::string filename = folder + "/" + dataName;

    // Log initialization
    std::string logFileName = "logs/log_" + dataName + ".log";
    initLog(logFileName, false);

    // Initial hypergraph
    std::vector<int> vertex;
    std::vector<std::vector<int>> hyperedge;
    read_hypergraph(filename, vertex, hyperedge);
    WeightedHypergraph hg;
    hg.InitialVertex(vertex);
    hg.InitialHyperedge(hyperedge);

    spdlog::info("Entropy: {}, Vertex size: {}, Hyperedge size: {}, Size: {}", hg.ComputeHypergraphEntropy(),
                 hg.GetVertexList().size(), hg.GetHyperedgeList().size(), hg.GetHypergraphSize());

    outputProperty(hg);

    // algo
    double threshold = 0.1;
    PDD sim = std::make_pair(0.9, 0.8);
    PII cnt = std::make_pair(200, 2000);
    int seed = 1;
    EDHM_Sample(hg, threshold, sim, cnt, seed);

    spdlog::info("Entropy: {}, Vertex size: {}, Hyperedge size: {}, Size: {}", hg.ComputeHypergraphEntropy(),
                 hg.GetVertexList().size(), hg.GetHyperedgeList().size(), hg.GetHypergraphSize());
    outputProperty(hg);
}