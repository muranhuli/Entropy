#include <cmath>
#include <vector>
#include <map>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "basic_properity.hpp"

static std::vector<int> intersection(const std::unordered_set<int> &set1, const std::unordered_set<int> &set2)
{
    std::vector<int> result;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(result));
    return result;
}

std::vector<double> get_core_distribution(const WeightedHypergraph &hg, std::unordered_map<int, int> &core)
{
    int max_core = INT_MIN;
    int sum = 0;
    for (auto info : core)
    {
        max_core = std::max(max_core, info.second);
        sum += hg.GetVertex(info.first).weight;
    }
    std::vector<double> core_dist(max_core + 1, 0);

    for (auto info : core)
    {
        core_dist[info.second] += hg.GetVertex(info.first).weight;
    }
    for (size_t i = 0; i < core_dist.size(); ++i)
    {
        core_dist[i] /= double(sum);
    }
    return core_dist;
}

std::vector<double> get_degree_distribution(const WeightedHypergraph &hg)
{
    std::vector<int> vec = hg.GetVertexList();
    std::map<int, int> degree_count;
    int max_degree = INT_MIN;
    int sum = 0;
    for (auto &i : vec)
    {
        int d = hg.GetVertexDegree(i);
        degree_count[d] += hg.GetVertex(i).weight;
        // 计算最大度，统计所有顶点数目
        max_degree = std::max(max_degree, d);
        sum += hg.GetVertex(i).weight;
    }
    std::vector<double> dist(max_degree + 1, 0.0);
    for (auto &i : degree_count)
    {
        dist[i.first] = double(i.second) / double(sum);
    }
    return dist;
}

std::vector<double> get_cardi_distribution(const WeightedHypergraph &hg)
{
    std::vector<int> vec = hg.GetHyperedgeList();
    std::map<int, int> cardi_count;
    int max_cardi = INT_MIN;
    int sum = 0;
    for (auto &i : vec)
    {
        int c = hg.GetHyperedgeCardi(i);
        cardi_count[c] += hg.GetHyperedge(i).weight;
        // 计算最大度，统计所有顶点数目
        max_cardi = std::max(max_cardi, c);
        sum += hg.GetHyperedge(i).weight;
    }
    std::vector<double> dist(max_cardi + 1, 0.0);
    for (auto &i : cardi_count)
    {
        dist[i.first] = double(i.second) / double(sum);
    }
    return dist;
}

std::vector<double> get_intersection_distribution(const WeightedHypergraph &hg)
{
    std::vector<int> vec = hg.GetHyperedgeList();
    std::map<int, int> intersection_count;
    int max_intersection = INT_MIN;
    int sum = 0;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        for (size_t j = i + 1; j < vec.size(); ++j)
        {
            WeightedHyperedge e1 = hg.GetHyperedge(vec[i]);
            WeightedHyperedge e2 = hg.GetHyperedge(vec[j]);
            std::vector<int> intsect = intersection(e1.vertices, e2.vertices);
            int cnt = 0;
            for (auto &k : intsect)
            {
                cnt += hg.GetVertex(k).weight;
            }
            intersection_count[cnt] += e1.weight * e2.weight;
            max_intersection = std::max(max_intersection, cnt);
            sum += e1.weight * e2.weight;
        }
    }
    std::vector<double> dist(max_intersection + 1, 0.0);
    for (auto &i : intersection_count)
    {
        dist[i.first] = double(i.second) / double(sum);
    }
    return dist;
}

std::vector<double> get_pairdeg_distribution(const WeightedHypergraph &hg)
{
    std::vector<int> vec = hg.GetVertexList();
    std::map<int, int> pairdeg_count;
    int max_pairdeg = INT_MIN;
    int sum = 0;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        for (size_t j = i + 1; j < vec.size(); ++j)
        {
            std::unordered_set<int> v1 = hg.GetAdjacencyList(vec[i]);
            std::unordered_set<int> v2 = hg.GetAdjacencyList(vec[j]);
            int cnt = 0;
            // v1和v2的交集
            std::vector<int> intsect = intersection(v1, v2);
            for (auto &k : intsect)
            {
                cnt += hg.GetHyperedge(k).weight;
            }
            pairdeg_count[cnt] += hg.GetVertex(vec[i]).weight * hg.GetVertex(vec[j]).weight;
            max_pairdeg = std::max(max_pairdeg, cnt);
            sum += hg.GetVertex(vec[i]).weight * hg.GetVertex(vec[j]).weight;
        }
    }
    std::vector<double> dist(max_pairdeg + 1, 0.0);
    for (auto &i : pairdeg_count)
    {
        dist[i.first] = double(i.second) / double(sum);
    }
    return dist;
}

double kl_divergence(const std::vector<double> &dist1, const std::vector<double> &dist2)
{
    double kl_div = 0.0;
    for (size_t i = 0; i < dist1.size(); ++i)
    {
        if (dist1[i] == 0)
        {
            continue;
        }
        double q = (dist2[i] == 0) ? 1e-9 : dist2[i];
        kl_div += dist1[i] * std::log(dist1[i] / q);
    }
    return kl_div;
}

double js_divergence(const std::vector<double> &dist1, const std::vector<double> &dist2)
{
    double js_div = 0.0;
    std::vector<double> avg_dist(dist1.size(), 0.0);
    for (size_t i = 0; i < dist1.size(); ++i)
    {
        avg_dist[i] = 0.5 * (dist1[i] + dist2[i]);
    }
    js_div = 0.5 * kl_divergence(dist1, avg_dist) + 0.5 * kl_divergence(dist2, avg_dist);
    return js_div;
}

double kl_divergence(const WeightedHypergraph &hg1, const WeightedHypergraph &hg2)
{
    std::vector<double> dist1 = get_degree_distribution(hg1);
    std::vector<double> dist2 = get_degree_distribution(hg2);
    return kl_divergence(dist1, dist2);
}

double js_divergence(const WeightedHypergraph &hg1, const WeightedHypergraph &hg2)
{
    std::vector<double> dist1 = get_degree_distribution(hg1);
    std::vector<double> dist2 = get_degree_distribution(hg2);
    return js_divergence(dist1, dist2);
}

int hamming_distance(const WeightedHypergraph &hg1, const WeightedHypergraph &hg2, std::unordered_map<int, std::unordered_set<int>> &idV, std::unordered_map<int, std::unordered_set<int>> &idE)
{
    int hamming_distance = 0;
    std::vector<int> hyperedge_list = hg2.GetHyperedgeList();
    for (auto e : hyperedge_list)
    {
        // 统计融合后的超边含有多少顶点
        std::unordered_set<int> merge_hyperedge = hg2.GetHyperedge(e).vertices;
        std::vector<int> vertex_fusion;
        for (auto v : merge_hyperedge)
        {
            // 统计融合后的顶点包含了哪些顶点，并将其展开
            if (idV.find(v) != idV.end())
            {
                for (auto i : idV[v])
                {
                    vertex_fusion.push_back(i);
                }
            }
        }
        // vertex_fusion插入进merge_hyperedge
        for (auto i : vertex_fusion)
        {
            merge_hyperedge.insert(i);
        }

        // 统计超边e详单与多少超边
        std::vector<int> origin_hyperedge;
        origin_hyperedge.push_back(e);
        if (idE.find(e) != idE.end())
        {
            for (auto i : idE[e])
            {
                origin_hyperedge.push_back(i);
            }
        }
        for (auto i : origin_hyperedge)
        {
            std::unordered_set<int> origin = hg1.GetHyperedge(i).vertices;
            // 计算hamming distance
            int count = 0;

            for (auto i : origin)
            {
                if (merge_hyperedge.find(i) != merge_hyperedge.end())
                {
                    count++;
                }
            }
            int hamming_dist = origin.size() + merge_hyperedge.size() - 2 * count;
            hamming_distance += hamming_dist;
        }
    }
    return hamming_distance;
}