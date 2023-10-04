#ifndef EXHIBITION_HPP
#define EXHIBITION_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "../connection.hpp"

class Exhibition {

public:
    Exhibition() : id(0), name(""), address(""), day(0), month(0), year(0) {}

    Exhibition(int i, const std::string& n, const std::string& a, int d, int m, int y) 
        : id(i), name(n), address(a), day(d), month(m), year(y) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Exhibition find(SQLHDBC dbc, int id);
    static std::map<int, int> get_values(SQLHDBC dbc);
    static std::map<int, int> get_values(SQLHDBC dbc, std::string attribute, std::string value);
    static void display(SQLHDBC dbc, std::map<int, int> record_map);

    // getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    std::string getDate() const;

    // setters
    void setName(const std::string& n) { name = n; }
    void setAddress(const std::string& a) { address = a; }
    void setDay(int day) { this->day = day; }
    void setMonth(int month) { this->month = month; }
    void setYear(int year) { this->year = year; }

private:

    static inline const std::string table_name {"exhibitions"};

    int id;
    std::string name;
    std::string address;
    int day;
    int month;
    int year;

};


#endif // EXHIBITION_HPP
