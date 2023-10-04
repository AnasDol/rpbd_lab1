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

    std::string create_query = "DO $$ BEGIN IF NOT EXISTS (SELECT 1 FROM pg_type WHERE typname = 'gen') THEN CREATE TYPE gen AS ENUM ('male', 'female'); END IF; END$$; create table if not exists breeds(id serial PRIMARY KEY, name text UNIQUE); create table if not exists clients(id serial PRIMARY KEY, last_name text NOT NULL, first_name text NOT NULL, patronymic text, address text); create table if not exists positions(id serial PRIMARY KEY, name text UNIQUE NOT NULL); create table if not exists employees(id serial PRIMARY KEY, last_name text NOT NULL, first_name text NOT NULL, patronymic text, address text, position_id integer REFERENCES positions(id) ON DELETE CASCADE, salary money); create table if not exists animals(id serial PRIMARY KEY, name text, age integer CHECK (age > 0), gender gen, breed_id integer REFERENCES breeds(id) ON DELETE CASCADE, appearance text, client_id integer REFERENCES clients(id) ON DELETE CASCADE, vet_id integer REFERENCES employees(id) ON DELETE CASCADE); create table if not exists pedigree(parent_id integer REFERENCES animals(id) ON DELETE CASCADE, child_id integer REFERENCES animals(id) ON DELETE CASCADE); create table if not exists exhibitions(id serial PRIMARY KEY, name text, address text, exhibition_date date); create table if not exists participations(animal_id integer NOT NULL REFERENCES animals(id) ON DELETE CASCADE, exhibition_id integer NOT NULL REFERENCES exhibitions(id) ON DELETE CASCADE, reward text, PRIMARY KEY (animal_id, exhibition_id)); create table if not exists requests(id serial PRIMARY KEY, client_id integer REFERENCES clients(id) ON DELETE CASCADE, breed_id integer REFERENCES breeds(id) ON DELETE CASCADE, gender gen, request_date date);";

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

int get_record_num(SQLHDBC dbc, const std::string& table_name) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    // Выполнение команды SQL для получения числа строк в таблице
    std::string query = "SELECT COUNT(*) FROM " + table_name;
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        throw std::runtime_error("Failed to allocate statement handle");
    }
    ret = SQLExecDirect(stmt, (SQLCHAR*)(query.c_str()), SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    // Получение результата запроса
    SQLLEN rowCount;
    ret = SQLFetch(stmt);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        ret = SQLGetData(stmt, 1, SQL_C_LONG, &rowCount, 0, NULL);
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            throw std::runtime_error("Failed to get result data");
        }
    } else {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to fetch result data");
    }

    // Освобождение ресурсов и возвращение результата
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return static_cast<int>(rowCount);
}

std::list<std::string> get_enum_values(SQLHDBC dbc, const std::string &enum_type_name) {
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string select_query = "SELECT e.enumlabel as enum_value"
                        " FROM pg_type t "
                        " JOIN pg_enum e ON t.oid = e.enumtypid"
                        " WHERE t.typname = " + enum_type_name;

    ret = SQLExecDirect(stmt, (SQLCHAR*)select_query.c_str(), SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    std::list<std::string> values;

    //Fetch enum values
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        SQLCHAR buff[255];
        SQLGetData(stmt, 1, SQL_C_CHAR, &buff, sizeof(buff), NULL);
        values.push_back(std::string((char*)buff));
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return values;
}

std::list<std::string> get_values(SQLHDBC dbc, const std::string &table_name) {
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLSMALLINT num_columns;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(dbc, SQL_HANDLE_DBC);
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string select_query = "SELECT * FROM " + table_name;
    ret = SQLExecDirect(stmt, (SQLCHAR*)select_query.c_str(), SQL_NTS);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    ret = SQLNumResultCols(stmt, &num_columns);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        show_error(stmt, SQL_HANDLE_STMT);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to retrieve number of columns");
    }

    std::list<std::string> rows;

    //Fetch table data
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        std::string row = "";
        for (SQLUSMALLINT i = 1; i <= num_columns; i++) {
            SQLLEN value_len;
            SQLCHAR value[128];
            ret = SQLGetData(stmt, i, SQL_C_CHAR, value, sizeof(value), &value_len);
            if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
                show_error(stmt, SQL_HANDLE_STMT);
                SQLFreeHandle(SQL_HANDLE_STMT, stmt);
                throw std::runtime_error("Failed to retrieve data");
            }
            row += (i > 1 ? "\t" : "") + std::string((char*)value);
        }
        rows.push_back(row);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return rows;
}

int countRecords(SQLHDBC dbc, const std::string& tableName, const std::string& attributeName, const std::string& attributeValue) {
    SQLRETURN ret;  // Переменная для хранения возвращаемого значения функций ODBC
    SQLHSTMT stmt;  // Объект ODBC для выполнения SQL-запросов

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);  // Выделение памяти для объекта ODBC
    if (ret != SQL_SUCCESS) {
        std::cerr << "Failed to allocate statement handle." << std::endl;
        return -1;  // Возвращаем -1 в случае ошибки
    }

    // Создание SQL-запроса с использованием переданных параметров
    std::string query = "SELECT COUNT(*) FROM " + tableName + " WHERE " + attributeName + " = ?";
    ret = SQLPrepare(stmt, (SQLCHAR*)(query.data()), SQL_NTS);  // Подготовка SQL-запроса
    if (ret != SQL_SUCCESS) {
        std::cerr << "Failed to prepare SQL statement." << std::endl;
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);  // Освобождаем выделенную память перед выходом
        return -1;
    }

    // Привязка значения атрибута к параметру в SQL-запросе
    ret = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, attributeValue.size(), 0,
                           (SQLCHAR*)(attributeValue.data()), attributeValue.size(), nullptr);
    if (ret != SQL_SUCCESS) {
        std::cerr << "Failed to bind parameter." << std::endl;
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);  // Освобождаем выделенную память перед выходом
        return -1;
    }

    // Выполнение SQL-запроса
    ret = SQLExecute(stmt);
    if (ret != SQL_SUCCESS) {
        std::cerr << "Failed to execute SQL statement." << std::endl;
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);  // Освобождаем выделенную память перед выходом
        return -1;
    }

    // Получение результата запроса
    SQLLEN count;
    ret = SQLFetch(stmt);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        ret = SQLGetData(stmt, 1, SQL_C_LONG, &count, sizeof(count), nullptr);  // Получаем значение числа записей
        if (ret != SQL_SUCCESS) {
            std::cerr << "Failed to retrieve data." << std::endl;
            count = -1;
        }
    } else {
        std::cerr << "Failed to fetch data." << std::endl;
        count = -1;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);  // Освобождаем выделенную память
    return count;
}