#ifndef DANCER_H
#define DANCER_H

#include <set>


class Dancer {
public:
    struct id_less {
        bool operator() (int id1, int id2) const;
    };
    std::set<int, id_less> possible_partners_ids;
    int id;
    std::string gender;
    int attractiveness, acceptable_min, acceptable_max;

    Dancer (int attractiveness, int acceptable_min, int acceptable_max);
    Dancer ();
    ~Dancer();
    int get_attractiveness() const;
    int add_pos_partners_id(int id);
    int remove_pos_partners_id(int id);
    std::string to_string() const;
    
    friend class Dance;
};

#endif //DANCER_H
