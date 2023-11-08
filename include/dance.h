#ifndef DANCE_H
#define DANCE_H

#include <set>
#include <string>
#include <dancer.h>



class Dance
{
    public:
    struct id_less {
        bool operator() (Dancer const &dancer1, Dancer const &dancer2) const;
    };
    std::set<Dancer, id_less> dancers;
    Dance();
    ~Dance();
    int read_dancers(std::string &file_name);
    int add_dancer(Dancer *dancer);
    int print_dancers();
};

#endif //DANCE_H
