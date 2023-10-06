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

class Participation {
public:

    Participation() : animal_id(0), exhibition_id(0), reward("") {}

    Participation(int aid, int eid, const std::string& r) 
        : animal_id(aid), exhibition_id(eid), reward(r) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Participation find(SQLHDBC dbc, int animal_id, int exhibition_id);
    static std::map<int, pair> get_values(SQLHDBC dbc);
    static std::map<int, pair> get_values(SQLHDBC dbc, std::string attribute, std::string value);
    static void display(SQLHDBC dbc, std::map<int, pair> record_map);

    // getters
    int getAnimalId() const { return animal_id; }
    int getExhibitionId() const { return exhibition_id; }
    std::string getReward() const { return reward; }

    // setters
    void setAnimalId(int aid) { animal_id = aid; }
    void setExhibitionId(int eid) { exhibition_id = eid; }
    void setReward(const std::string& r) { reward = r; }

private:

    static inline const std::string table_name {"participations"};

    int animal_id;
    int exhibition_id;
    std::string reward;
};

#endif // PARTICIPATION_HPP