#ifndef SUPPORT_H
#define SUPPORT_H

#include <string>
#include <iostream>

enum loglvl {
    FATAL   = 0,
    ERROR   = 1,
    WARN    = 2,
    INFO    = 3,
    DEBUG   = 4,
    TRACE   = 5
};

int log_print(int log_lvl, std::string str);

namespace logging
{
    template<typename... Args>
    void print_log(const char* file, int line, const char* func, int level, Args... args) {
        if (LOG_LVL >= level) {
            std::clog << "[" << file << ":" << line << ":" << func << "()] ";
            (std::clog << ... << args);
            std::clog << std::endl;
        }
    }
}

#define PRINT_LOG(LEVEL, ...)                                                           \
    do {                                                                                \
        logging::print_log(__FILE__, __LINE__, __func__, LEVEL, __VA_ARGS__);    \
    } while (0)


#endif //SUPPORT_H