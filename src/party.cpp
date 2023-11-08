#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <dance.h>
#include <dancer.h>
#include <support.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
        return  0;

    std::string fname(argv[1]);
    Dance dance;

    log_print(TRACE, std::string(argv[0]));
    log_print(TRACE, std::string(argv[1]));

    log_print(TRACE, "Start");

    dance.read_dancers(fname);
    dance.print_dancers();

    return 0;
}