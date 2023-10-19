#ifndef PARTICIPATION_HPP
#define PARTICIPATION_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "../connection.hpp"

#include "Animal.hpp"
#include "Exhibition.hpp"

class Participation {
public:

    Participation() : animal(nullptr), exhibition(nullptr), reward("") {}

    Participation(Animal* animal, Exhibition* exhibition, const std::string& r) 
        : animal(animal), exhibition(exhibition), reward(r) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Participation* find(SQLHDBC dbc, int animal_id, int exhibition_id);
    static std::map<int, pair> get_values(SQLHDBC dbc);
    static std::map<int, pair> get_values(SQLHDBC dbc, std::string attribute, std::string value);
    static void display(SQLHDBC dbc, std::map<int, pair> record_map);

    // getters
    Animal* getAnimal() const { return animal; }
    Exhibition* getExhibition() const { return exhibition; }
    std::string getReward() const { return reward; }

    // setters
    void setAnimal(Animal* an) { animal = an; }
    void setExhibition(Exhibition* ex) { exhibition = ex; }
    void setReward(const std::string& r) { reward = r; }

    ~Participation() {
        delete animal;
        delete exhibition;
    }

private:

    static inline const std::string table_name {"participations"};

    Animal* animal;
    Exhibition* exhibition;
    std::string reward;
};

#endif // PARTICIPATION_HPP