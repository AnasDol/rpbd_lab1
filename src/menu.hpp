#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <ios>
#include <limits>
#include <regex>
#include "ActiveRecord/Breed.hpp"
#include "ActiveRecord/Client.hpp"
#include "ActiveRecord/Employee.hpp"
#include "ActiveRecord/Position.hpp"
#include "ActiveRecord/Animal.hpp"
#include "ActiveRecord/Request.hpp"

enum class Table {BREEDS, CLIENTS, EMPLOYEES, ANIMALS, EXHIBITIONS, PEDIGREE, PARTICIPATIONS, REQUESTS};

void start(SQLHDBC dbc);
void proceed(SQLHDBC dbc, int option);

int option_add_new_animal(SQLHDBC dbc);
int option_add_new_breed(SQLHDBC dbc); // возвращает id или -1
int option_add_new_client(SQLHDBC dbc);
int option_add_new_employee(SQLHDBC dbc);
int option_add_new_vet(SQLHDBC dbc);
int option_add_new_position(SQLHDBC dbc);
int option_add_new_request(SQLHDBC dbc);

int select_breed(SQLHDBC dbc);
int select_client(SQLHDBC dbc);
std::string select_gender();
int select_date(int* day, int* month, int* year);

bool isLeapYear(int year);
bool isValidDate(int day, int month, int year);



void print_table_list();


#endif // MENU_HPP
