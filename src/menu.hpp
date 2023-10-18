#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <ios>
#include <limits>
#include <regex>
#include "ActiveRecord/Animal.hpp"
#include "ActiveRecord/Breed.hpp"
#include "ActiveRecord/Client.hpp"
#include "ActiveRecord/Employee.hpp"
#include "ActiveRecord/Position.hpp"
#include "ActiveRecord/Request.hpp"
#include "ActiveRecord/Exhibition.hpp"
#include "ActiveRecord/Participation.hpp"

void start(SQLHDBC dbc);
void proceed(SQLHDBC dbc, int option);

int option_add_new_animal(SQLHDBC dbc);
int option_add_new_breed(SQLHDBC dbc); // возвращает id или -1
int option_add_new_client(SQLHDBC dbc);
int option_add_new_employee(SQLHDBC dbc);
int option_add_new_vet(SQLHDBC dbc);
int option_add_new_position(SQLHDBC dbc);
int option_add_new_request(SQLHDBC dbc);
int option_add_new_exhibition(SQLHDBC dbc);
int option_add_new_participation(SQLHDBC dbc);
int option_add_new_participation(SQLHDBC dbc, int animal_id);

int option_add_new_pedigree_info(SQLHDBC dbc);
void printFamilyTree(const Animal* animal, const std::string& prefix = "");

int option_update_animal(SQLHDBC dbc);
int option_update_breed(SQLHDBC dbc);
int option_update_client(SQLHDBC dbc);
int option_update_employee(SQLHDBC dbc);
int option_update_position(SQLHDBC dbc);
int option_update_request(SQLHDBC dbc);
int option_update_exhibition(SQLHDBC dbc);
int option_update_participation(SQLHDBC dbc);

int option_update_pedigree_info(SQLHDBC dbc);

int option_remove_animal(SQLHDBC dbc);
int option_remove_breed(SQLHDBC dbc);
int option_remove_client(SQLHDBC dbc);
int option_remove_employee(SQLHDBC dbc);
int option_remove_position(SQLHDBC dbc);
int option_remove_request(SQLHDBC dbc);
int option_remove_exhibition(SQLHDBC dbc);
int option_remove_participation(SQLHDBC dbc);

int option_remove_pedigree_info(SQLHDBC dbc);

int option_show_data(SQLHDBC dbc);
int option_show_pedigree_info(SQLHDBC dbc);

int select_animal(SQLHDBC dbc, bool addition = true);
int select_animal(SQLHDBC dbc, std::string gender, bool addition = true);
int select_breed(SQLHDBC dbc, bool addition = true);
int select_client(SQLHDBC dbc, bool addition = true);
int select_employee(SQLHDBC dbc, bool addition = true);
int select_position(SQLHDBC dbc, bool addition = true);
int select_request(SQLHDBC dbc, bool addition = true);
int select_exhibition(SQLHDBC dbc, bool addition = true);
int select_vet(SQLHDBC dbc, bool addition = true);
std::string select_gender();
int select_date(int* day, int* month, int* year);

bool isLeapYear(int year);
bool isValidDate(int day, int month, int year);

#endif // MENU_HPP
