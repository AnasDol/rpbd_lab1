#ifndef TEST
#define TEST

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include "../connection.hpp"

class Test {
public:
    Test(int id, int value) : id_(id), value_(value) {}

    static Test find_by_id(SQLHDBC dbc, int id);
    bool save(SQLHDBC dbc);
    bool update(SQLHDBC dbc);
    bool remove(SQLHDBC dbc);


//private:
    int id_;
    int value_;

    static int last_insert_id(SQLHDBC dbc);
};

#endif