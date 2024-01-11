#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <support.h>
#include <dancer.h>
#include <unistd.h>


class Dance {
public:
    int id_next;
    struct id_less {
        bool operator() (Dancer const &dancer1, Dancer const &dancer2) const {
            return dancer1.id < dancer2.id;
        }
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
    int set_pairs();
    int print_dancers();
    int print_dancers_pnum();
    int make_pairs();
    int print_pairs();
    int print_pairs(std::string fname);
};

Dance::Dance() {
    this->id_next = 1;
};

Dance::~Dance() {
}

int Dance::read_dancers(std::string const &filename) {
    int dancers_count;
    std::string str;
    std::ifstream file;
    file.open(filename,  std::fstream::in);

    PRINT_LOG(TRACE, "Start reading data");

    if (!file.is_open())
    {
        PRINT_LOG(ERROR, "open " , filename ," failed");
        exit(1);
    }

    getline(file, str);
    dancers_count = stoi(str);

    PRINT_LOG(TRACE, "dancers: ", dancers_count);

    for (int i = 0; i < dancers_count; i++) {
        Dancer dancer;
        getline(file, str, ' ');
        dancer.gender = str;
        getline(file, str, ' ');
        dancer.attractiveness = stoi(str);
        getline(file, str, ' ');
        dancer.acceptable_min = stoi(str);
        getline(file, str);
        dancer.acceptable_max = stoi(str);
        dancer.id = id_next++;

        add_dancer(&dancer);
    }

    PRINT_LOG(TRACE, "exit function");
    return 0;
}

int Dance::print_dancers() {
    std::set<Dancer>::iterator itr;
    std::string str;

    PRINT_LOG(TRACE, "enter function");

    for (itr = dancers.begin(); itr != dancers.end(); itr++) {
        str = (*itr).to_string();
        log_print(TRACE, str);
    }
    return 0;
}

int Dance::add_dancer(Dancer *dancer) {
    std::set<Dancer>::iterator itr;

    PRINT_LOG(TRACE, "id:", dancer->id);

    for (itr = dancers.begin(); itr != dancers.end(); itr++) {
        if (((dancer->gender == "E" && (*itr).gender == "P") or (dancer->gender == "P" && (*itr).gender == "E"))
            && dancer->acceptable_min <= (*itr).attractiveness && dancer->acceptable_max >= (*itr).attractiveness
            && (*itr).acceptable_min <= dancer->attractiveness && (*itr).acceptable_max >= dancer->attractiveness) {

            dancer->add_pos_partners_id((*itr).id);

            Dancer d = *itr;
            dancers.erase(itr);
            d.add_pos_partners_id((*dancer).id);
            dancers.insert(d);

            PRINT_LOG(TRACE, "match: ", dancer->to_string() + " -> ", d.to_string());
        }
    }

    dancers.insert(*dancer);

    return 0;
}

int Dance::fill_dancers_pnum() {
    PRINT_LOG(TRACE, "Enter function");
    std::set<Dancer>::iterator itr;

    for (itr = dancers.begin(); itr != dancers.end(); itr++) {
        PRINT_LOG(TRACE, "id:", (*itr).id);
        dancers_pnum.insert(*itr);
    }

    PRINT_LOG(TRACE, "Exit function");
    return 0;
}

int Dance::print_dancers_pnum() {
    std::multiset<Dancer>::iterator itr;
    std::string str;

    PRINT_LOG(TRACE, "Enter function");

    for (itr = dancers_pnum.begin(); itr != dancers_pnum.end(); itr++) {
        str = (*itr).to_string();
        log_print(TRACE, str);
    }

    return 0;
}

int Dance::make_pairs() {
    Dancer d1, d2;
    PRINT_LOG(TRACE, "Enter function");
    std::multiset<Dancer>::iterator itr1;
    std::multiset<Dancer>::iterator itr2;
    std::set<int>::iterator posp_id;
    //std::set<int> *ids2;
    int found;

    for ( ; dancers_pnum.size() > 0 ; ) {
        itr1 = dancers_pnum.begin();
        found = 0;
        if ((*itr1).possible_partners_ids.size() == 0) { //if zero partners
            dancers_pnum.erase(itr1);
            continue;
        }

        d1 = (*itr1);
        log_print(TRACE, std::string("d1: ") + d1.to_string());
        dancers_pnum.erase(itr1);

        for (itr2 = dancers_pnum.begin(); itr2 != dancers_pnum.end(); itr2++) {
            log_print(TRACE, std::string("itr2:") +  std::to_string((*itr1).id));
            if (!found && (*itr2).possible_partners_ids.contains(d1.id)) {
                log_print(TRACE, std::string("d2: ") + d2.to_string());
                d2 = (*itr2);
                itr2 = dancers_pnum.erase(itr2);
                found = 1;
                break;
            }
        }

        //TODO fix possible partners id deleting from every dancer (test, if it fixed error)
        for (itr2 = dancers_pnum.begin(); itr2 != dancers_pnum.end(); ) {
            log_print(TRACE, std::string("list itr2 ids: ") + (*itr2).to_string());

            auto tmpitr = (++itr2)--;
            if ((*itr2).possible_partners_ids.contains(d1.id)
                || (*itr2).possible_partners_ids.contains(d2.id)) {
                log_print(TRACE, std::string("itr2 contains id:") + std::to_string(d1.id) + std::string(" or ") + std::to_string(d2.id));
                auto i = dancers_pnum.extract(itr2);
                Dancer& d = i.value();
                d.remove_pos_partners_id(d1.id);
                d.remove_pos_partners_id(d2.id);
                dancers_pnum.insert(std::move(d));
            }
            itr2 = tmpitr;
        }

        pairs.push_back(std::pair(d1, d2));
        log_print(TRACE, std::string("pair: ") + d1.to_string() + d2.to_string());
    }

    return 0;
}


int Dance::print_pairs() {
    log_print(TRACE, std::string("print_pairs()"));
    for (auto p : pairs) {
        log_print(TRACE, std::string("pair:"));
        log_print(TRACE, p.first.to_string());
        log_print(TRACE, p.second.to_string());
    }

    return 0;
}

int Dance::print_pairs(std::string fname) {
    std::ofstream file;

    PRINT_LOG(TRACE, std::string("print_pairs() to file"));

    file.open(fname,  std::fstream::out);

    if (!file.is_open())
    {
        PRINT_LOG(ERROR, "open " , fname ," failed");
        exit(1);
    }

    for (auto p : pairs) {
        file << "[" << p.first.id << " " << p.first.gender << " " << p.first.attractiveness << " "
            << p.first.acceptable_min << " " << p.first.acceptable_max << "]\t";
        file << "[" << p.second.id << " " << p.second.gender << " " << p.second.attractiveness << " "
            << p.second.acceptable_min << " " << p.second.acceptable_max << "]" << std::endl;
    }

    return 0;
}

//Update for C++17: that proposal has been accepted. Now you want to use extract():
/*
auto node = S.extract(vertex);
node.value().cost = 200;
S.insert(std::move(node));
*/
