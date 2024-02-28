#ifndef FILE_READER_HPP
#define FILE_READER_HPP
#include <string>
#include <vector>
#include <fstream>
using namespace std;

/**
 * @brief Read hypergraphs, hyperedge sets, and vertex sets from files, conforming to the structure of a weighted hypergraph.
*/
void read_hypergraph(const string &filename, vector<int> &vertex, vector<vector<int>> &hyperedge);

template <class T> void print_vector_to_file(const string &filename, const vector<T> &vec)
{
    ofstream fout(filename, ios::out);
    if (!fout.is_open())
    {
        cerr << "Error opening file " << filename << endl;
        return;
    }
    for (size_t i = 0; i < vec.size(); i++)
    {
        fout << vec[i] << endl;
    }
    fout.close();
}


#endif // FILE_READER_HPP