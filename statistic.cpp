#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <map>
#include <climits>
#include <algorithm>
using namespace std;

struct myCmp
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)
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

void getGraph(const string &filename, vector<vector<int>> &hyperEdge, unordered_map<int, vector<int>> &hyperNode)
{
    ifstream fin(filename, ios::in);
    int count = -1;
    while (true)
    {
        string str;
        getline(fin, str);
        if (str == "")
            break;
        istringstream ss(str);
        int tmp;
        vector<int> e;
        while (ss >> tmp)
        {
            if (find(e.begin(), e.end(), tmp) == e.end())
                e.push_back(tmp);
        }
        if (e.size() == 1)
            continue;
        count++;
        hyperEdge.push_back(e);
        for (auto &node : e)
            hyperNode[node].push_back(count);
    }
}

int main()
{
    string file = "NDCC NDCS TaAU MaAn WaTr ThAU ThMS CoMH CoGe CoDB";
    string filepath = "datasets/";
    istringstream ss(file);
    string str;
    ofstream fout("./results/datasetsInformation.txt");
    while (ss >> str)
    {
        string filename = filepath + str;
        vector<vector<int>> hyperEdge;
        unordered_map<int, vector<int>> hyperNode;
        getGraph(filename, hyperEdge, hyperNode);
        int deg_max = INT_MIN;
        int deg_count = 0;
        int cardi_max = INT_MIN;
        int cardi_count = 0;
        for (auto &it : hyperNode)
        {
            deg_max = max(deg_max, int(it.second.size()));
            deg_count += int(it.second.size());
        }
        for (auto &it : hyperEdge)
        {
            cardi_max = max(cardi_max, int(it.size()));
            cardi_count += int(it.size());
        }
        fout << str << " & " << hyperNode.size() << " & " << hyperEdge.size() << " & " << deg_max << " & "
             << deg_count / int(hyperNode.size()) << " & " << cardi_max << " & " << cardi_count / int(hyperEdge.size()) << " \\\\" << endl;
    }
    fout.close();
}