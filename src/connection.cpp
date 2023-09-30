#include "connection.hpp"

void show_error(SQLHANDLE handle, SQLSMALLINT handle_type) {
    SQLCHAR sql_state[6], error_msg[ODBC_ERROR_MSG_SIZE];
    SQLINTEGER native_error;
    SQLSMALLINT i = 0, msg_len;

    while (SQLGetDiagRec(handle_type, handle, ++i, sql_state, &native_error, error_msg, ODBC_ERROR_MSG_SIZE, &msg_len) == SQL_SUCCESS) {
        std::cout << sql_state << " " << (long)native_error << " " << error_msg << std::endl;
    }
}

int connect_to_db(std::string dsn, std::string uid, std::string pwd, SQLHENV *env, SQLHDBC *dbc) {
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, env);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(*env, SQL_HANDLE_ENV);
        return 1;
    }

    ret = SQLSetEnvAttr(*env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, 0);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(*env, SQL_HANDLE_ENV);
        return 1;
    }

    ret = SQLAllocHandle(SQL_HANDLE_DBC, *env, dbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(*env, SQL_HANDLE_ENV);
        SQLFreeHandle(SQL_HANDLE_ENV, *env);
        return 1;
    }

    ret = SQLConnect(*dbc, (SQLCHAR*)dsn.c_str(), SQL_NTS, (SQLCHAR*)uid.c_str(), SQL_NTS, (SQLCHAR*)pwd.c_str(), SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(*dbc, SQL_HANDLE_DBC);
        SQLFreeHandle(SQL_HANDLE_DBC, *dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, *env);
        return 1;
    }

    std::cout << "Connection established." << std::endl;

    return 0;
}


bool already_exists(SQLHDBC dbc, const std::string& table_name) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        return false;
    }

    std::string query = "SELECT EXISTS (SELECT 1 FROM information_schema.tables WHERE table_name = '" + table_name + "');";
    ret = SQLExecDirect(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return false;
    }

    SQLINTEGER exists;
    ret = SQLFetch(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return false;
    }

    ret = SQLGetData(stmt, 1, SQL_INTEGER, &exists, 0, NULL);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return false;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return (exists == 1);
}

int create_table_if_not_exists(SQLHDBC dbc, std::string table_name, std::string table_args) {

    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        return 1;
    }

    std::string create_query = "CREATE TABLE IF NOT EXISTS " + table_name + " (" + table_args + ")";

    ret = SQLExecDirect(stmt, (SQLCHAR*)create_query.c_str(), SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return 1;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return 0;
}

int init_tables(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        return 1;
    }

    std::string create_query = "do $$ begin if not exists (select 1 from pg_type where typname = 'gen') then create type gen as enum ('male', 'female'); end if; if not exists (select 1 from pg_type where typname = 'pos') then create type pos as enum ('vet', 'admin', 'cleaner'); end if; end$$; create table if not exists breeds(id serial primary key, name text UNIQUE); create table if not exists clients(id serial primary key, last_name text not null, first_name text not null, patronymic text, address text); create table if not exists employees(id serial primary key, last_name text not null, first_name text not null, patronymic text, address text, position pos, salary money); create table if not exists animals(id serial primary key, name text, age integer check (age > 0), gender gen, breed_id integer references breeds(id), appearance text, client_id integer references clients(id), vet_id integer references employees(id)); create table if not exists pedigree(parent_id integer references animals(id), child_id integer references animals(id)); create table if not exists exhibitions(id serial primary key, name text, address text, date date); create table if not exists participations(id serial primary key, animal_id integer references animals(id), exhibition_id integer references exhibitions(id), reward text);";

    ret = SQLExecDirect(stmt, (SQLCHAR*)create_query.c_str(), SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return 1;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return 0;
}


int disconnect_from_db(SQLHENV env, SQLHDBC dbc) {
    SQLRETURN ret;

    ret = SQLDisconnect(dbc);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        return 1;
    }

    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    std::cout << "Connection closed." << std::endl;

    return 0;
}

int print_table(SQLHDBC dbc, const std::string &table_name) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLSMALLINT num_columns;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        return 1;
    }

    std::string select_query = "SELECT * FROM " + table_name;
    ret = SQLExecDirect(stmt, (SQLCHAR *)select_query.c_str(), SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return 1;
    }

    ret = SQLNumResultCols(stmt, &num_columns);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return 1;
    }

    SQLULEN column_size;

    // Print column names
    for (SQLUSMALLINT i = 1; i <= num_columns; i++) {
        SQLCHAR column_name[128];
        SQLSMALLINT column_name_len;
        
        SQLSMALLINT nullable;
        SQLSMALLINT decimal_digits;
        SQLSMALLINT data_type;

        ret = SQLDescribeCol(stmt, i, column_name, sizeof(column_name), &column_name_len,
                              &data_type, &column_size, &decimal_digits, &nullable);

        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            show_error(stmt, SQL_HANDLE_STMT);
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            return 1;
        }
        std::cout << "\t";
        std::cout << /*std::setw(column_size) <<*/ column_name;
    }
    std::cout << std::endl;

    //Print table data
    int num = 0;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        num++;
        for (SQLUSMALLINT i = 1; i <= num_columns; i++) {
            SQLLEN value_len;
            SQLCHAR value[128];
            ret = SQLGetData(stmt, i, SQL_C_CHAR, value, sizeof(value), &value_len);
            if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
                show_error(stmt, SQL_HANDLE_STMT);
                SQLFreeHandle(SQL_HANDLE_STMT, stmt);
                return 1;
            }
            if (i == 1) std::cout << num << ".";
            std::cout << "\t";
            std::cout << /*std::setw(column_size) <<*/ value;
        }
        std::cout << std::endl;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return 0;
}


int get_last_inserted_id(SQLHDBC dbc, const std::string& table_name) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT max(id) FROM " + table_name;
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLINTEGER last_id = 0;
    SQLLEN len = 0;
    res = SQLBindCol(stmt, 1, SQL_C_LONG, &last_id, 0, &len); 
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for id");
    }
    
    res = SQLFetch(stmt);
    if (res == SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return last_id;
    }
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to fetch max ID");
    }
}