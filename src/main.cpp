#include <iostream>
#include "Windows.h"
#include <odbcinst.h>

int main(void) {

     std::cout<<"test1\n";

    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;

    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);

    /* connect to the data source */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    /* do something with the statement handle e.g. issue sql */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    /* disconnect */
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    std::cout<<"test2\n";
}