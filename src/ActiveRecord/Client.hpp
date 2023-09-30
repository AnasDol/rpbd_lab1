#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include "../connection.hpp"

class Client {

public:
    Client() : id(0), last_name(""), first_name(""), patronymic(""), address("") {}

    Client(int i, const std::string& ln, const std::string& fn, const std::string& p, const std::string& a) 
        : id(i), last_name(ln), first_name(fn), patronymic(p), address(a) {}

    /// @brief добавляет в базу новую строчку с текущим name, в значение поля id записывается id новой строки
    void insert(SQLHDBC dbc);

    /// @brief изменяет значение name в строчке с текущим id
    void update(SQLHDBC dbc);

    /// @brief удаляет строчку с текущим id
    void remove(SQLHDBC dbc);

    static Client find_by_id(SQLHDBC dbc, int id);

    static int get_record_num(SQLHDBC dbc);

    static int get_last_inserted_id(SQLHDBC dbc);

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

private:
    int id;
    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string address;

};


#endif // CLIENT_HPP
