#include <chrono> // include chrono header for timing
#include "algorithm_test.hpp"
#include <queue>
#include <stack>
#include <set>
#include <map>

using namespace std;

double bfs(const WeightedHypergraph &hg, int v_id)
{
    auto start = std::chrono::high_resolution_clock::now(); // start timer

    // function code here
    queue<int> v_queue;
    v_queue.push(v_id);
    unordered_set<int> visited;
    visited.emplace(v_id);
    while (!v_queue.empty())
    {
        int v = v_queue.front();
        v_queue.pop();
        unordered_set<int> adj = hg.GetAdjacencyList(v);
        for (auto e : adj)
        {
            WeightedHyperedge he = hg.GetHyperedge(e);
            for (auto v1 : he.vertices)
            {
                if (visited.find(v1) != visited.end())
                    continue;
                v_queue.push(v1);
                visited.emplace(v1);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();                              // end timer
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // calculate duration in nanoseconds
    return duration.count();                                                           // return duration in nanoseconds
}

double dfs(const WeightedHypergraph &hg, int v_id)
{
    auto start = std::chrono::high_resolution_clock::now(); // start timer

    // function code here
    stack<int> v_stack;
    v_stack.push(v_id);
    unordered_set<int> visited;
    visited.emplace(v_id);
    while (!v_stack.empty())
    {
        int v = v_stack.top();
        v_stack.pop();
        unordered_set<int> adj = hg.GetAdjacencyList(v);
        for (auto e : adj)
        {
            WeightedHyperedge he = hg.GetHyperedge(e);
            for (auto v1 : he.vertices)
            {
                if (visited.find(v1) != visited.end())
                    continue;
                v_stack.push(v1);
                visited.emplace(v1);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();                              // end timer
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // calculate duration in nanoseconds
    return duration.count();                                                           // return duration in nanoseconds
}


typedef pair<int, int> PII;
struct myCmp
{
    bool operator()(const PII &a, const PII &b) const
    {
        if (a.first == b.first)
            return false;
        else
        {
            if (a.second != b.second)
                return a.second < b.second;
            else
                return a.first < b.first;
        }
    }
};

double kcoredecomposition(const WeightedHypergraph &hg, unordered_map<int, int> &core)
{
    auto start = std::chrono::high_resolution_clock::now(); // start timer

    // function code here
    vector<int> v_list = hg.GetVertexList();
    unordered_map<int,int> v_degree;
    unordered_map<int,bool> v_visited;
    unordered_map<int,bool> e_visited;
    set<PII, myCmp> v_deg_set;
    for (auto v : v_list)
    {
        int degree = hg.GetVertexDegree(v);
        v_degree.emplace(v,degree);
        v_visited.emplace(v,false);
        v_deg_set.emplace(v,v_degree[v]);
    }

    int k = 0;
    while (!v_deg_set.empty())
    {
        PII p = *v_deg_set.begin();
        v_deg_set.erase(v_deg_set.begin());
        v_visited[p.first] = true;
        k = max(k,p.second);
        core[p.first] = k;
        v_visited[p.first] = true;
        unordered_set<int> adj = hg.GetAdjacencyList(p.first);
        for (auto e : adj)
        {
            if (e_visited[e])
                continue;
            e_visited[e] = true;
            WeightedHyperedge he = hg.GetHyperedge(e);
            for (auto v1 : he.vertices)
            {
                v_deg_set.erase(make_pair(v1,v_degree[v1]));
                v_degree[v1] -= he.weight;
                v_deg_set.emplace(v1,v_degree[v1]);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();                              // end timer
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start); // calculate duration in nanoseconds
    return duration.count();                                                           // return duration in nanoseconds
}