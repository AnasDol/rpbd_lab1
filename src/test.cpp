#include "ActiveRecord/Animal.hpp"
#include "ActiveRecord/Breed.hpp"
#include "Windows.h"
#include "connection.hpp"
#include "menu.hpp"
#include <iostream>
#include <odbcinst.h>

int main() {

    std::string dsn = "PostgresDataSource";
    std::string uid = "rpbd_user";
    std::string pwd = "1234";

    SQLHENV env;
    SQLHDBC dbc;

    int result = connect_to_db(dsn, uid, pwd, &env, &dbc);

    if (result == 1) {
        std::cout << "Connection failed.";
        return 1;
    }

    if (init_tables(dbc) != 0) {
        std::cout << "Tables initialization failed.";
        return 1;
    }

    // std::map<int, int> animals = Animal::get_values(dbc);
    // Animal::display(dbc, animals);

    //std::map<int, int> breeds = Breed::get_values(dbc);
   // Breed::display(dbc, breeds);

    Position pos;
    pos.setName("test");
    pos.insert(dbc);

    disconnect_from_db(env, dbc);

    return 0;
}
