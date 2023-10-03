#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "../connection.hpp"

class Employee {

public:
    Employee() : id(0), last_name(""), first_name(""), patronymic(""), address(""), position_id(0), salary(0) {}

    Employee(int i, const std::string& ln, const std::string& fn, const std::string& p, const std::string& a, int pos, int s) 
        : id(i), last_name(ln), first_name(fn), patronymic(p), address(a), position_id(pos), salary(s) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Employee find(SQLHDBC dbc, int id);

    static std::map<int, int> display_and_return(SQLHDBC dbc);
    static std::map<int, int> display_and_return_vets(SQLHDBC dbc);

    // getters
    int getId() const { return id; }
    std::string getLastName() const { return last_name; }
    std::string getFirstName() const { return first_name; }
    std::string getPatronymic() const { return patronymic; }
    std::string getAddress() const { return address; }
    int getPositionId() const { return position_id; }
    int getSalary() const { return salary; }

    // setters
    void setLastName(const std::string& n) { last_name = n; }
    void setFirstName(const std::string& n) { first_name = n; }
    void setPatronymic(const std::string& p) { patronymic = p; }
    void setAddress(const std::string& a) { address = a; }
    void setPositionId(int pos_id) { position_id = pos_id; }
    void setSalary(int s) { salary = s; }

private:
    int id;
    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string address;
    int position_id;
    int salary;

};


#endif // EMPLOYEE_HPP
