#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include "../connection.hpp"

class Employee {

public:
    Employee() : id(0), last_name(""), first_name(""), patronymic(""), address(""), position_id(0), salary(0) {}

    Employee(int i, const std::string& ln, const std::string& fn, const std::string& p, const std::string& a, int pos, int s) 
        : id(i), last_name(ln), first_name(fn), patronymic(p), address(a), position_id(pos), salary(s) {}

    /// @brief добавляет в базу новую строчку с текущим name, в значение поля id записывается id новой строки
    void insert(SQLHDBC dbc);

    /// @brief изменяет значение name в строчке с текущим id
    void update(SQLHDBC dbc);

    /// @brief удаляет строчку с текущим id
    void remove(SQLHDBC dbc);

    static Employee find_by_id(SQLHDBC dbc, int id);

        int getId() const {
        return id;
    }

    std::string getLastName() const {
        return last_name;
    }

    void setLastName(const std::string& n) {
        last_name = n;
    }

    std::string getFirstName() const {
        return first_name;
    }

    void setFirstName(const std::string& n) {
        first_name = n;
    }

    std::string getPatronymic() const {
        return patronymic;
    }

    void setPatronymic(const std::string& p) {
        patronymic = p;
    }

    std::string getAddress() const {
        return address;
    }

    void setAddress(const std::string& a) {
        address = a;
    }

    int getPositionId() const {
        return position_id;
    }

    void setPositionId(int pos_id) {
        position_id = pos_id;
    }

    int getSalary() const {
        return salary;
    }

    void setSalary(int s) {
        salary = s;
    }

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
