#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <random>
#include <support.h>
#include <unistd.h>
#include <dance.h>
#include <dancer.h>
#include <cxxopts.hpp>

int generate(std::string fname, int num);

int main(int argc, char* argv[])
{
    int n;
    std::string fname;
    cxxopts::Options options("party",   "Make pairs of dancers\n"
                                        "party --input <input_file> --output <output_file>"
                                        "party --generate <number> --output <output_file>"
                                        "party --help"
                            );

    PRINT_LOG(TRACE, "Start");

    options.add_options()
        ("g,generate", "Number of dancers", cxxopts::value<int>())
        ("i,input", "Input file name", cxxopts::value<std::string>())
        ("o,output", "Output file name", cxxopts::value<std::string>())
        ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
        ("h,help", "Print usage")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    else if (result.count("generate")
        && ( (n = result["generate"].as<int>()) > 0)
        && (result.count("output"))) {
        fname = result["output"].as<std::string>();
        generate(fname, n);
    }
    else if (result.count("input") > 0 && result.count("output") > 0)
    {
        Dance dance;
        dance.read_dancers(result["input"].as<std::string>());
        dance.fill_dancers_pnum();
        dance.print_dancers();
        dance.print_dancers_pnum();
        dance.make_pairs();
        dance.print_pairs(result["output"].as<std::string>());
    }

    return 0;
}

int generate(std::string filename, int n) {
    std::ofstream file;
    int attr, P_num, accpt_rng, accpt_min, accpt_max;

    PRINT_LOG(TRACE, "enter function");

    file.open(filename,  std::fstream::out);
    if (!file.is_open())
    {
        PRINT_LOG(ERROR, "open " , filename ," failed");
        exit(1);
    }

    file << n << std::endl;
    P_num = n / 2;
    for (int i = 0; i < n; i++) {
        file << ((i < P_num) ? "P " : "E ");
        attr = rand() % n + 1;
        accpt_rng = rand() % n;
        accpt_min = rand() % n;
        accpt_max = accpt_min + accpt_rng;
        file << attr << " " << accpt_min << " " << accpt_max << " " << std::endl;
    }

    file.close();

    return 0;
}
