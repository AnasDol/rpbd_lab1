#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "ActiveRecord/Breed.hpp"
#include "ActiveRecord/Client.hpp"
#include "ActiveRecord/Employee.hpp"
#include "ActiveRecord/Position.hpp"
#include "ActiveRecord/Animal.hpp"

enum class Table {BREEDS, CLIENTS, EMPLOYEES, ANIMALS, EXHIBITIONS, PEDIGREE, PARTICIPATIONS, REQUESTS};

int option_add_new_animal(SQLHDBC dbc);

int option_add_new_breed(SQLHDBC dbc); // возвращает id или -1
int option_add_new_client(SQLHDBC dbc);
int option_add_new_employee(SQLHDBC dbc);
int option_add_new_position(SQLHDBC dbc);

void print_table_list();


#endif // MENU_HPP
