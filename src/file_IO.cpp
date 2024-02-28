#ifndef FILE_READER_H
#define FILE_READER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>
#include "file_IO.hpp"
using namespace std;

/**
 * @brief Read hypergraphs, hyperedge sets, and vertex sets from files, conforming to the structure of a weighted hypergraph.
 */
void read_hypergraph(const string &filename, vector<int> &vertex, vector<vector<int>> &hyperedge)
{
    ifstream fin(filename, ios::in);
    if (!fin.is_open())
    {
        cerr << "Error opening file " << filename << endl;
        return;
    }
    int maxValue = INT_MIN;
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
            e.push_back(tmp);
            maxValue = max(maxValue, tmp);
        }
        if (e.size() == 1)
            continue;
        hyperedge.push_back(e);
    }

    vertex.resize(maxValue + 1);
    for (int i = 0; i <= maxValue; i++)
    {
        vertex[i] = i;
    }
}


#endif // FILE_READER_H