#ifndef POSITION_HPP
#define POSITION_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "../connection.hpp"

class Position {

public:
    Position() : id(0), name("") {}

    Position(int i, const std::string& n) : id(i), name(n) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Position find(SQLHDBC dbc, int id);
    static Position find(SQLHDBC dbc, std::string attribute, std::string value);
    static std::map<int, int> display_and_return(SQLHDBC dbc);
    static std::map<int, int> display_and_return(SQLHDBC dbc, std::string attribute, std::string value);

    // getters
    int getId() const { return id; }
    std::string getName() const { return name; }

    // setters
    void setName(const std::string& n) { name = n; }

private:
    int id;
    std::string name;

};


#endif // POSITION_HPP
