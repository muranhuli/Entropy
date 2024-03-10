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
#include "spdlog/sinks/basic_file_sink.h"
using namespace std;

int main(int argc, char *argv[])
{
    std::string filename = "logs/logfile.txt";
    auto logger = spdlog::basic_logger_mt("basic_logger", filename);
    logger->set_level(spdlog::level::info);

    spdlog::info("Welcome to spdlog!");
    string filename = argv[1];
    vector<int> vertex;
    vector<vector<int>> hyperedge;
    read_hypergraph(filename, vertex, hyperedge);
    WeightedHypergraph hg1;
    hg1.InitialVertex(vertex);
    hg1.InitialHyperedge(hyperedge);
    WeightedHypergraph hg2;
    hg2.InitialVertex(vertex);
    hg2.InitialHyperedge(hyperedge);

    cout << "the entropy of hypergraph is " << hg2.ComputeHypergraphEntropy() << endl;
    cout << "vertex size: " << hg2.GetVertexList().size() << " hyperedge size: " << hg2.GetHyperedgeList().size() << endl;
    cout << "the size of hypergraph is " << hg2.GetHypergraphSize() << endl;
    // cout << "the KL divergence of hypergraph is " << kl_divergence(hg1, hg2) << " JS divergence is " << js_divergence(hg1, hg2) << endl;

    // unordered_map<int, unordered_set<int>> idV = mergeVertex(hg2, 0.90, 400, 1);
    // mergeVertexWithMaxSimarity(hg2, 1000, 1);
    unordered_map<int, unordered_set<int>> idE = mergeHyperedge(hg2, 0.80, 2000, 1);

    cout << "*************************" << endl;
    cout << "the entropy of hypergraph is " << hg2.ComputeHypergraphEntropy() << endl;
    cout << "vertex size: " << hg2.GetVertexList().size() << " hyperedge size: " << hg2.GetHyperedgeList().size() << endl;
    cout << "the size of hypergraph is " << hg2.GetHypergraphSize() << endl;
}