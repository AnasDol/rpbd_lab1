#include "menu.hpp"

int option_add_new_animal(SQLHDBC dbc) {

    std::string name;
    int age;
    std::string gender;
    int breed_id;
    std::string appearance;
    int client_id;
    //int vet_id;

    int option;

    std::cout << "Name: ";
    //std::cin >> name;
    getline(std::cin, name);

    std::cout << "Age: ";
    std::cin >> age;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    std::cout << "Select gender:\n";
    std::cout << "\t1. male\n\t2. female\n> ";
    std::cin >> option;
    if (!std::cin.good() || (option != 1 && option != 2)) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    switch (option)
    {
    case 1:
        gender = "male";
        break;
    case 2:
        gender = "female";
        break;
    
    default:
        break;
    }

    std::cout << "Select breed:\n";
    print_table(dbc, "breeds");
    std::cout << /*Breed::get_record_num(dbc)+1*/Breed::get_last_inserted_id(dbc)+1 << ". Add new breed\n> ";
    std::cin >> breed_id; // позднее переделать на логический номер

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    try {
        Breed breed = Breed::find_by_id(dbc, breed_id);
    } catch (std::runtime_error const& e) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    if (breed_id == /*Breed::get_record_num(dbc)+1*/Breed::get_last_inserted_id(dbc)+1) {
        breed_id = option_add_new_breed(dbc);
    }

    std::cout << "Appearance: ";
    getline(std::cin, appearance);

    std::cout << "Select client:\n";
    print_table(dbc, "clients");
    std::cin >> client_id;
    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    try {
        Client client = Client::find_by_id(dbc, client_id);
    } catch (std::runtime_error const& e) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    if (client_id == /*Breed::get_record_num(dbc)+1*/Client::get_last_inserted_id(dbc)+1) {
        client_id = option_add_new_client(dbc);
    }





    // ...

    return 0; // будет возвращаться id

}

int option_add_new_breed(SQLHDBC dbc) {

    std::string name;

    std::cout << "Breed name: ";
    std::cin >> name;

    Breed new_record;
    new_record.setName(name);

    try {
        new_record.insert(dbc);
        std::cout << "New entry added to breeds.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to add new entry to breeds.\n";
        return -1;
    }

    return new_record.getId();

}

int option_add_new_client(SQLHDBC dbc) {

    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string address;

    std::cout << "Client last name: ";
    getline(std::cin, last_name);

    std::cout << "Client first name: ";
    getline(std::cin, first_name);

    std::cout << "Client patronymic: ";
    getline(std::cin, patronymic);

    std::cout << "Client address: ";
    getline(std::cin, address);

    Client new_record;
    new_record.setLastName(last_name);
    new_record.setFirstName(first_name);
    new_record.setPatronymic(patronymic);
    new_record.setAddress(address);

    try {
        new_record.insert(dbc);
        std::cout << "New entry added to clients.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to add new entry to clients.\n";
        return -1;
    }

    return new_record.getId();

}

void option_insert_new_record(SQLHDBC dbc) {

    std::cout << "Select table:\n";
    print_table_list();

    int option;
    std::cin >> option;
    switch (option)
    {
    case 1:
    {
        std::cout << "Name: ";
        std::string name;
        std::cin >> name;
        Breed new_record;
        new_record.setName(name);
        new_record.insert(dbc);

    }  
        break;
    
    default:
        std::cout << "Wrong input!\n";
        break;
    }

}

// void option_update_record(SQLHDBC dbc) {

//     std::cout << "Select table:\n";
//     print_table_list();

//     Table option;
//     std::cin >> option;
//     switch (option)
//     {
//     case Table::BREEDS:
//     {
//         std::cout << "Input row number: ";
//         int number;
//         std::cin >> number;

//         std::cout << "Select parameter to update: \n";
//         //print_parameter_list(option);

//     }  
//         break;
    
//     default:
//         std::cout << "Wrong input!\n";
//         break;
//     }

// }


void print_table_list() {
    std::cout << "1. BREEDS\n";
    std::cout << "2. CLIENTS\n";
    std::cout << "3. EMPLOYEES\n";
    std::cout << "4. ANIMALS\n";
    std::cout << "5. EXHIBITIONS\n";
    std::cout << "6. PEDIGREE\n";
    std::cout << "7. PARTICIPATIONS\n";
    std::cout << "8. REQUESTS\n";
}