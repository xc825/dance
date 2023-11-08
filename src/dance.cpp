#include <set>
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
    std::set<Dancer, id_less> dancers;
    Dance();
    ~Dance();
    int read_dancers(std::string &file_name);
    int add_dancer(Dancer *dancer);
    int print_dancers();
};

Dance::Dance() {
    log_print(TRACE, std::string("~Dance() constructor"));
    this->id_next = 1;
};

Dance::~Dance() {
    log_print(TRACE, "~Dance() destructor");
}

int Dance::read_dancers(std::string &filename) {
    int dancers_count, attract, min, max;
    std::string str;
    std::ifstream file;
    Dancer dancer;
    file.open(filename);


    log_print(TRACE, "read_dancers()");

    getline(file, str);
    dancers_count = std::stoi(str);
    
    log_print(TRACE, "dancers: " + std::to_string(dancers_count));

    for (int i = 0; i < dancers_count; i++) {
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

        log_print(TRACE, "Add dancer: " + dancer.to_string() );
    }
    log_print(TRACE, "read_dancers(): end");
    return 0;
}

int Dance::print_dancers() {
    std::set<Dancer>::iterator itr;
    std::string str;

    for (itr = dancers.begin(); itr != dancers.end(); itr++) {
        str = (*itr).to_string();
        log_print(TRACE, str);
        //sleep(1);
    }
    /*std:for_each ( dance.dancers.cbegin(), dance.dancers.cend(), [](Dancer &dancer) {
        log_print(TRACE, dancer.to_string());
    });*/
    return 0;
}

int Dance::add_dancer(Dancer *dancer) {
    log_print(TRACE, std::string("add_dancer(") + std::to_string(dancer->id) + std::string(")"));
    std::set<Dancer>::iterator itr;

    for (itr = dancers.begin(); itr != dancers.end(); itr++) {
        if ((dancer->gender == "E" && (*itr).gender == "P" or dancer->gender == "P" && (*itr).gender == "E")
            && dancer->acceptable_min <= (*itr).attractiveness && dancer->acceptable_max >= (*itr).attractiveness
            && (*itr).acceptable_min <= dancer->attractiveness && (*itr).acceptable_max >= dancer->attractiveness) {
            dancer->add_pos_partners_id((*itr).id);

            Dancer d = *itr;
            dancers.erase(itr);
            d.add_pos_partners_id((*dancer).id);
            dancers.insert(d);

            log_print(TRACE, "match: "+ dancer->to_string() + " -> " + d.to_string());
        }
    }

    dancers.insert(*dancer);

    return 0;
}


//Update for C++17: that proposal has been accepted. Now you want to use extract():
/*
auto node = S.extract(vertex);
node.value().cost = 200;
S.insert(std::move(node));
*/
