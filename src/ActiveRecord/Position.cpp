#include "Position.hpp"

void Position::insert(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "INSERT INTO positions (name) VALUES (?) RETURNING id";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, name.size(), 0,
                              (SQLCHAR*)name.c_str(), name.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for name");
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
    
    this->id = inserted_id;

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Position::update(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "UPDATE positions SET name = ? WHERE id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, name.size(), 0,
                              const_cast<char *>(name.c_str()), name.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for name");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);
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

void Position::remove(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "DELETE FROM positions WHERE id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);
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

Position Position::find_by_id(SQLHDBC dbc, int id) {
    
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM positions WHERE id = ?";

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }

    Position position;
    res = SQLBindCol(stmt, 1, SQL_C_LONG, &position.id, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for id");
    }

    SQLLEN len;
    char nameBuffer[255];
    res = SQLBindCol(stmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), &len);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for name");
    }

    res = SQLFetch(stmt);
    if (res == SQL_SUCCESS) {
      position.setName(std::string(nameBuffer, len));
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return position;

}

Position Position::find(SQLHDBC dbc, std::string attribute, std::string value) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM positions WHERE " + attribute + " = ?";

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, value.size(), 0,
                              (SQLCHAR*)value.c_str(), value.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for value");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }

    Position position;
    res = SQLBindCol(stmt, 1, SQL_C_LONG, &position.id, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for id");
    }

    SQLLEN len;
    char nameBuffer[255];
    res = SQLBindCol(stmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), &len);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for name");
    }

    res = SQLFetch(stmt);
    if (res == SQL_SUCCESS) {
      position.setName(std::string(nameBuffer, len));
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return position;
}

std::map<int, int> Position::display_and_return_all(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM positions";

    std::map<int, int> posMap;
    int positionId;
    char nameBuffer[255];
    SQLLEN len;

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &positionId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for id");
    }
    
    res = SQLBindCol(stmt, 2, SQL_C_CHAR, nameBuffer, sizeof(nameBuffer), &len);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for name");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }
 
    std::cout << "  "
              << std::setw(10) << "Id" 
              << std::setw(20) << "Name" 
              << std::endl;

    int rowNum = 1;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        std::cout << rowNum << "."
                  << std::setw(10) << positionId
                  << std::setw(20) << nameBuffer
                  << std::endl;
        posMap.insert({rowNum, positionId});
        rowNum++;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return posMap;
}