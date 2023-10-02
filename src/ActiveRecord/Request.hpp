#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "../connection.hpp"

class Request {

public:
    Request() : id(0), client_id(0), breed_id(0), gender(""), day(0), month(0), year(0) {}

    Request(int id, int client_id, int breed_id, std::string gender, int day, int month, int year)
        : id(id), client_id(client_id), breed_id(breed_id), gender(gender), day(day), month(month), year(year) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Request find(SQLHDBC dbc, std::string attribute, std::string value);
    static std::map<int, int> display_and_return(SQLHDBC dbc);
    static std::map<int, int> display_and_return(SQLHDBC dbc, std::string attribute, std::string value);

    // getters
    int getId() const { return id; }
    int getClientId() const { return client_id; }
    int getBreedId() const { return breed_id; }
    std::string getGender() const { return gender; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    std::string getDate() const;

    // setters
    void setClientId(int client_id) { this->client_id = client_id; }
    void setBreedId(int breed_id) { this->breed_id = breed_id; }
    void setGender(const std::string &gender) { this->gender = gender; }
    void setDay(int day) { this->day = day; }
    void setMonth(int month) { this->month = month; }
    void setYear(int year) { this->year = year; }

private:
    int id;
    int client_id;
    int breed_id;
    std::string gender;
    int day;
    int month;
    int year;

};


#endif // REQUEST_HPP
