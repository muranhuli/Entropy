#include "tools.hpp"

void initLog(const std::string &logFileName, bool isWriteToConsole)
{
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    if (!isWriteToConsole)
    {
        consoleSink->set_level(spdlog::level::off);
    }
    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFileName, true);
    auto logger = std::make_shared<spdlog::logger>("main", std::initializer_list<spdlog::sink_ptr>{consoleSink, fileSink});
    logger->set_level(spdlog::level::info);
    logger->set_pattern("%v");
    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);
}