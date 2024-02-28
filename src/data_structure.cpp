#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include "data_structure.hpp"

using namespace std;

/**
 * @brief hypergraph
 */
WeightedHypergraph::WeightedHypergraph()
{
}

void WeightedHypergraph::InitialVertex(vector<int> vertices)
{
    for (auto &i : vertices)
    {
        this->vertices.emplace(i, WeightedVertex(i, 1));
    }
}

void WeightedHypergraph::InitialHyperedge(vector<vector<int>> hyperedges)
{
    for (int i = 0; i < int(hyperedges.size()); i++)
    {
        for (auto &j : hyperedges[i])
        {
            this->adjacency_list[j].insert(i);
        }
        unordered_set<int> e(hyperedges[i].begin(), hyperedges[i].end());
        this->hyperedges.emplace(i, WeightedHyperedge(i, e, 1));
    }
}

// Merge similar sets of vertices.
void WeightedHypergraph::MergeVertex(vector<int> v)
{
    // Find hyperedges that need to merge vertices
    unordered_set<int> hyperedges_to_merge;
    for (auto &node : v)
    {
        for (auto &i : this->adjacency_list[node])
        {
            hyperedges_to_merge.insert(i);
        }
    }
    // Merge vertices in hyperedges
    for (auto &e : hyperedges_to_merge)
    {
        for (auto &node : v)
        {
            auto it = this->hyperedges[e].vertices.find(node);
            if (it != this->hyperedges[e].vertices.end())
                this->hyperedges[e].vertices.erase(node);
        }
        this->hyperedges[e].vertices.insert(v[0]);
    }

    // Calculate the weight of the merged vertex
    int weight = 0;
    for (auto &node : v)
    {
        weight += this->vertices[node].weight;
    }

    // Merge vertices
    for (int i = 1; i < int(v.size()); i++)
    {
        // Delete the vertex that has been merged and the adjacency hypergraph of this vertex

        this->adjacency_list[v[0]].merge(this->adjacency_list[v[i]]);
        this->vertices.erase(v[i]);
        this->adjacency_list.erase(v[i]);
    }
    this->vertices[v[0]].weight = weight;
}

// Merge similar hyperedges
void WeightedHypergraph::MergeHyperedge(vector<int> e)
{
    int weight = 0;
    for (auto &i : e)
    {
        weight += this->hyperedges[i].weight;
    }
    for (int i = 1; i < int(e.size()); i++)
    {
        for (auto &j : this->hyperedges[e[i]].vertices)
        {
            this->adjacency_list[j].erase(e[i]);
            this->adjacency_list[j].insert(e[0]);
            this->hyperedges[e[0]].vertices.insert(j);
        }
        this->hyperedges.erase(e[i]);
    }
    this->hyperedges[e[0]].weight = weight;
}

const WeightedHyperedge WeightedHypergraph::GetHyperedge(int id) const
{
    return this->hyperedges.at(id);
}

const WeightedVertex WeightedHypergraph::GetVertex(int id) const
{
    return this->vertices.at(id);
}

void WeightedHypergraph::Output()
{
    cout << "Vertices:" << endl;
    for (auto &i : this->vertices)
    {
        cout << i.first << " " << i.second.weight << endl;
    }
    cout << "adjacency_list:" << endl;
    for (auto &i : this->adjacency_list)
    {
        cout << i.first << " adj: ";
        for (auto &j : i.second)
        {
            cout << j << " ";
        }
        cout << endl;
    }

    cout << "Hyperedges:" << endl;
    for (auto &i : this->hyperedges)
    {
        cout << "ID: " << i.first << " Weight: " << i.second.weight << " Edge: ";
        for (auto &j : i.second.vertices)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

const int WeightedHypergraph::GetVertexDegree(int id) const
{
    int deg = 0;
    for (auto &e : this->adjacency_list.at(id))
    {
        deg += this->hyperedges.at(e).weight;
    }

    return deg;
}

const int WeightedHypergraph::GetHyperedgeCardi(int id) const
{
    int cardi = 0;
    for (const auto &node : this->hyperedges.at(id).vertices)
    {
        cardi += this->vertices.at(node).weight;
    }
    return cardi;
}

const unordered_set<int> WeightedHypergraph::GetAdjacencyList(int id) const
{
    return this->adjacency_list.at(id);
}

const vector<int> WeightedHypergraph::GetVertexList() const
{
    vector<int> vertex_list;
    for (auto &i : this->vertices)
    {
        vertex_list.push_back(i.second.id);
    }
    return vertex_list;
}

const vector<int> WeightedHypergraph::GetHyperedgeList() const
{
    vector<int> hyperedge_list;
    for (auto &i : this->hyperedges)
    {
        hyperedge_list.push_back(i.second.id);
    }
    return hyperedge_list;
}

const int WeightedHypergraph::GetHypergraphSize() const
{
    int size = 0;
    for (auto &edge: this->hyperedges)
    {
        size += int(edge.second.vertices.size());
    }
    return size;
}





const float WeightedHypergraph::ComputeHypergraphEntropy() const
{
    // 超边熵
    float HyperedgeEntropy = 0;
    int sum_vertex = 0;
    for (auto &info : this->vertices)
    {
        sum_vertex += info.second.weight;
    }

    for (auto &info : this->hyperedges)
    {
        int sum_edge_vertex = 0;
        sum_edge_vertex = this->GetHyperedgeCardi(info.second.id);
        // for (auto &node : info.second.vertices)
        // {
        //     sum_edge_vertex += this->vertices.at(node).weight;
        //     // sum_edge_vertex += this->GetVertexDegree(node);
        // }
        float p = float(sum_edge_vertex) / float(sum_vertex);
        HyperedgeEntropy += -p * log(p)*info.second.weight;
    }

    // 顶点熵
    float VertexEntropy = 0;
    int sum_edge = 0;
    for (auto &info : this->hyperedges)
    {
        sum_edge += info.second.weight;
    }
    for (auto &info : this->vertices)
    {
        int sum_vertex_edge = 0;
        sum_vertex_edge = this->GetVertexDegree(info.second.id);
        // for(auto &edge: this->adjacency_list.at(info.second.id))
        // {
        //     sum_vertex_edge += this->hyperedges.at(edge).weight;
        // }
        float p = float(sum_vertex_edge) / float(sum_edge);
        VertexEntropy += -p * log(p)*info.second.weight;
    }
    cout<< "HyperedgeEntropy: " << HyperedgeEntropy << " VertexEntropy: " << VertexEntropy << endl;
    return HyperedgeEntropy + VertexEntropy;
}