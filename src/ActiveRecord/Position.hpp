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

    int getId() const {
        return id;
    }

    std::string getName() const {
        return name;
    }

    void setName(const std::string& n) {
        name = n;
    }

    /// @brief добавляет в базу новую строчку с текущим name, в значение поля id записывается id новой строки
    void insert(SQLHDBC dbc);

    /// @brief изменяет значение name в строчке с текущим id
    void update(SQLHDBC dbc);

    /// @brief удаляет строчку с текущим id
    void remove(SQLHDBC dbc);

    static Position find_by_id(SQLHDBC dbc, int id);

    static std::map<int, int> display_and_return_all(SQLHDBC dbc);

private:
    int id;
    std::string name;

};


#endif // POSITION_HPP
