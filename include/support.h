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
//int log_print(int log_lvl, char* str);

#endif //SUPPORT_H