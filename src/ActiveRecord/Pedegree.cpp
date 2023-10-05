#include "Pedigree.hpp"

void Pedigree::insert(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query =
        "INSERT INTO " + table_name + " (parent_id, child_id) VALUES (?, ?)";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &parent_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for parent_id");
    }


    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &child_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for child_id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Pedigree::update(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query =
        "UPDATE " + table_name + " SET parent_id = ?, child_id = ? WHERE parent_id = ? AND child_id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &parent_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for parent_id");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &child_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for child_id");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &parent_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for parent_id");
    }

    res = SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &child_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for child_id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Pedigree::remove(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "DELETE FROM " + table_name + " WHERE parent_id = ? AND child_id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &parent_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for parent_id");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &child_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for child_id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

Pedigree Pedigree::find(SQLHDBC dbc, int parent_id, int child_id) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM " + table_name + " WHERE parent_id = ? AND child_id = ?";

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &parent_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for parent_id");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &child_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for child_id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    Pedigree pedigree;

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &pedigree.parent_id, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for parent_id");
    }

    res = SQLBindCol(stmt, 2, SQL_C_LONG, &pedigree.child_id, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for child_id");
    }

    res = SQLFetch(stmt);

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return pedigree;
}

std::map<int, pair> Pedigree::get_values(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM " + table_name;

    std::map<int, pair> recordMap;
    int parentId, childId;

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &parentId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for parentId");
    }

    res = SQLBindCol(stmt, 2, SQL_C_LONG, &childId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for childId");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }

    int rowNum = 1;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        recordMap.insert({rowNum, {parentId, childId}});
        rowNum++;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return recordMap;
}

std::map<int, pair> Pedigree::get_values(SQLHDBC dbc, std::string attribute, std::string value) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM " + table_name + " WHERE " + attribute + " = ?";

    std::map<int, pair> recordMap;
    int parentId, childId;

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

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &parentId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for parentId");
    }

    res = SQLBindCol(stmt, 2, SQL_C_LONG, &childId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for childId");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }

    int rowNum = 1;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        recordMap.insert({rowNum, {parentId, childId}});
        rowNum++;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return recordMap;

}

void Pedigree::display(SQLHDBC dbc, std::map<int, pair> record_map) {
    
    std::cout << "  "
              << std::setw(20) << "Parent Id" 
              << std::setw(20) << "Child Id"
              << std::endl;

    for (const auto& [order, p] : record_map) {

        SQLHSTMT hstmt;
        SQLRETURN retcode;

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &hstmt);

        if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
            std::cout << "Failed to allocate handle." << std::endl;
            return;
        }

        std::string query = "SELECT * FROM " + table_name + " WHERE parent_id = " + std::to_string(p.parent_id) + " AND child_id = " + std::to_string(p.child_id);

        retcode = SQLExecDirect(hstmt, (SQLCHAR*)(query.c_str()), SQL_NTS);

        if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
            std::cout << "Failed to execute query." << std::endl;
            continue;
        }

        while (SQLFetch(hstmt) == SQL_SUCCESS) {

            std::cout << order << "."
                << std::setw(20) << p.parent_id
                << std::setw(20) << p.child_id
                << std::endl;
        }   

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);       
    }
    
}