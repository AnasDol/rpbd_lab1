#include "Employee.hpp"

void Employee::insert(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "INSERT INTO employees (last_name, first_name, patronymic, address, position_id, salary) VALUES (?, ?, ?, ?, ?, ?) RETURNING id";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, last_name.size(), 0,
                              (SQLCHAR*)last_name.c_str(), last_name.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for last_name");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, first_name.size(), 0,
                              (SQLCHAR*)first_name.c_str(), first_name.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for first_name");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, patronymic.size(), 0,
                              (SQLCHAR*)patronymic.c_str(), patronymic.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for patronymic");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, address.size(), 0,
                              (SQLCHAR*)address.c_str(), address.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for address");
    }

    res = SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &position_id, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for position_id");
    }

    res = SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &salary, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for salary");
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

void Employee::update(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "UPDATE employees SET last_name = ?, first_name = ?, patronymic = ?, address = ?, position_id = ?, salary = ? WHERE id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, last_name.size(), 0,
                              (SQLCHAR*)last_name.c_str(), last_name.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for last_name");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, first_name.size(), 0,
                              (SQLCHAR*)first_name.c_str(), first_name.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for first_name");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, patronymic.size(), 0,
                              (SQLCHAR*)patronymic.c_str(), patronymic.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for patronymic");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, address.size(), 0,
                              (SQLCHAR*)address.c_str(), address.size(), nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for address");
    }

    res = SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &position_id, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for position_id");
    }

    res = SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &salary, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for salary");
    }

    res = SQLBindParameter(stmt, 7, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);
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

void Employee::remove(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "DELETE FROM employees WHERE id = ?";
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

Employee Employee::find(SQLHDBC dbc, int id) {
    
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM employees WHERE id = ?";

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

    Employee employee;
    res = SQLBindCol(stmt, 1, SQL_C_LONG, &employee.id, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for id");
    }

    SQLLEN len1;
    char last_name_buf[255];
    res = SQLBindCol(stmt, 2, SQL_C_CHAR, last_name_buf, sizeof(last_name_buf), &len1);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for last_name");
    }

    SQLLEN len2;
    char first_name_buf[255];
    res = SQLBindCol(stmt, 3, SQL_C_CHAR, first_name_buf, sizeof(first_name_buf), &len2);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for first_name");
    }

    SQLLEN len3;
    char patronymic_buf[255];
    res = SQLBindCol(stmt, 4, SQL_C_CHAR, patronymic_buf, sizeof(patronymic_buf), &len3);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for patronymic");
    }

    SQLLEN len4;
    char address_buf[255];
    res = SQLBindCol(stmt, 5, SQL_C_CHAR, address_buf, sizeof(address_buf), &len4);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for address");
    }

    res = SQLBindCol(stmt, 6, SQL_C_LONG, &employee.position_id, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for position_id");
    }

    res = SQLBindCol(stmt, 7, SQL_C_LONG, &employee.salary, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column for salary");
    }

    res = SQLFetch(stmt);
    if (res == SQL_SUCCESS) {
        employee.setLastName(std::string(last_name_buf, len1));
        employee.setFirstName(std::string(first_name_buf, len2));
        employee.setPatronymic(std::string(patronymic_buf, len3));
        employee.setAddress(std::string(address_buf, len4));
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return employee;

}

std::map<int, int> Employee::display_and_return(SQLHDBC dbc) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM employees";

    std::map<int, int> empMap;
    int empId;

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &empId, 0, nullptr);
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

    int positionId;
    res = SQLBindCol(stmt, 6, SQL_C_LONG, &positionId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for positionId");
    }

    int salary;
    res = SQLBindCol(stmt, 7, SQL_C_LONG, &salary, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for salary");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    std::cout << "  " << std::setw(10) << "Id" << std::setw(20) << "Last name"
              << std::setw(20) << "First name" << std::setw(20) << "Patronymic"
              << std::setw(40) << "Address" << std::setw(20) << "Position ID"
              << std::setw(20) << "Salary" << std::endl;

    int rowNum = 1;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        std::cout << rowNum << "." << std::setw(10) << empId << std::setw(20)
                  << last_name_buf << std::setw(20) << first_name_buf
                  << std::setw(20) << patronymic_buf << std::setw(40)
                  << address_buf << std::setw(20) << positionId << std::setw(20) << salary << std::endl;
        empMap.insert({rowNum, empId});
        rowNum++;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return empMap;
}

std::map<int, int> Employee::display_and_return_vets(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::map<int, int> empMap;

    std::cout << "  " << std::setw(10) << "Id" << std::setw(20) << "Last name"
              << std::setw(20) << "First name" << std::setw(20) << "Patronymic"
              << std::setw(40) << "Address" << std::setw(20) << "Position ID"
              << std::setw(20) << "Salary" << std::endl;

    if (countRecords(dbc, "positions", "name", "vet") == 0) {
        std::cout << "---- Nothing to show -\n";
        return empMap;
    }

    // Get position ID for provided position name
    std::string query1 = "SELECT id FROM positions WHERE name = 'vet'";
    res = SQLPrepare(stmt, (SQLCHAR *)query1.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement 1");
    }

    int positionId;
    res = SQLBindCol(stmt, 1, SQL_C_LONG, &positionId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for id");
    }

    res = SQLExecute(stmt);
    if (SQLFetch(stmt) != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to fetch position id");
    }

    SQLFreeStmt(stmt, SQL_CLOSE);

    std::string query2 = "SELECT * FROM employees WHERE position_id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query2.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement 2");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &positionId, 0, nullptr);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for position_id");
    }

    int empId;

    res = SQLPrepare(stmt, (SQLCHAR *)query2.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &empId, 0, nullptr);
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

    res = SQLBindCol(stmt, 6, SQL_C_LONG, &positionId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for positionId");
    }

    int salary;
    res = SQLBindCol(stmt, 7, SQL_C_LONG, &salary, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for salary");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }


    int rowNum = 1;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        std::cout << rowNum << "." << std::setw(10) << empId << std::setw(20)
                  << last_name_buf << std::setw(20) << first_name_buf
                  << std::setw(20) << patronymic_buf << std::setw(40)
                  << address_buf << std::setw(20) << positionId << std::setw(20) << salary << std::endl;
        empMap.insert({rowNum, empId});
        rowNum++;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return empMap;



}