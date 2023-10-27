#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "defaults.hpp"

struct pair {
    int first;
    int second;

    pair(int f, int s) : first(f), second(s) {}
};

#define ODBC_ERROR_MSG_SIZE 1024

void show_error(SQLHANDLE handle, SQLSMALLINT handle_type);

int connect_to_db(std::string dsn, std::string uid, std::string pwd, SQLHENV *env, SQLHDBC *dbc);


bool already_exists(SQLHDBC dbc, const std::string& table_name);

int create_table_if_not_exists(SQLHDBC dbc, std::string table_name, std::string table_args);

int init_tables(SQLHDBC dbc);


int disconnect_from_db(SQLHENV env, SQLHDBC dbc);

int print_table(SQLHDBC dbc, const std::string &table_name) ;

int get_last_inserted_id(SQLHDBC dbc, const std::string& table_name);

int get_record_num(SQLHDBC dbc, const std::string& table_name);

std::list<std::string> get_enum_values(SQLHDBC dbc, const std::string &enum_type_name);

std::list<std::string> get_values(SQLHDBC dbc, const std::string &table_name);

int countRecords(SQLHDBC dbc, const std::string& tableName, const std::string& attributeName, const std::string& attributeValue);


#endif // CONNECTION_HPP
