#ifndef FILE_READER_HPP
#define FILE_READER_HPP
#include <string>
#include <vector>
#include <fstream>
#include "tools.hpp"
#include <spdlog/spdlog.h>

/**
 * @brief Read hypergraphs, hyperedge sets, and vertex sets from files, conforming to the structure of a weighted hypergraph.
 */
void read_hypergraph(const std::string &filename, std::vector<int> &vertex, std::vector<std::vector<int>> &hyperedge);

template <class T>
void print_vector_to_file(const std::string &filename, const std::vector<T> &vec)
{
    spdlog::info("print vector to file {}", filename);
    spdlog::info("{}", toString(vec));
}

#endif // FILE_READER_HPP