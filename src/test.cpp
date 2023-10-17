#include "Windows.h"
#include "connection.hpp"
#include <iostream>
#include <odbcinst.h>
#include "ActiveRecord/Position.hpp"
#include "ActiveRecord/Employee.hpp"
#include "ActiveRecord/Breed.hpp"
#include "ActiveRecord/Client.hpp"
#include "ActiveRecord/Animal.hpp"
#include "menu.hpp"

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

    // Position pos;
    // pos.setName("test2");
    // pos.insert(dbc);

    // Employee emp;
    // emp.setLastName("Spanch");
    // emp.setFirstName("Bob");
    // emp.setPosition(pos);
    // emp.insert(dbc);

    // Employee emp = Employee::find(dbc, 4);
    // std::cout << emp.getLastName() << " " << emp.getFirstName();

    // Animal lisa;
    // lisa.setName("Lisa");
    // try {
    //     lisa.insert(dbc);
    //     std::cout << "New entry added.\n";
    // } catch (std::runtime_error const& e) {
    //     std::cout << "Failed to add new entry.\n";
    //     return -1;
    // }

    // Animal lisa = Animal::find(dbc, 1);

    // Animal dan;
    // dan.setName("Dan");
    // dan.insert(dbc);

    // Animal joe;
    // joe.setName("Joe");
    // joe.setAge(5);
    // joe.setMother(&lisa);
    // joe.setFather(&dan);
    // joe.insert(dbc);

    // Animal marva = Animal::find(dbc, 2);
    // marva.setName("Marva");
    // marva.update(dbc);

    // Animal lisa = Animal::find(dbc, 1);
    // lisa.setMother(&marva);
    // lisa.update(dbc);

    // Animal dan = Animal::find(dbc, 3);
    // dan.remove(dbc);

    //Position admin = Position::find(dbc, 5);

    //Breed scotland("scotland");
    //scotland.insert(dbc);

    // Employee spanchbob("Watson", "John", "", "", &admin, 3000);
    // spanchbob.insert(dbc);

    //option_add_new_animal(dbc);

    option_show_data(dbc);


    disconnect_from_db(env, dbc);

    return 0;
}
