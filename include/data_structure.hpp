#ifndef DATA_STRUCTURE_HPP
#define DATA_STRUCTURE_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/**
 * @brief vertex in hypergraph
 */
struct WeightedVertex
{
    int id;
    int weight;
    WeightedVertex()
    {
    }
    WeightedVertex(int id, int weight) :
        id(id), weight(weight)
    {
    }
};

/**
 * @brief hyperedge in hypergraph
 */

struct WeightedHyperedge
{
    int id;
    std::unordered_set<int> vertices;
    int weight;
    WeightedHyperedge()
    {
    }
    WeightedHyperedge(int id, std::unordered_set<int> vertices, int weight) :
        id(id), vertices(vertices), weight(weight)
    {
    }
};

/**
 * @brief hypergraph
 */
class WeightedHypergraph
{
private:
    std::unordered_map<int, WeightedVertex> vertices;
    std::unordered_map<int, WeightedHyperedge> hyperedges;
    std::unordered_map<int, std::unordered_set<int>> adjacency_list;

public:
    WeightedHypergraph();
    void InitialVertex(std::vector<int> vertices);
    void InitialHyperedge(std::vector<std::vector<int>> hyperedges);
    void MergeVertex(std::vector<int> v);
    void MergeHyperedge(std::vector<int> e);
    // 获得指定ID的超边
    const WeightedHyperedge GetHyperedge(int id) const;
    // 获得指定ID的顶点
    const WeightedVertex GetVertex(int id) const;
    // 获得指定ID的顶点的度
    const int GetVertexDegree(int id) const;
    // 获得指定ID的超边的基数
    const int GetHyperedgeCardi(int id) const;
    // 获得指定ID的超边的邻接表
    const std::unordered_set<int> GetAdjacencyList(int id) const;
    // 获取顶点列表
    const std::vector<int> GetVertexList() const;
    // 获取超边列表
    const std::vector<int> GetHyperedgeList() const;
    // 计算超图的尺寸
    const int GetHypergraphSize() const;
    // 计算超图的熵
    const float ComputeHypergraphEntropy() const;
    void Output();
};

#endif // DATA_STRUCTURE_HPP