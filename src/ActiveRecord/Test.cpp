#include "Test.hpp"

Test Test::find_by_id(SQLHDBC dbc, int id) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        throw std::runtime_error("Error allocating statement handle");
    }

    std::string select_query = "SELECT * FROM test WHERE id = " + std::to_string(id);
    ret = SQLExecDirect(stmt, (SQLCHAR *)select_query.c_str(), SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Error executing query");
    }

    if (SQLFetch(stmt) != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Record not found");
    }

    SQLINTEGER id_result;
    SQLINTEGER value_result;

    ret = SQLGetData(stmt, 1, SQL_INTEGER, &id_result, 0, NULL);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Error fetching data");
    }

    ret = SQLGetData(stmt, 2, SQL_INTEGER, &value_result, sizeof(value_result), NULL);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Error fetching data");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return Test(id_result, value_result);
}

bool Test::save(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        return false;
    }

    std::string insert_query = "INSERT INTO test (id, value) VALUES (" + std::to_string(id_) + ", " + std::to_string(value_) + ")";
    ret = SQLExecDirect(stmt, (SQLCHAR *)insert_query.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        return false;
    }

    id_ = last_insert_id(dbc);

    return true;
}

bool Test::update(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        return false;
    }

    std::string update_query = "UPDATE test SET value = " + std::to_string(value_)+ " WHERE id = " + std::to_string(id_);
    ret = SQLExecDirect(stmt, (SQLCHAR *)update_query.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        return false;
    }

    return true;
}

bool Test::remove(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        return false;
    }

    std::string remove_query = "DELETE FROM test WHERE id = " + std::to_string(id_);
    ret = SQLExecDirect(stmt, (SQLCHAR *)remove_query.c_str(), SQL_NTS);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        return false;
    }

    return true;
}


int Test::last_insert_id(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        throw std::runtime_error("Error allocating statement handle");
    }

    std::string query = "SELECT lastval()";
    ret = SQLExecDirect(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Error executing query");
    }

    ret = SQLFetch(stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Error fetching data");
    }

    SQLINTEGER last_id;

    ret = SQLGetData(stmt, 1, SQL_INTEGER, &last_id, 0, NULL);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Error fetching data");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return last_id;
}