#ifndef BREED_HPP
#define BREED_HPP

#include "../connection.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <windows.h>

class Breed {

  public:
    Breed() : id(0), name("") {}

    Breed(int i, const std::string &n) : id(i), name(n) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Breed find(SQLHDBC dbc, int id);
    static Breed find(SQLHDBC dbc, std::string attribute, std::string value);
    static std::map<int, int> display_and_return(SQLHDBC dbc);
    static std::map<int, int> display_and_return(SQLHDBC dbc, std::string attribute, std::string value);

    // getters
    int getId() const { return id; }
    std::string getName() const { return name; }

    // setters
    void setName(const std::string &n) { name = n; }

  private:
    int id;
    std::string name;
};

#endif // BREED_HPP
