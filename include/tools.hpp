#pragma once
#include <string>
#include <sstream>
#include <unordered_set>
#include "spdlog/spdlog.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "spdlog/sinks/basic_file_sink.h"

void initLog(const std::string &logFileName, bool isWriteToConsole = true);

template <typename Container, typename Element>
bool in(const Container &container, const Element &element)
{
    return container.find(element) != container.end();
}

class Time
{
private:
    std::string functionName; // 函数名
    std::string timeUnit;     // 时间单位
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::string externalLoggerName; // 外部日志器名

public:
    Time(const std::string &name, const std::string &unit = "ms", const std::string &logger = "") :
        functionName(name), timeUnit(unit), externalLoggerName(logger)
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Time()
    {
        end = std::chrono::high_resolution_clock::now();
        long long elapsed = 0;

        if (timeUnit == "s")
        {
            elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        }
        else if (timeUnit == "ms")
        {
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }
        else if (timeUnit == "us")
        {
            elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        else if (timeUnit == "ns")
        {
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        // 构建日志消息
        std::string logMessage = fmt::format("[{}] execution takes {} {}", functionName, elapsed, timeUnit);

        // 如果提供了日志器选项，则使用它；否则，使用spdlog::info
        if (externalLoggerName != "")
        {
            auto externalLogger = spdlog::get(externalLoggerName);
            externalLogger->info(logMessage);
        }
        else
        {
            spdlog::info(logMessage);
        }
    }
};

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
