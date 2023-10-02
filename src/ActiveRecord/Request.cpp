#include "Request.hpp"

void Request::insert(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "INSERT INTO requests(client_id, breed_id, gender, request_date) VALUES (?, ?, ?, TO_DATE(?, 'DD.MM.YYYY')) RETURNING id";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &client_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for client_id");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &breed_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for breed_id");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, gender.size(), 0, (SQLCHAR*)gender.c_str(), gender.size(), NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for gender");
    }

    std::string request_date = getDate();
    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, request_date.size(), 0, (SQLCHAR*)request_date.c_str(), request_date.size(), NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for request_date");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLINTEGER inserted_id;
    SQLLEN id_len;
    if (SQL_SUCCESS == SQLFetch(stmt))
    {
        res = SQLGetData(stmt, 1, SQL_INTEGER, &inserted_id, 0, &id_len);
        if(res != SQL_SUCCESS) {
            throw std::runtime_error("Failed to retrieve ID");
        }
    }
    
    id = inserted_id;

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

 std::string Request::getDate() const {
    std::string dayStr = std::to_string(day);
    std::string monthStr = std::to_string(month);
    std::string yearStr = std::to_string(year);

    // Добавляем ведущий ноль, если значение дня меньше 10
    if (dayStr.length() < 2) {
      dayStr = "0" + dayStr;
    }

    // Добавляем ведущий ноль, если значение месяца меньше 10
    if (monthStr.length() < 2) {
      monthStr = "0" + monthStr;
    }

    // Создаем строку в формате "dd.mm.yyyy"
    std::string dateString = dayStr + "." + monthStr + "." + yearStr;
    return dateString;
  }