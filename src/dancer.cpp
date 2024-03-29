#include <string>
#include <set>
#include <support.h>


class Dancer {
    public:
    struct id_less {
        bool operator() (int id1, int id2) const {
            return id1 < id2;
        }
    };
    std::set<int, id_less> possible_partners_ids;
    int id;
    int partners_num;
    std::string gender;
    int attractiveness, acceptable_min, acceptable_max;


    Dancer ();
    Dancer (int attractiveness, int acceptable_min, int acceptable_max);
    ~Dancer();
    int get_attractiveness() const;
    int add_pos_partners_id(int id);
    int remove_pos_partners_id(int id);
    std::string to_string() const;

    friend class Dance;
};

Dancer::Dancer (int attractiveness, int acceptable_min, int acceptable_max) {
    this->attractiveness = attractiveness;
    this->acceptable_min = acceptable_min;
    this->acceptable_max = acceptable_max;
};

Dancer::Dancer () {
    PRINT_LOG(TRACE, "");
    partners_num = 0;
    attractiveness = 0;
    acceptable_min = 0;
    acceptable_max = 0;
}

Dancer::~Dancer() {
}

int Dancer::get_attractiveness() const {
    return this->attractiveness;
}

std::string Dancer::to_string() const{
    std::string str;

    str += "id:" + std::to_string(this->id);
    str += " gender:" + this->gender;
    str += " attr:" + std::to_string(this->attractiveness);
    str += " min:" + std::to_string(this->acceptable_min);
    str += " max:" + std::to_string(this->acceptable_max);
    str += " [";

    std::set<int>::iterator itr;
    for (itr = possible_partners_ids.begin(); itr != possible_partners_ids.end(); itr++) {
        str += std::to_string(*itr);
        if (itr != std::next(possible_partners_ids.end(), -1))
            str += ",";
    }

    str += "]";

    return str;
}

int Dancer::add_pos_partners_id(int id) {
    PRINT_LOG(TRACE, "add ", this->id, ".", id);
    if (possible_partners_ids.count(id) == 0) {
        partners_num++;
    }
    possible_partners_ids.insert(id);
    return 0;
 }

int Dancer::remove_pos_partners_id(int id) {
    PRINT_LOG(TRACE, "id:", this->id, ".", id);
    if (possible_partners_ids.count(id) > 0) {
        partners_num--;
    }
    possible_partners_ids.erase(id);
    return 0;
}
