#include "Exhibition.hpp"

void Exhibition::insert(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query =
        "INSERT INTO " + table_name + " (name, address, exhibition_date) VALUES (?, ?, TO_DATE(?, 'DD.MM.YYYY')) RETURNING id";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           name.size(), 0, (SQLCHAR *)name.c_str(),
                           name.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for name");
    }
    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           address.size(), 0, (SQLCHAR *)address.c_str(),
                           address.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for address");
    }

    std::string exhibition_date = getDate();
    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, exhibition_date.size(), 0, (SQLCHAR*)exhibition_date.c_str(), exhibition_date.size(), NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for exhibition_date");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLINTEGER inserted_id;
    SQLLEN id_len;
    if (SQL_SUCCESS == SQLFetch(stmt)) {
        res = SQLGetData(stmt, 1, SQL_INTEGER, &inserted_id, 0, &id_len);
        if (res != SQL_SUCCESS) {
            throw std::runtime_error("Failed to retrieve ID");
        }
    }

    this->id = inserted_id;

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Exhibition::update(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query =
        "UPDATE " + table_name + " SET name = ?, address = ?, exhibition_date = TO_DATE(?, 'DD.MM.YYYY') WHERE id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           name.size(), 0, (SQLCHAR *)name.c_str(),
                           name.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for name");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           address.size(), 0, (SQLCHAR *)address.c_str(),
                           address.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for address");
    }

    std::string exhibition_date = getDate();
    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, exhibition_date.size(), 0, (SQLCHAR*)exhibition_date.c_str(), exhibition_date.size(), NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for exhibition_date");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0,
                           0, &id, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Exhibition::remove(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "DELETE FROM " + table_name + " WHERE id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0,
                           0, &id, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

Exhibition Exhibition::find(SQLHDBC dbc, int id) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM " + table_name + " WHERE id = ?";

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0,
                           0, &id, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    Exhibition exhibition;
    res = SQLBindCol(stmt, 1, SQL_C_LONG, &exhibition.id, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for id");
    }

    SQLLEN name_len;
    char name_buf[255];

    SQLLEN address_len;
    char address_buf[255];

    SQLCHAR exhibition_date_buf[255];
    SQLLEN exhibition_date_len;

    if (SQLBindCol(stmt, 1, SQL_C_LONG, &exhibition.id, 0, nullptr) != SQL_SUCCESS
      || SQLBindCol(stmt, 2, SQL_C_CHAR, name_buf, sizeof(name_buf), &name_len) != SQL_SUCCESS
      || SQLBindCol(stmt, 3, SQL_C_CHAR, address_buf, sizeof(address_buf), &address_len) != SQL_SUCCESS
      || SQLBindCol(stmt, 4, SQL_C_CHAR, exhibition_date_buf, sizeof(exhibition_date_buf), &exhibition_date_len) != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column");
    }

    res = SQLFetch(stmt);
    if (res == SQL_SUCCESS) {
        exhibition.setName(std::string(name_buf, name_len));
        exhibition.setAddress(std::string(address_buf, address_len));
        sscanf((char*)exhibition_date_buf, "%d-%d-%d", &(exhibition.year), &(exhibition.month), &(exhibition.day));  // assuming that date is obtained in format "yyyy-mm-dd"
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return exhibition;
}

std::map<int, int> Exhibition::get_values(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM " + table_name;

    std::map<int, int> recordMap;
    int recordId;

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &recordId, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }

    int rowNum = 1;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        recordMap.insert({rowNum, recordId});
        rowNum++;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return recordMap;
}

std::map<int, int> Exhibition::get_values(SQLHDBC dbc, std::string attribute, std::string value) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM " + table_name + " WHERE " + attribute + " = ?";

    std::map<int, int> recordMap;
    int recordId;

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    // Bind the attribute value parameter
    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, value.size(), 0, (SQLCHAR *)value.c_str(), value.size(), NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for attribute value");
    }

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &recordId, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }

    int rowNum = 1;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        recordMap.insert({rowNum, recordId});
        rowNum++;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return recordMap;

}

void Exhibition::display(SQLHDBC dbc, std::map<int, int> record_map) {
    
    std::cout << "  "
              << std::setw(10) << "Id" 
              << std::setw(20) << "Name" 
              << std::setw(40) << "Address"
              << std::setw(20) << "Exhibition date" 
              << std::endl;

    for (const auto& [order, id] : record_map) {

        SQLHSTMT hstmt;
        SQLRETURN retcode;

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &hstmt);

        if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
            std::cout << "Failed to allocate handle." << std::endl;
            return;
        }

        std::string query = "SELECT * FROM " + table_name + " WHERE id = " + std::to_string(id);

        retcode = SQLExecDirect(hstmt, (SQLCHAR*)(query.c_str()), SQL_NTS);

        if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
            std::cout << "Failed to execute query." << std::endl;
            continue;
        }

        while (SQLFetch(hstmt) == SQL_SUCCESS) {

            SQLINTEGER id;
            SQLCHAR name[64], address[64], exhibition_date[64];

            SQLGetData(hstmt, 1, SQL_C_LONG, &id, 0, nullptr);
            SQLGetData(hstmt, 2, SQL_C_CHAR, &name, sizeof(name), nullptr);
            SQLGetData(hstmt, 3, SQL_C_CHAR, &address, sizeof(address), nullptr);
            SQLGetData(hstmt, 4, SQL_C_CHAR, &exhibition_date, sizeof(exhibition_date), nullptr);

            std::cout << order << "."
                << std::setw(10) << id
                << std::setw(20) << name
                << std::setw(40) << address
                << std::setw(20) << exhibition_date
                << std::endl;
        }   

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);       
    }
    
}

std::string Exhibition::getDate() const {
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