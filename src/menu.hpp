#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "ActiveRecord/Breed.hpp"

enum class Table {BREEDS, CLIENTS, EMPLOYEES, ANIMALS, EXHIBITIONS, PEDIGREE, PARTICIPATIONS, REQUESTS};

// std::istream& operator>>(std::istream& is, Table& t)
// {
//     int number;
//     std::cin >> number;
//     switch (number)
//     {
//     case 0:
//         t = Table::BREEDS;
//         break;
//     case 1:
//         t = Table::CLIENTS;
//         break;
//     case 2:
//         t = Table::EMPLOYEES;
//         break;
//     case 3:
//         t = Table::ANIMALS;
//         break;
//     case 4:
//         t = Table::EXHIBITIONS;
//         break;
//     case 5:
//         t = Table::PEDIGREE;
//         break;
//     case 6:
//         t = Table::PARTICIPATIONS;
//         break;
//     case 7:
//         t = Table::REQUESTS;
//         break;
    
//     default:
//         break;
//     }

//     return is;
// }

int option_add_new_animal(SQLHDBC dbc);

int option_add_new_breed(SQLHDBC dbc); // возвращает id или -1

void option_insert_new_record(SQLHDBC dbc);
void option_update_record(SQLHDBC dbc);
void option_delete_record(SQLHDBC dbc);
void option_print_table(SQLHDBC dbc);

void print_table_list();


#endif // MENU_HPP
