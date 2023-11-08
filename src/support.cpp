#include <iostream>
//#include <fstream>
#include <string>
#include <support.h>

int log_print(int log_lvl, std::string str) {
    if (LOG_LVL >= log_lvl) {
        std::cout << str << std::endl;
    }
    return 0;
}

int log_print(int log_lvl, char* str) {
    if (LOG_LVL >= log_lvl) {
        std::cout << str << std::endl;
    }
    return 0;
}
