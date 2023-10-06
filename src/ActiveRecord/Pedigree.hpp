#ifndef PEDIGREE_HPP
#define PEDIGREE_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "../connection.hpp"
#include "Animal.hpp"

class Pedigree {
public:

    Pedigree() : parent_id(0), child_id(0) {}

    Pedigree(int pid, int cid) 
        : parent_id(pid), child_id(cid) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Pedigree find(SQLHDBC dbc, int parent_id, int child_id);
    static std::map<int, pair> get_values(SQLHDBC dbc);
    static std::map<int, pair> get_values(SQLHDBC dbc, std::string attribute, std::string value);
    static void display(SQLHDBC dbc, std::map<int, pair> record_map);

    // getters
    int getParentId() const { return parent_id; }
    int getChildId() const { return child_id; }

    // setters
    void setParentId(int aid) { parent_id = aid; }
    void setChildId(int eid) { child_id = eid; }

private:

    static inline const std::string table_name {"pedigree"};

    int parent_id;
    int child_id;

};

#endif // PEDIGREE_HPP