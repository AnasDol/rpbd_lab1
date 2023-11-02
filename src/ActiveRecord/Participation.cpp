#include "Participation.hpp"

void Participation::insert(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query =
        "INSERT INTO " + table_name + " (animal_id, exhibition_id, reward) VALUES (?, ?, ?)";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    SQLLEN cbAnimal_id = 0, cbExhibition_id = 0, cbReward = SQL_NTS;

    int animal_id, exhibition_id;

    //if (reward == "") cbReward = SQL_NULL_DATA;

    if (animal == nullptr) {
        //animal_id = -1;
        cbAnimal_id = SQL_NULL_DATA;
    } else animal_id = animal->getId();

    if (exhibition == nullptr) {
        //exhibition_id = -1;
        cbExhibition_id = SQL_NULL_DATA;
    } else exhibition_id = exhibition->getId();


    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &animal_id, 0, &cbAnimal_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for animal_id");
    }


    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &exhibition_id, 0, &cbExhibition_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for exhibition_id");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           reward.size(), 0, (SQLCHAR *)reward.c_str(),
                           reward.size(), &cbReward);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for reward");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Participation::update(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query =
        "UPDATE " + table_name + " SET animal_id = ?, exhibition_id = ?, reward = ? WHERE animal_id = ? AND exhibition_id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

        SQLLEN cbAnimal_id = 0, cbExhibition_id = 0, cbReward = SQL_NTS;

    int animal_id, exhibition_id;

    if (reward == "") cbReward = SQL_NULL_DATA;

    if (animal == nullptr) {
        animal_id = -1;
        cbAnimal_id = SQL_NULL_DATA;
    } else animal_id = animal->getId();

    if (exhibition == nullptr) {
        exhibition_id = -1;
        cbExhibition_id = SQL_NULL_DATA;
    } else exhibition_id = exhibition->getId();


    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &animal_id, 0, &cbAnimal_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for animal_id");
    }


    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &exhibition_id, 0, &cbExhibition_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for exhibition_id");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                           reward.size(), 0, (SQLCHAR *)reward.c_str(),
                           reward.size(), &cbReward);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind parameter for reward");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &animal_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for animal_id");
    }

    res = SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &exhibition_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for exhibition_id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

void Participation::remove(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "DELETE FROM " + table_name + " WHERE animal_id = ? AND exhibition_id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    SQLLEN cbAnimal_id = 0, cbExhibition_id = 0;

    int animal_id = -1, exhibition_id = -1;

    if (animal != nullptr) animal_id = animal->getId();

    if (exhibition != nullptr) exhibition_id = exhibition->getId();

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &animal_id, 0, &cbAnimal_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for animal_id");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &exhibition_id, 0, &cbExhibition_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for exhibition_id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

Participation* Participation::find(SQLHDBC dbc, int animal_id, int exhibition_id) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM " + table_name + " WHERE animal_id = ? AND exhibition_id = ?";

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &animal_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for animal_id");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &exhibition_id, 0, NULL);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for exhibition_id");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to execute SQL statement");
    }

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &animal_id, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for animal_id");
    }

    res = SQLBindCol(stmt, 2, SQL_C_LONG, &exhibition_id, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for exhibition_id");
    }

    char reward_buf[255];
    SQLLEN reward_len;

    res = SQLBindCol(stmt, 3, SQL_C_CHAR, reward_buf, sizeof(reward_buf), &reward_len);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for reward");
    }

    Participation* participation = new Participation();

    res = SQLFetch(stmt);
    if (res == SQL_SUCCESS) {
        participation->setReward(std::string(reward_buf, reward_len));
        participation->setAnimal(Animal::find(dbc, animal_id));
        participation->setExhibition(Exhibition::find(dbc, exhibition_id));
    }
    else if (res == SQL_NO_DATA) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        //throw std::runtime_error("No such animal with given id");
        return nullptr;
    } 
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to fetch data");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return participation;
}

std::map<int, pair> Participation::get_values(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM " + table_name;

    std::map<int, pair> recordMap;
    int animalId, exhibitionId;

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to prepare SQL statement");
    }

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &animalId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for animalId");
    }

    res = SQLBindCol(stmt, 2, SQL_C_LONG, &exhibitionId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for exhibitionId");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }

    int rowNum = 1;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        recordMap.insert({rowNum, {animalId, exhibitionId}});
        rowNum++;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return recordMap;
}

std::map<int, pair> Participation::get_values(SQLHDBC dbc, std::string attribute, std::string value) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT * FROM " + table_name + " WHERE " + attribute + " = ?";

    std::map<int, pair> recordMap;
    int animalId, exhibitionId;

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

    res = SQLBindCol(stmt, 1, SQL_C_LONG, &animalId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for animalId");
    }

    res = SQLBindCol(stmt, 2, SQL_C_LONG, &exhibitionId, 0, nullptr);
    if (res != SQL_SUCCESS) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to bind column for exhibitionId");
    }

    res = SQLExecute(stmt);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to execute SQL statement");
    }

    int rowNum = 1;
    while (SQLFetch(stmt) == SQL_SUCCESS) {
        recordMap.insert({rowNum, {animalId, exhibitionId}});
        rowNum++;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return recordMap;

}

void Participation::display(SQLHDBC dbc, std::map<int, pair> record_map) {
    
    std::cout << "  "
              << std::setw(20) << "Animal Id" 
              << std::setw(20) << "Exhibition Id" 
              << std::setw(20) << "Reward"
              << std::endl;

    for (const auto& [order, p] : record_map) {

        SQLHSTMT hstmt;
        SQLRETURN retcode;

        retcode = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &hstmt);

        if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
            std::cout << "Failed to allocate handle." << std::endl;
            return;
        }

        std::string query = "SELECT * FROM " + table_name + " WHERE animal_id = " + std::to_string(p.first) + " AND exhibition_id = " + std::to_string(p.second);

        retcode = SQLExecDirect(hstmt, (SQLCHAR*)(query.c_str()), SQL_NTS);

        if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
            std::cout << "Failed to execute query." << std::endl;
            continue;
        }

        while (SQLFetch(hstmt) == SQL_SUCCESS) {

            SQLCHAR reward[64];

            SQLGetData(hstmt, 4, SQL_C_CHAR, &reward, sizeof(reward), nullptr);

            std::cout << order << "."
                << std::setw(20) << p.first
                << std::setw(20) << p.second
                << std::setw(20) << reward
                << std::endl;
        }   

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);       
    }
    
}