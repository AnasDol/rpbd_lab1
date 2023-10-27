#ifndef POSITION_HPP
#define POSITION_HPP

#include "../defaults.hpp"

class Position {

public:
    Position() : id(-1), name("") {}

    Position(const std::string& n) : id(-1), name(n) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Position* find(SQLHDBC dbc, int id);
    static std::map<int, int> get_values(SQLHDBC dbc);
    static std::map<int, int> get_values(SQLHDBC dbc, std::string attribute, std::string value);
    static void display(SQLHDBC dbc, std::map<int, int> record_map);

    // getters
    int getId() const { return id; }
    std::string getName() const { return name; }

    // setters
    void setName(const std::string& n) { name = n; }

private:

    static inline const std::string table_name {"positions"};

    int id;
    std::string name;

};


#endif // POSITION_HPP
