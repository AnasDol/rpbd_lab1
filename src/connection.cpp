#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>

#define ODBC_ERROR_MSG_SIZE 1024

void show_error(SQLHANDLE handle, SQLSMALLINT handle_type) {
    SQLCHAR sql_state[6], error_msg[ODBC_ERROR_MSG_SIZE];
    SQLINTEGER native_error;
    SQLSMALLINT i = 0, msg_len;

    while (SQLGetDiagRec(handle_type, handle, ++i, sql_state, &native_error, error_msg, ODBC_ERROR_MSG_SIZE, &msg_len) == SQL_SUCCESS) {
        std::cout << sql_state << " " << (long)native_error << " " << error_msg << std::endl;
    }
}

int main() {
    SQLHENV env;
    SQLHDBC dbc;
    SQLRETURN ret;

    const char *dsn = "PostgresDataSource";
    const char *uid = "rpbd_user";
    const char *pwd = "1234";

    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(env, SQL_HANDLE_ENV);
        return 1;
    }

    ret = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, 0);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(env, SQL_HANDLE_ENV);
        return 1;
    }

    ret = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(env, SQL_HANDLE_ENV);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    ret = SQLConnect(dbc, (SQLCHAR*)dsn, SQL_NTS, (SQLCHAR*)uid, SQL_NTS, (SQLCHAR*)pwd, SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    std::cout << "Connection established." << std::endl;

    SQLDisconnect(dbc);

    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return 0;
}
