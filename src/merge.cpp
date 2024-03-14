#include <algorithm>
#include <vector>
#include "merge.hpp"
#include "spdlog/spdlog.h"

// 每次合并一个顶点和其邻居节点中最相似的顶点
void mergeVertexWithMaxSimarity(WeightedHypergraph &hg, int cnt, int seed)
{
    std::default_random_engine generator(seed);
    while (cnt--)
    {
        std::vector<int> vec = hg.GetVertexList();
        std::uniform_int_distribution<int> d1(0, int(vec.size()) - 1);
        int index = d1(generator);
        int v = vec[index];

        double max_sim = -1.0;
        int max_w = -1;
        std::unordered_set<int> adj = hg.GetAdjacencyList(v);
        for (auto &e : adj)
        {
            WeightedHyperedge he = hg.GetHyperedge(e);
            for (auto &v1 : he.vertices)
            {
                if (v1 == v)
                    continue;
                double sim = similarity_vertex(hg, v, v1);
                if (sim > max_sim)
                {
                    max_sim = sim;
                    max_w = v1;
                }
            }
        }
        if (max_sim < 0.9)
        {
            cnt++;
            continue;
        }
        std::vector<int> vv{v, max_w};
        hg.MergeVertex(vv);
    }
}

std::unordered_map<int, std::unordered_set<int>> singleVertexMerge(WeightedHypergraph &hg, float similarity, int seed)
{
    std::unordered_map<int, std::unordered_set<int>> ID_map;
    std::default_random_engine generator(seed);
    int count = 0;
    while (true)
    {
        if (count >= 10000)
        {
            spdlog::error("Vertex: The number of iterations exceeds 10000, sample failed");
            return ID_map;
        }

        std::vector<int> vec = hg.GetVertexList();
        std::uniform_int_distribution<int> d1(0, int(vec.size()) - 1);
        int index = d1(generator);
        int v = vec[index];

        std::unordered_set<int> adj = hg.GetAdjacencyList(v);
        std::uniform_int_distribution<int> d2(0, int(adj.size()) - 1);
        index = d2(generator);
        auto it = adj.begin();
        std::advance(it, index);
        int e = *it;
        WeightedHyperedge he = hg.GetHyperedge(e);

        // 随机获得该超边中的一个顶点
        std::uniform_int_distribution<int> d3(0, int(he.vertices.size()) - 1);
        index = d3(generator);
        it = he.vertices.begin();
        std::advance(it, index);
        int v1 = *it;

        if (v1 == v)
        {
            ++count;
            continue;
        }
        auto sim = similarity_vertex(hg, v, v1);
        if (sim > similarity)
        {
            std::vector<int> vv{v, v1};
            hg.MergeVertex(vv);
            // 记录合并的顶点
            // 判断v1是否再ID_map中
            if (ID_map.find(v1) != ID_map.end())
            {
                ID_map[v].insert(ID_map[v1].begin(), ID_map[v1].end());
                ID_map[v].insert(v1);
                ID_map.erase(v1);
            }
            else
            {
                ID_map[v].insert(v1);
            }
            return ID_map;
        }
        else
        {
            ++count;
            continue;
        }
    }
    return ID_map;
}

std::unordered_map<int, std::unordered_set<int>> singleHyperedgeMerge(WeightedHypergraph &hg, float similarity, int seed)
{
    std::unordered_map<int, std::unordered_set<int>> ID_map;
    std::default_random_engine generator(seed);
    int count = 0;
    while (true)
    {
        if (count >= 10000)
        {
            spdlog::error("Hyperedge: The number of iterations exceeds 10000, sample failed");
            return ID_map;
        }

        std::vector<int> vec = hg.GetHyperedgeList();
        std::uniform_int_distribution<int> d1(0, int(vec.size()) - 1);
        int index = d1(generator);
        int e = vec[index];

        std::unordered_set<int> vertices = hg.GetHyperedge(e).vertices;
        std::uniform_int_distribution<int> d2(0, int(vertices.size()) - 1);
        index = d2(generator);
        auto it = vertices.begin();
        std::advance(it, index);
        int v = *it;

        // 随机获得该顶点的邻接超边集合中的一条超边
        std::unordered_set<int> adj = hg.GetAdjacencyList(v);
        std::uniform_int_distribution<int> d3(0, int(adj.size()) - 1);
        index = d3(generator);
        it = adj.begin();
        std::advance(it, index);
        int e1 = *it;
        if (e1 == e)
        {
            ++count;
            continue;
        }

        auto sim = similarity_hyperedge(hg, e, e1);
        if (sim > similarity)
        {
            std::vector<int> ee{e, e1};

            hg.MergeHyperedge(ee);
            if (ID_map.find(e1) != ID_map.end())
            {
                ID_map[e].insert(ID_map[e1].begin(), ID_map[e1].end());
                ID_map[e].insert(e1);
                ID_map.erase(e1);
            }
            else
            {
                ID_map[e].insert(e1);
            }
            return ID_map;
        }
        else
        {
            ++count;
            continue;
        }
    }
    return ID_map;
}

bool compareByV2(const int &a, const int &b, const std::vector<int> &v2)
{
    return v2[a] > v2[b]; // Compare values in v2
}

std::vector<int> genCandidateVertex(WeightedHypergraph &hypergraph)
{
    std::vector<int> vertexList = hypergraph.GetVertexList();
    std::vector<int> degreeList;
    for (auto &i : vertexList)
    {
        degreeList.push_back(hypergraph.GetVertexDegree(i));
    }
    std::sort(vertexList.begin(), vertexList.end(), [&](const int &a, const int &b) {
        return compareByV2(a, b, degreeList);
    });
    return vertexList;
}

std::vector<int> genCandidateHyperedge(WeightedHypergraph &hypergraph)
{
    std::vector<int> hyperedgeList = hypergraph.GetHyperedgeList();
    std::vector<int> cardiList;
    for (auto &i : hyperedgeList)
    {
        cardiList.push_back(hypergraph.GetHyperedgeCardi(i));
    }
    std::sort(hyperedgeList.begin(), hyperedgeList.end(), [&](const int &a, const int &b) {
        return compareByV2(a, b, cardiList);
    });
    return hyperedgeList;
}

int randomSelect(std::unordered_set<int> &S, int seed)
{
    std::mt19937 gen(seed);

    // 随机选择一个顶点
    if (!S.empty())
    {
        std::uniform_int_distribution<int> distribution(0, S.size() - 1);
        auto it = S.begin();
        std::advance(it, distribution(gen));
        int randomVertex = *it;
        return randomVertex;
    }
    else
    {
        return -1;
    }
}
