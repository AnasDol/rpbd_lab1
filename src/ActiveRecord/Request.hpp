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

#include "Client.hpp"
#include "Breed.hpp"

class Request {

public:

    Request() : id(-1), client(nullptr), breed(nullptr), gender(""), day(0), month(0), year(0) {}

    Request(Client* client, Breed* breed, std::string gender, int day, int month, int year)
        : id(-1), client(client), breed(breed), gender(gender), day(day), month(month), year(year) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Request* find(SQLHDBC dbc, int id);
    static std::map<int, int> get_values(SQLHDBC dbc);
    static std::map<int, int> get_values(SQLHDBC dbc, std::string attribute, std::string value);
    static void display(SQLHDBC dbc, std::map<int, int> record_map);

    // getters
    int getId() const { return id; }
    Client* getClient() const { return client; }
    Breed* getBreed() const { return breed; }
    std::string getGender() const { return gender; }
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    std::string getDate() const;

    // setters
    void setClient(Client* cl) { client = cl; }
    void setBreed(Breed* br) { breed = br; }
    void setGender(const std::string &gender) { this->gender = gender; }
    void setDay(int day) { this->day = day; }
    void setMonth(int month) { this->month = month; }
    void setYear(int year) { this->year = year; }

    ~Request() {
        delete client;
        delete breed;
    }

private:

    static inline const std::string table_name {"requests"};

    int id;
    Client* client;
    Breed* breed;
    std::string gender;
    int day;
    int month;
    int year;

};


#endif // REQUEST_HPP
