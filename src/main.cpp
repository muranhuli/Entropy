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
using namespace std;

int main(int argc, char *argv[])
{
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

    // hg.Output();
    cout << "the entropy of hypergraph is " << hg2.ComputeHypergraphEntropy() << endl;
    cout << "vertex size: " << hg2.GetVertexList().size() << " hyperedge size: " << hg2.GetHyperedgeList().size() << endl;
    cout << "the size of hypergraph is " << hg2.GetHypergraphSize() << endl;
    // cout << "the KL divergence of hypergraph is " << kl_divergence(hg1, hg2) << " JS divergence is " << js_divergence(hg1, hg2) << endl;

    // unordered_map<int, unordered_set<int>> idV = mergeVertex(hg2, 0.90, 400, 1);
    // mergeVertexWithMaxSimarity(hg2, 1000, 1);
    unordered_map<int, unordered_set<int>> idE = mergeHyperedge(hg2, 0.80, 2000, 1);

    // 记录hg和hg1的度分布，并存入文件
    // unordered_map<int, int> core1;
    // unordered_map<int, int> core2;

    // cout << "kcoredecomposition: " << kcoredecomposition(hg1, core1) << endl;
    // cout << "kcoredecomposition: " << kcoredecomposition(hg2, core2) << endl;
    // print_vector_to_file("./results/core_distribution1.txt", get_core_distribution(hg1, core1));
    // print_vector_to_file("./results/core_distribution2.txt", get_core_distribution(hg2, core2));
    // print_vector_to_file("./results/degree_distribution1.txt", get_degree_distribution(hg1));
    // print_vector_to_file("./results/degree_distribution2.txt", get_degree_distribution(hg2));
    // print_vector_to_file("./results/cardinality_distribution1.txt", get_cardi_distribution(hg1));
    // print_vector_to_file("./results/cardinality_distribution2.txt", get_cardi_distribution(hg2));
    // print_vector_to_file("./results/intersection_distribution1.txt", get_intersection_distribution(hg1));
    // print_vector_to_file("./results/intersection_distribution2.txt", get_intersection_distribution(hg2));
    // print_vector_to_file("./results/pairdeg_distribution1.txt", get_pairdeg_distribution(hg1));
    // print_vector_to_file("./results/pairdeg_distribution2.txt", get_pairdeg_distribution(hg2));

    cout << "*************************" << endl;
    cout << "the entropy of hypergraph is " << hg2.ComputeHypergraphEntropy() << endl;
    cout << "vertex size: " << hg2.GetVertexList().size() << " hyperedge size: " << hg2.GetHyperedgeList().size() << endl;
    cout << "the size of hypergraph is " << hg2.GetHypergraphSize() << endl;
    // cout << "the KL divergence of hypergraph is " << kl_divergence(hg1, hg2) << " JS divergence is " << js_divergence(hg1, hg2) << endl;
    // cout << "hamming distance of vertex is " << hamming_distance(hg1, hg2, idV, idE) << endl;
}