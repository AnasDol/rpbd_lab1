#include "Animal.hpp"

void Animal::insert(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "INSERT INTO " + table_name + " (name, age, gender, breed_id, appearance, client_id, vet_id, mother_id, father_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?) RETURNING id";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    SQLLEN cbName = SQL_NTS,
    cbAge = 0,
    cbGender = SQL_NTS,
    cbBreed_id = 0,
    cbAppearance = SQL_NTS,
    cbClient_id = 0,
    cbVet_id = 0,
    cbMother_id = 0,
    cbFather_id = 0;

    int breed_id, client_id, vet_id, mother_id, father_id;

    if (name == "") cbName = SQL_NULL_DATA;
    if (age == -1) cbAge = SQL_NULL_DATA;
    if (gender == "") cbGender = SQL_NULL_DATA;

    if (breed == nullptr) {
        breed_id = -1;
        cbBreed_id = SQL_NULL_DATA;
    } else breed_id = breed->getId();

    if (appearance == "") cbAppearance = SQL_NULL_DATA;

    if (client == nullptr) {
        client_id = -1;
        cbClient_id = SQL_NULL_DATA;
    } else client_id = client->getId();

    if (vet == nullptr) {
        vet_id = -1;
        cbVet_id = SQL_NULL_DATA;
    } else vet_id = vet->getId();

    if (mother == nullptr) {
        mother_id = -1;
        cbMother_id = SQL_NULL_DATA;
    } else mother_id = mother->getId();

    if (father == nullptr) {
        father_id = -1;
        cbFather_id = SQL_NULL_DATA;
    } else father_id = father->getId();

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, name.size(), 0, (SQLCHAR*)name.c_str(), name.size(), &cbName);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for name");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &age, 0, &cbAge);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for age");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, gender.size(), 0, (SQLCHAR*)gender.c_str(), gender.size(), &cbGender);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for gender");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &breed_id, 0, &cbBreed_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for breed_id");
    }

    res = SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, appearance.size(), 0, (SQLCHAR*)appearance.c_str(), appearance.size(), &cbAppearance);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for appearance");
    }

    res = SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &client_id, 0, &cbClient_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for client_id");
    }

    res = SQLBindParameter(stmt, 7, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &vet_id, 0, &cbVet_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for vet_id");
    }

    res = SQLBindParameter(stmt, 8, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &mother_id, 0, &cbMother_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for mother_id");
    }

    res = SQLBindParameter(stmt, 9, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &father_id, 0, &cbFather_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for father_id");
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

void Animal::update(SQLHDBC dbc) {

    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
      throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "UPDATE " + table_name + " SET name = ?, age = ?, gender = ?, breed_id = ?, appearance = ?, client_id = ?, vet_id = ?, mother_id = ?, father_id = ? WHERE id = ?";
    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    SQLLEN cbName = SQL_NTS,
    cbAge = 0,
    cbGender = SQL_NTS,
    cbBreed_id = 0,
    cbAppearance = SQL_NTS,
    cbClient_id = 0,
    cbVet_id = 0,
    cbMother_id = 0,
    cbFather_id = 0;

    int breed_id, client_id, vet_id, mother_id, father_id;

    if (name == "") cbName = SQL_NULL_DATA;
    if (age == -1) cbAge = SQL_NULL_DATA;
    if (gender == "") cbGender = SQL_NULL_DATA;

    if (breed == nullptr) {
        breed_id = -1;
        cbBreed_id = SQL_NULL_DATA;
    } else breed_id = breed->getId();

    if (appearance == "") cbAppearance = SQL_NULL_DATA;

    if (client == nullptr) {
        client_id = -1;
        cbClient_id = SQL_NULL_DATA;
    } else client_id = client->getId();

    if (vet == nullptr) {
        vet_id = -1;
        cbVet_id = SQL_NULL_DATA;
    } else vet_id = vet->getId();

    if (mother == nullptr) {
        mother_id = -1;
        cbMother_id = SQL_NULL_DATA;
    } else mother_id = mother->getId();

    if (father == nullptr) {
        father_id = -1;
        cbFather_id = SQL_NULL_DATA;
    } else father_id = father->getId();

    res = SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, name.size(), 0, (SQLCHAR*)name.c_str(), name.size(), &cbName);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for name");
    }

    res = SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &age, 0, &cbAge);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for age");
    }

    res = SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, gender.size(), 0, (SQLCHAR*)gender.c_str(), gender.size(), &cbGender);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for gender");
    }

    res = SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &breed_id, 0, &cbBreed_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for breed_id");
    }

    res = SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, appearance.size(), 0, (SQLCHAR*)appearance.c_str(), appearance.size(), &cbAppearance);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for appearance");
    }

    res = SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &client_id, 0, &cbClient_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for client_id");
    }

    res = SQLBindParameter(stmt, 7, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &vet_id, 0, &cbVet_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for vet_id");
    }

    res = SQLBindParameter(stmt, 8, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &mother_id, 0, &cbMother_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for mother_id");
    }

    res = SQLBindParameter(stmt, 9, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &father_id, 0, &cbFather_id);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind parameter for father_id");
    }

    res = SQLBindParameter(stmt, 10, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &id, 0, nullptr);
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

void Animal::remove(SQLHDBC dbc) {
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

Animal* Animal::find(SQLHDBC dbc, int id) {
    SQLHSTMT stmt;
    SQLRETURN res = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    if (res != SQL_SUCCESS) {
        throw std::runtime_error("Failed to allocate statement handle");
    }

    std::string query = "SELECT id, name, age, gender, breed_id, appearance, client_id, vet_id, mother_id, father_id FROM " + table_name + " WHERE id = ?";

    res = SQLPrepare(stmt, (SQLCHAR *)query.c_str(), SQL_NTS);
    if (res != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to prepare SQL statement");
    }

    SQLLEN cbId, cbName, cbAge, cbGender, cbBreedId, cbAppearance, cbClientId, cbVetId, cbMotherId, cbFatherId;
    SQLLEN age, breed_id, client_id, vet_id, mother_id, father_id;
    SQLCHAR name[512], gender[512], appearance[512];

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
      || SQLBindCol(stmt, 2, SQL_C_CHAR, name, sizeof(name), &cbName) != SQL_SUCCESS
      || SQLBindCol(stmt, 3, SQL_C_LONG, &age, 0, &cbAge) != SQL_SUCCESS
      || SQLBindCol(stmt, 4, SQL_C_CHAR, gender, sizeof(gender), &cbGender) != SQL_SUCCESS
      || SQLBindCol(stmt, 5, SQL_C_LONG, &breed_id, 0, &cbBreedId) != SQL_SUCCESS
      || SQLBindCol(stmt, 6, SQL_C_CHAR, appearance, sizeof(appearance), &cbAppearance) != SQL_SUCCESS
      || SQLBindCol(stmt, 7, SQL_C_LONG, &client_id, 0, &cbClientId) != SQL_SUCCESS
      || SQLBindCol(stmt, 8, SQL_C_LONG, &vet_id, 0, &cbVetId) != SQL_SUCCESS
      || SQLBindCol(stmt, 9, SQL_C_LONG, &mother_id, 0, &cbMotherId) != SQL_SUCCESS
      || SQLBindCol(stmt, 10, SQL_C_LONG, &father_id, 0, &cbFatherId) != SQL_SUCCESS) {
      SQLFreeHandle(SQL_HANDLE_STMT, stmt);
      throw std::runtime_error("Failed to bind column");
    }

    Animal* animal = new Animal();

    res = SQLFetch(stmt);
    if (res == SQL_SUCCESS) {
        
        if (cbId != SQL_NULL_DATA) animal->id = id;
        if (cbName != SQL_NULL_DATA) animal->name = std::string((char*)name);
        if (cbAge != SQL_NULL_DATA) animal->age = age;
        if (cbGender != SQL_NULL_DATA) animal->gender = std::string((char*)gender);
        if (cbBreedId != SQL_NULL_DATA) animal->breed = Breed::find(dbc, breed_id);
        if (cbAppearance != SQL_NULL_DATA) animal->appearance = std::string((char*)appearance);
        if (cbClientId != SQL_NULL_DATA) animal->client = Client::find(dbc, client_id);
        if (cbVetId != SQL_NULL_DATA) animal->vet = Employee::find(dbc, vet_id);
        if (cbMotherId != SQL_NULL_DATA) animal->mother = Animal::find(dbc, mother_id);
        if (cbFatherId != SQL_NULL_DATA) animal->father = Animal::find(dbc, father_id);
    } 
    else if (res == SQL_NO_DATA) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        //throw std::runtime_error("No such animal with given id");
        return nullptr;
    } 
    else {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Failed to fetch data");
        return nullptr;
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    return animal;
}

std::map<int, int> Animal::get_values(SQLHDBC dbc) {

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

std::map<int, int> Animal::get_values(SQLHDBC dbc, std::string attribute, std::string value) {

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

void Animal::display(SQLHDBC dbc, std::map<int, int> record_map) {
    
    std::cout << "  "
              << std::setw(10) << "Id" 
              << std::setw(15) << "Name" 
              << std::setw(10) << "Age" 
              << std::setw(10) << "Gender" 
              << std::setw(15) << "Breed"
              << std::setw(15) << "Appearance" 
              << std::setw(15) << "Client"
              << std::setw(15) << "Vet" 
              << std::setw(15) << "Mother"
              << std::setw(15) << "Father" 
              << std::endl;

    
    for (const auto& [order, id] : record_map) {

        Animal* current = find(dbc, id);

        std::cout << order << "."
                  << std::setw(10) << current->getId()
                  << std::setw(15) << current->getName()
                  << std::setw(10) << ((current->getAge() != -1) ? std::to_string(current->getAge()) : "")
                  << std::setw(10) << current->getGender()
                  << std::setw(15) << ((current->getBreed() != nullptr) ? current->getBreed()->getName() : "")
                  << std::setw(15) << current->getAppearance()
                  << std::setw(15) << ((current->getClient() != nullptr) ? current->getClient()->getLastName() + " " + current->getClient()->getFirstName() : "")
                  << std::setw(15) << ((current->getVet() != nullptr) ? current->getVet()->getLastName() + " " + current->getVet()->getFirstName() : "")
                  << std::setw(15) << ((current->getMother() != nullptr) ? current->getMother()->getName() : "")
                  << std::setw(15) << ((current->getFather() != nullptr) ? current->getFather()->getName() : "")
                  << std::endl;
        
    }
    
}