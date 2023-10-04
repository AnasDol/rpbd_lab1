#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "../connection.hpp"

class Client {

public:
    Client() : id(0), last_name(""), first_name(""), patronymic(""), address("") {}

    Client(int i, const std::string& ln, const std::string& fn, const std::string& p, const std::string& a) 
        : id(i), last_name(ln), first_name(fn), patronymic(p), address(a) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Client find(SQLHDBC dbc, int id);
    static std::map<int, int> get_values(SQLHDBC dbc);
    static std::map<int, int> get_values(SQLHDBC dbc, std::string attribute, std::string value);
    static void display(SQLHDBC dbc, std::map<int, int> record_map);

    // getters
    int getId() const { return id; }
    std::string getLastName() const { return last_name; }
    std::string getFirstName() const { return first_name; }
    std::string getPatronymic() const { return patronymic; }
    std::string getAddress() const { return address; }

    // setters
    void setLastName(const std::string& n) { last_name = n; }
    void setFirstName(const std::string& n) { first_name = n; }
    void setPatronymic(const std::string& p) { patronymic = p; }
    void setAddress(const std::string& a) { address = a; }

private:

    static inline const std::string table_name {"clients"};

    int id;
    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string address;

};


#endif // CLIENT_HPP
