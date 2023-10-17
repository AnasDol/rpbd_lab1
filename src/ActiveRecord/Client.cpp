#include "Client.hpp"

void Client::insert(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query =
        "INSERT INTO clients (last_name, first_name, patronymic, address) VALUES (?, ?, ?, ?) RETURNING id";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           last_name.size(), 0, (SQLCHAR *)last_name.c_str(),
                           last_name.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for last_name");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           first_name.size(), 0, (SQLCHAR *)first_name.c_str(),
                           first_name.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for first_name");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           patronymic.size(), 0, (SQLCHAR *)patronymic.c_str(),
                           patronymic.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for patronymic");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           address.size(), 0, (SQLCHAR *)address.c_str(),
                           address.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for address");
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

void Client::update(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query =
        "UPDATE clients SET last_name = ?, first_name = ?, patronymic = ?, address = ? WHERE id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           last_name.size(), 0, (SQLCHAR *)last_name.c_str(),
                           last_name.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for last_name");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           first_name.size(), 0, (SQLCHAR *)first_name.c_str(),
                           first_name.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for first_name");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           patronymic.size(), 0, (SQLCHAR *)patronymic.c_str(),
                           patronymic.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for patronymic");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           address.size(), 0, (SQLCHAR *)address.c_str(),
                           address.size(), nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for address");
    }

    res = SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0,
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

void Client::remove(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "DELETE FROM clients WHERE id = ?";
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

Client* Client::find(SQLHDBC dbc, int id) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM clients WHERE id = ?";

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

    Client* client = new Client();
    res = SQLBindCol(stmt, 1, SQL_C_LONG, &client->id, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for id");
    }

    SQLLEN len1;
    char last_name_buf[255];
    res = SQLBindCol(stmt, 2, SQL_C_CHAR, last_name_buf, sizeof(last_name_buf),
                     &len1);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for last_name");
    }

    SQLLEN len2;
    char first_name_buf[255];
    res = SQLBindCol(stmt, 3, SQL_C_CHAR, first_name_buf,
                     sizeof(first_name_buf), &len2);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for first_name");
    }

    SQLLEN len3;
    char patronymic_buf[255];
    res = SQLBindCol(stmt, 4, SQL_C_CHAR, patronymic_buf,
                     sizeof(patronymic_buf), &len3);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for patronymic");
    }

    SQLLEN len4;
    char address_buf[255];
    res = SQLBindCol(stmt, 5, SQL_C_CHAR, address_buf, sizeof(address_buf),
                     &len4);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for address");
    }

    res = SQLFetch(stmt);
    if (res == SQL_SUCCESS) {
        client->setLastName(std::string(last_name_buf, len1));
        client->setFirstName(std::string(first_name_buf, len2));
        client->setPatronymic(std::string(patronymic_buf, len3));
        client->setAddress(std::string(address_buf, len4));
    } else return nullptr;

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return client;
}

std::map<int, int> Client::get_values(SQLHDBC dbc) {

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

std::map<int, int> Client::get_values(SQLHDBC dbc, std::string attribute, std::string value) {

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

void Client::display(SQLHDBC dbc, std::map<int, int> record_map) {
    
    std::cout << "  "
              << std::setw(10) << "Id" 
              << std::setw(20) << "Last name" 
              << std::setw(20) << "First name" 
              << std::setw(20) << "Patronymic" 
              << std::setw(40) << "Address"
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
            SQLCHAR last_name[64], first_name[10], patronymic[64], address[64];

            SQLGetData(hstmt, 1, SQL_C_LONG, &id, 0, nullptr);
            SQLGetData(hstmt, 2, SQL_C_CHAR, &last_name, sizeof(last_name), nullptr);
            SQLGetData(hstmt, 3, SQL_C_CHAR, &first_name, sizeof(first_name), nullptr);
            SQLGetData(hstmt, 4, SQL_C_CHAR, &patronymic, sizeof(patronymic), nullptr);
            SQLGetData(hstmt, 5, SQL_C_CHAR, &address, sizeof(address), nullptr);

            std::cout << order << "."
                << std::setw(10) << id
                << std::setw(20) << last_name
                << std::setw(20) << first_name
                << std::setw(20) << patronymic
                << std::setw(40) << address
                << std::endl;
        }   

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);       
    }
    
}