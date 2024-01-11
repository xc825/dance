#ifndef DANCE_H
#define DANCE_H

#include <set>
#include <string>
#include <vector>
#include <dancer.h>



class Dance
{
    public:
    struct id_less {
        bool operator() (Dancer const &dancer1, Dancer const &dancer2) const;
    };
        struct partners_less {
        bool operator() (Dancer const &dancer1, Dancer const &dancer2) const {
            return dancer1.partners_num < dancer2.partners_num;
        }
    };

    std::set<Dancer, id_less> dancers; //sorted by id
    std::multiset<Dancer, partners_less> dancers_pnum; //sorted by number possible partners
    std::vector<std::pair<Dancer, Dancer>> pairs;
    Dance();
    ~Dance();
    int read_dancers(std::string const &file_name);
    int add_dancer(Dancer *dancer);
    int fill_dancers_pnum();
    int print_dancers();
    int print_dancers_pnum();
    int make_pairs();
    int print_pairs();
    int print_pairs(std::string fname);
};

#endif //DANCE_H
