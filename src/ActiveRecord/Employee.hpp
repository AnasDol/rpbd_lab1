#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include <map>
#include <memory>
#include "../connection.hpp"

#include "Position.hpp"

class Employee {

public:
    Employee() : id(-1), last_name(""), first_name(""), patronymic(""), address(""), position(nullptr), salary(0) {}

    Employee(const std::string& ln, const std::string& fn, const std::string& p, const std::string& a, Position* pos, int s) 
        : id(-1), last_name(ln), first_name(fn), patronymic(p), address(a), position(pos), salary(s) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Employee* find(SQLHDBC dbc, int id);
    static std::map<int, int> get_values(SQLHDBC dbc);
    static std::map<int, int> get_values(SQLHDBC dbc, std::string attribute, std::string value);
    static void display(SQLHDBC dbc, std::map<int, int> record_map);

    // getters
    int getId() const { return id; }
    std::string getLastName() const { return last_name; }
    std::string getFirstName() const { return first_name; }
    std::string getPatronymic() const { return patronymic; }
    std::string getAddress() const { return address; }
    Position* getPosition() const { return position; }
    int getSalary() const { return salary; }

    // setters
    void setLastName(const std::string& n) { last_name = n; }
    void setFirstName(const std::string& n) { first_name = n; }
    void setPatronymic(const std::string& p) { patronymic = p; }
    void setAddress(const std::string& a) { address = a; }
    void setPosition(Position* newPosition) { position = newPosition; }
    void setSalary(int s) { salary = s; }

private:

    static inline const std::string table_name {"employees"};

    int id;
    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string address;
    Position* position;
    int salary;

};


#endif // EMPLOYEE_HPP
