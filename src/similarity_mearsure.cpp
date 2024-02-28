#include "similarity_mearsure.hpp"
#include "data_structure.hpp"

static std::unordered_set<int> intersection(const std::unordered_set<int> &set1, const std::unordered_set<int> &set2)
{
    std::unordered_set<int> intersect;
    for (const auto &elem : set1)
    {
        if (set2.find(elem) != set2.end())
        {
            intersect.insert(elem);
        }
    }
    return intersect;
}

static std::unordered_set<int> unionSets(const std::unordered_set<int> &set1, const std::unordered_set<int> &set2)
{
    std::unordered_set<int> unionSet = set1;
    for (const auto &elem : set2)
    {
        unionSet.insert(elem);
    }
    return unionSet;
}

static std::unordered_set<int> difference(const std::unordered_set<int> &A, const std::unordered_set<int> &B)
{
    std::unordered_set<int> diff = A;
    for (const auto &elem : B)
    {
        diff.erase(elem);
    }
    return diff;
}

float similarity_hyperedge(const WeightedHypergraph &hg, int a, int b)
{
    float similarity = 0;
    WeightedHyperedge e0 = hg.GetHyperedge(a);
    WeightedHyperedge e1 = hg.GetHyperedge(b);
    similarity = float(intersection(e0.vertices, e1.vertices).size()) / float(unionSets(e0.vertices, e1.vertices).size());
    float punish = 0;
    for (const auto &node : difference(e0.vertices, e1.vertices))
    {
        int deg = hg.GetVertexDegree(node);
        punish += float(deg) / float((deg + hg.GetHyperedge(b).weight));
    }
    for (const auto &node : difference(e1.vertices, e0.vertices))
    {
        int deg = hg.GetVertexDegree(node);
        punish += float(deg) / float((deg + hg.GetHyperedge(a).weight));
    }
    if (difference(e0.vertices, e1.vertices).size() + difference(e1.vertices, e0.vertices).size() == 0)
        punish = 1;
    else
        punish /= difference(e0.vertices, e1.vertices).size() + difference(e1.vertices, e0.vertices).size();
    return similarity * punish;
}

float similarity_vertex(const WeightedHypergraph &hg, int a, int b)
{
    float similarity = 0;
    WeightedVertex v0 = hg.GetVertex(a);
    WeightedVertex v1 = hg.GetVertex(b);
    unordered_set<int> adj_a = hg.GetAdjacencyList(a);
    unordered_set<int> adj_b = hg.GetAdjacencyList(b);

    similarity = float(intersection(adj_a, adj_b).size()) / float(intersection(adj_b, adj_a).size());
    float punish = 0;
    for (const auto &e : difference(adj_a, adj_b))
    {
        int cardi = hg.GetHyperedgeCardi(e);
        punish += float(cardi) / float((cardi + v1.weight));
    }
    for (const auto &e : difference(adj_b, adj_a))
    {
        int cardi = hg.GetHyperedgeCardi(e);
        punish += float(cardi) / float((cardi + v0.weight));
    }
    if (difference(adj_a, adj_b).size() + difference(adj_b, adj_a).size() == 0)
        punish = 1;
    else
        punish /= difference(adj_a, adj_b).size() + difference(adj_b, adj_a).size();
    return similarity * punish;
}