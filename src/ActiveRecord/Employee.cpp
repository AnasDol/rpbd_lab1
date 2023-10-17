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

    SQLLEN cbLast_name = SQL_NTS,
    cbFirst_name = SQL_NTS,
    cbPatronymic = SQL_NTS,
    cbAddress = SQL_NTS,
    cbPosition_id = 0,
    cbSalary = 0;

    if (last_name == "") cbLast_name = SQL_NULL_DATA;
    if (first_name == "") cbFirst_name = SQL_NULL_DATA;
    if (patronymic == "") cbPatronymic = SQL_NULL_DATA;
    if (address == "") cbAddress = SQL_NULL_DATA;

    int position_id;
    if (position == nullptr) {
        position_id = -1;
        cbPosition_id = SQL_NULL_DATA;
    } else position_id = position->getId();

    if (salary == -1) cbSalary = SQL_NULL_DATA;

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, last_name.size(), 0,
                              (SQLCHAR*)last_name.c_str(), last_name.size(), &cbLast_name);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for last_name");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, first_name.size(), 0,
                              (SQLCHAR*)first_name.c_str(), first_name.size(), &cbFirst_name);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for first_name");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, patronymic.size(), 0,
                              (SQLCHAR*)patronymic.c_str(), patronymic.size(), &cbPatronymic);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for patronymic");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, address.size(), 0,
                              (SQLCHAR*)address.c_str(), address.size(), &cbAddress);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for address");
    }

    res = SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &position_id, 0, &cbPosition_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for position_id");
    }

    res = SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &salary, 0, &cbSalary);
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

    SQLLEN cbLast_name = SQL_NTS,
    cbFirst_name = SQL_NTS,
    cbPatronymic = SQL_NTS,
    cbAddress = SQL_NTS,
    cbPosition_id = 0,
    cbSalary = 0;

    if (last_name == "") cbLast_name = SQL_NULL_DATA;
    if (first_name == "") cbFirst_name = SQL_NULL_DATA;
    if (patronymic == "") cbPatronymic = SQL_NULL_DATA;
    if (address == "") cbAddress = SQL_NULL_DATA;
    
    int position_id;
    if (position == nullptr) {
        position_id = -1;
        cbPosition_id = SQL_NULL_DATA;
    } else position_id = position->getId();

    if (salary == -1) cbSalary = SQL_NULL_DATA;

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, last_name.size(), 0,
                              (SQLCHAR*)last_name.c_str(), last_name.size(), &cbLast_name);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for last_name");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, first_name.size(), 0,
                              (SQLCHAR*)first_name.c_str(), first_name.size(), &cbFirst_name);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for first_name");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, patronymic.size(), 0,
                              (SQLCHAR*)patronymic.c_str(), patronymic.size(), &cbPatronymic);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for patronymic");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, address.size(), 0,
                              (SQLCHAR*)address.c_str(), address.size(), &cbAddress);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for address");
    }

    res = SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &position_id, 0, &cbPosition_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for position_id");
    }

    res = SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &salary, 0, &cbSalary);
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

Employee* Employee::find(SQLHDBC dbc, int id) {
    
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

    SQLLEN cbId, cbLastName, cbFirstName, cbPatronymic, cbAddress, cbPositionId, cbSalary;
    SQLLEN salary, position_id;
    char lastName[512], firstName[512], patronymic[512], address[512];

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

    if (SQLBindCol(stmt, 1, SQL_C_LONG, &id, 0, &cbId) != SQL_SUCCESS
      || SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*)lastName, 513, &cbLastName) != SQL_SUCCESS
      || SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR*)firstName, 513, &cbFirstName) != SQL_SUCCESS
      || SQLBindCol(stmt, 4, SQL_C_CHAR, (SQLCHAR*)patronymic, 513, &cbPatronymic) != SQL_SUCCESS
      || SQLBindCol(stmt, 5, SQL_C_CHAR, (SQLCHAR*)address, 513, &cbAddress) != SQL_SUCCESS
      || SQLBindCol(stmt, 6, SQL_C_LONG, &position_id, 0, &cbPositionId) != SQL_SUCCESS
      || SQLBindCol(stmt, 7, SQL_C_LONG, &salary, 0, &cbSalary) != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column");
    }

    Employee* employee = new Employee();

    res = SQLFetch(stmt);
    if (res == SQL_SUCCESS) {
        
        if (cbId != SQL_NULL_DATA) employee->id = id;
        if (cbLastName != SQL_NULL_DATA) employee->last_name = std::string((char*)lastName);
        if (cbFirstName != SQL_NULL_DATA) employee->first_name = std::string((char*)firstName);
        if (cbPatronymic != SQL_NULL_DATA) employee->patronymic = std::string((char*)patronymic);
        if (cbAddress != SQL_NULL_DATA) employee->address = std::string((char*)address);
        if (cbPositionId != SQL_NULL_DATA) employee->position = Position::find(dbc, position_id);
        if (cbSalary != SQL_NULL_DATA) employee->salary = salary;
    } else return nullptr;

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return employee;

}

std::map<int, int> Employee::get_values(SQLHDBC dbc) {

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

std::map<int, int> Employee::get_values(SQLHDBC dbc, std::string attribute, std::string value) {

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

void Employee::display(SQLHDBC dbc, std::map<int, int> record_map) {

    std::cout << "  "
              << std::setw(10) << "Id" 
              << std::setw(20) << "Last name" 
              << std::setw(20) << "First name" 
              << std::setw(20) << "Patronymic" 
              << std::setw(40) << "Address"
              << std::setw(20) << "Position" 
              << std::setw(20) << "Salary"
              << std::endl;
    
    for (const auto& [order, id] : record_map) {

        Employee* current = find(dbc, id);

        std::cout << order << "."
                  << std::setw(10) << current->getId()
                  << std::setw(20) << current->getLastName()
                  << std::setw(20) << current->getFirstName()
                  << std::setw(20) << current->getPatronymic()
                  << std::setw(40) << current->getPatronymic()
                  << std::setw(20) << ((current->getPosition() != nullptr) ? current->getPosition()->getName() : "")
                  << std::setw(20) << ((current->getSalary() != -1) ? std::to_string(current->getSalary()) : "")
                  << std::endl;
        
    }
}