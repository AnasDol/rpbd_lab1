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

    int getId() const { return id; }

    std::string getName() const { return name; }

    void setName(const std::string &n) { name = n; }

    /// @brief добавляет в базу новую строчку с текущим name, в значение поля id
    /// записывается id новой строки
    void insert(SQLHDBC dbc);

    /// @brief изменяет значение name в строчке с текущим id
    void update(SQLHDBC dbc);

    /// @brief удаляет строчку с текущим id
    void remove(SQLHDBC dbc);

    static Breed find_by_id(SQLHDBC dbc, int id);

    static std::map<int, int> display_and_return_all(SQLHDBC dbc);

  private:
    int id;
    std::string name;
};

#endif // BREED_HPP
