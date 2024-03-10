#pragma once
#include <string>
#include <sstream>
#include <unordered_set>
#include "spdlog/spdlog.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "spdlog/sinks/basic_file_sink.h"

void initLog(const std::string &logFileName, bool isWriteToConsole = true);

template <typename T>
std::string toString(const std::vector<T> &container, const std::string &separator = " ")
{
    std::ostringstream oss;
    for (auto it = container.begin(); it != container.end();)
    {
        oss << *it;
        if (++it != container.end())
        {
            oss << separator;
        }
    }
    return oss.str();
}

template <typename T>
std::string toString(const std::unordered_set<T> &container, const std::string &separator = " ")
{
    std::ostringstream oss;
    for (auto it = container.begin(); it != container.end();)
    {
        oss << *it;
        if (++it != container.end())
        {
            oss << separator;
        }
    }
    return oss.str();
}