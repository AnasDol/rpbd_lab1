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

Client Client::find_by_id(SQLHDBC dbc, int id) {
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

    Client client;
    res = SQLBindCol(stmt, 1, SQL_C_LONG, &client.id, 0, nullptr);
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
        client.setLastName(std::string(last_name_buf, len1));
        client.setFirstName(std::string(first_name_buf, len2));
        client.setPatronymic(std::string(patronymic_buf, len3));
        client.setAddress(std::string(address_buf, len4));
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return client;
}

std::map<int, int> Client::display_and_return_all(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM clients";

    std::map<int, int> clientMap;
    int clientId;

    std::cout << "  " << std::setw(10) << "Id" << std::setw(20) << "Last name"
              << std::setw(20) << "First name" << std::setw(20) << "Patronymic"
              << std::setw(20) << "Address" << std::endl;

    if (get_record_num(dbc, "clients")==0) {
        std::cout << "---- Nothing to show -\n";
        return clientMap;
    }

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &clientId, 0, nullptr);
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

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    int rowNum = 1;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        std::cout << rowNum << "." << std::setw(10) << clientId << std::setw(20)
                  << last_name_buf << std::setw(20) << first_name_buf
                  << std::setw(20) << patronymic_buf << std::setw(20)
                  << address_buf << std::endl;
        clientMap.insert({rowNum, clientId});
        rowNum++;
    }

    if (rowNum == 1) std::cout << std::setw(60) << "Nothing to show\n";

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return clientMap;
}