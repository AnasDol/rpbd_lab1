#include "menu.hpp"

void start(SQLHDBC dbc) {

    int option;
    do {
        std::cout << "-------- Choose option --------\n";
        std::cout << "\n";
        std::cout << "0. Show data\n";
        std::cout << "\n";
        std::cout << "1. Add new animal\n";
        std::cout << "2. Add new breed\n";
        std::cout << "3. Add new client\n";
        std::cout << "4. Add new employee\n";
        std::cout << "5. Add new position\n";
        std::cout << "6. Add new exhibition\n";
        std::cout << "\n";
        std::cout << "7. Create new request\n";
        std::cout << "\n";
        std::cout << "8. Enter data on the participation of animals in exhibitions\n";
        std::cout << "9. Enter pedigree information\n";
        std::cout << "\n";
        std::cout << "11. Update animal\n";
        std::cout << "12. Update breed\n";
        std::cout << "13. Update client\n";
        std::cout << "14. Update employee\n";
        std::cout << "15. Update position\n";
        std::cout << "16. Update exhibition\n";
        std::cout << "17. Update request\n";
        std::cout << "\n";
        std::cout << "18. Update data on the participation of animals in exhibitions\n";
        //std::cout << "19. Update pedigree information\n";
        std::cout << "\n";
        std::cout << "21. Delete animal\n";
        std::cout << "22. Delete breed\n";
        std::cout << "23. Delete client\n";
        std::cout << "24. Delete employee\n";
        std::cout << "25. Delete position\n";
        std::cout << "26. Delete exhibition\n";
        std::cout << "27. Delete request\n";
        std::cout << "\n";
        std::cout << "28. Delete data on the participation of animals in exhibitions\n";
        //std::cout << "29. Delete pedigree information\n";
        std::cout << "\n";
        std::cout << "-1. Exit\n";
        std::cout << "-------------------------------\n";
        std::cout << "\n> ";

        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> option;

        proceed(dbc, option);

        getchar();

        
    } while (option != -1);

}

void proceed(SQLHDBC dbc, int option) {

    switch (option)
    {
    case 0:
        option_show_data(dbc);
        break;
    case 1:
        option_add_new_animal(dbc);
        break;
    case 2:
        option_add_new_breed(dbc);
        break;
    case 3:
        option_add_new_client(dbc);
        break;
    case 4:
        option_add_new_employee(dbc);
        break;
    case 5:
        option_add_new_position(dbc);
        break;
    case 6:
        option_add_new_exhibition(dbc);
        break;
    case 7:
        option_add_new_request(dbc);
        break;
    case 8:
        option_add_new_participation(dbc);
        break;
    case 9:
        option_add_new_pedigree_info(dbc);
        break;

    case 11:
        option_update_animal(dbc);
        break;
    case 12:
        option_update_breed(dbc);
        break;
    case 13:
        option_update_client(dbc);
        break;
    case 14:
        option_update_employee(dbc);
        break;
    case 15:
        option_update_position(dbc);
        break;
    case 16:
        option_update_exhibition(dbc);
        break;
    case 17:
        option_update_request(dbc);
        break;
    case 18:
        option_update_participation(dbc);
        break;
    case 19:
        //option_update_pedigree_info(dbc);
        break;
    
    case 21:
        option_remove_animal(dbc);
        break;
    case 22:
        option_remove_breed(dbc);
        break;
    case 23:
        option_remove_client(dbc);
        break;
    case 24:
        option_remove_employee(dbc);
        break;
    case 25:
        option_remove_position(dbc);
        break;
    case 26:
        option_remove_exhibition(dbc);
        break;
    case 27:
        option_remove_request(dbc);
        break;
    case 28:
        option_remove_participation(dbc);
        break;
    case 29:
        //option_remove_pedigree_info(dbc);
        break;
    

    default:
        break;
    }

}

int option_add_new_animal(SQLHDBC dbc) {

    std::string name;
    int age;
    std::string gender;
    int breed_id;
    std::string appearance;
    int client_id;
    int vet_id;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Name: ";
    getline(std::cin, name);

    std::cout << "Age: ";
    std::cin >> age;

    if (!std::cin.good() || age < 0) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    gender = select_gender();
    if (gender == "") {
        return -1;
    }

    breed_id = select_breed(dbc);
    if (breed_id == -1) {
        return -1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Appearance: ";
    getline(std::cin, appearance);

    client_id = select_client(dbc);
    if (client_id == -1) {
        return -1;
    }

    vet_id = select_vet(dbc);
    if (vet_id == -1) {
        return -1;
    }

    Animal new_record;
    new_record.setName(name);
    new_record.setAge(age);
    new_record.setGender(gender);
    new_record.setBreed(Breed::find(dbc, breed_id));
    new_record.setAppearance(appearance);
    new_record.setClient(Client::find(dbc, client_id));
    new_record.setVet(Employee::find(dbc, vet_id));

    try {
        new_record.insert(dbc);
        std::cout << "New entry added to animals.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to add new entry to animals.\nError occured: " << e.what() << "\n";
        return -1;
    }

    std::cout << "Do you want to enter information about participations in exhibitions? (y/n)\n> ";
    char enter = '?';
    std::cin >> enter;
    if (!std::cin.good() || (enter != 'y' && enter != 'Y' && enter != 'n' && enter != 'N')) {
        std::cout << "Wrong input.\n";
    } else if (enter == 'y' || enter == 'Y') {
        option_add_new_participation(dbc, new_record.getId());
    }

    return new_record.getId();

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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, last_name);

    std::cout << "Client first name: ";
    getline(std::cin, first_name);

    std::cout << "Client patronymic: ";
    std::cin.clear();
    getline(std::cin, patronymic);

    std::cout << "Client address: ";
    std::cin.clear();
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

int option_add_new_employee(SQLHDBC dbc) {

    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string address;
    int position_id;
    int salary;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Employee last name: ";
    getline(std::cin, last_name);

    std::cout << "Employee first name: ";
    getline(std::cin, first_name);

    std::cout << "Employee patronymic: ";
    getline(std::cin, patronymic);

    std::cout << "Employee address: ";
    getline(std::cin, address);

    position_id = select_position(dbc);
    if (position_id == -1) {
        return -1;
    }

    std::cout << "Salary: ";
    std::cin >> salary;

    if (!std::cin.good() || salary < 0) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    Employee new_record;
    new_record.setLastName(last_name);
    new_record.setFirstName(first_name);
    new_record.setPatronymic(patronymic);
    new_record.setAddress(address);
    new_record.setPosition(Position::find(dbc, position_id));
    new_record.setSalary(salary);

    try {
        new_record.insert(dbc);
        std::cout << "New entry added to employees.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to add new entry to employees.\n";
        return -1;
    }

    return new_record.getId();

}

int option_add_new_vet(SQLHDBC dbc) {

    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string address;
    int salary;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Employee last name: ";
    getline(std::cin, last_name);

    std::cout << "Employee first name: ";
    getline(std::cin, first_name);

    std::cout << "Employee patronymic: ";
    getline(std::cin, patronymic);

    std::cout << "Employee address: ";
    getline(std::cin, address);

    Position* pos = new Position();
    std::map<int,int> vet = Position::get_values(dbc, "name", "vet");
    if (vet.size() == 0) {
        pos->setName("vet");
        pos->insert(dbc);
    } else {
        pos = Position::find(dbc, vet[1]);
    }

    std::cout << "Salary: ";
    std::cin >> salary;

    if (!std::cin.good() || salary < 0) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    Employee new_record;
    new_record.setLastName(last_name);
    new_record.setFirstName(first_name);
    new_record.setPatronymic(patronymic);
    new_record.setAddress(address);
    new_record.setPosition(pos);
    new_record.setSalary(salary);

    try {
        new_record.insert(dbc);
        std::cout << "New entry added to employees.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to add new entry to employees.\nError occured: "<< e.what();
        return -1;
    }

    return new_record.getId();

}

int option_add_new_position(SQLHDBC dbc) {

    std::string name;

    std::cout << "Position name: ";
    std::cin >> name;

    Position new_record;
    new_record.setName(name);

    try {
        new_record.insert(dbc);
        std::cout << "New entry added to positions.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to add new entry to positions.\n";
        return -1;
    }

    return new_record.getId();

}

int option_add_new_request(SQLHDBC dbc) {

    int client_id;
    int breed_id;
    std::string gender;
    int day, month, year;

    client_id = select_client(dbc);
    if (client_id == -1) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    breed_id = select_breed(dbc);
    if (breed_id == -1) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    gender = select_gender();
    if (gender == "") {
        std::cout << "Wrong input.\n";
        return -1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (select_date(&day, &month, &year) == -1) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    Request new_record(nullptr, nullptr, gender, day, month, year);
    new_record.setClient(Client::find(dbc, client_id));
    new_record.setBreed(Breed::find(dbc, breed_id));

    try {
        new_record.insert(dbc);
        std::cout << "New entry added to requests.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to add new entry to requests.\n";
        return -1;
    }

    return new_record.getId();

}

int option_add_new_exhibition(SQLHDBC dbc) { 

    std::string name;
    std::string address;
    int day, month, year;

    std::cout << "Exhibition name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, name);

    std::cout << "Exhibition address: ";
    getline(std::cin, address);

    if (select_date(&day, &month, &year) == -1) {
        return -1;
    }

    Exhibition new_record(name, address, day, month, year);

    try {
        new_record.insert(dbc);
        std::cout << "New entry added to exhibitions.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to add new entry to exhibitions.\n";
        return -1;
    }

    return new_record.getId();
}

int option_add_new_participation(SQLHDBC dbc) { 
    
    int animal_id, exhibition_id;
    std::string reward;

    animal_id = select_animal(dbc);
    if (animal_id == -1) {
        return -1;
    } 

    char enter = '?';

    do {

        exhibition_id = select_exhibition(dbc);
        if (exhibition_id == -1) {
            return -1;
        }

        Participation* participation = Participation::find(dbc, animal_id, exhibition_id);

        if (participation != nullptr) {
            std::cout << "Selected animal has already taken part in the selected exhibition.\n";
            return -1;
        }

        std::cout << "Reward: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, reward);

        participation = new Participation();
        participation->setAnimal(Animal::find(dbc, animal_id));
        participation->setExhibition(Exhibition::find(dbc, exhibition_id));
        participation->setReward(reward);

        try {
            participation->insert(dbc);
            std::cout << "New entry added to participations.\n";
        } catch (std::runtime_error const& e) {
            std::cout << "Failed to add new entry to participations.\n";
            return -1;
        }

        std::cout << "Do you want to add another exhibition? (y/n)\n> ";
        std::cin >> enter;
        if (!std::cin.good() || (enter != 'y' && enter != 'Y' && enter != 'n' && enter != 'N')) {
            std::cout << "Wrong input.\n";
            return -1;
        }

    } while (enter == 'Y' || enter == 'y');

    return 0;
}

int option_add_new_participation(SQLHDBC dbc, int animal_id) { 
    
    int exhibition_id;
    std::string reward;

    char enter = '?';

    do {

        exhibition_id = select_exhibition(dbc);
        if (exhibition_id == -1) {
            return -1;
        }

        Participation* participation = Participation::find(dbc, animal_id, exhibition_id);
    
        if (participation != nullptr) {
            std::cout << "Selected animal has already taken part in the selected exhibition.\n";
            return -1;
        }


        std::cout << "Reward: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, reward);

        participation = new Participation();
        participation->setAnimal(Animal::find(dbc, animal_id));
        participation->setExhibition(Exhibition::find(dbc, exhibition_id));
        participation->setReward(reward);


        try {
            participation->insert(dbc);
            std::cout << "New entry added to participations.\n";
        } catch (std::runtime_error const& e) {
            std::cout << "Failed to add new entry to participations.\n";
            return -1;
        }

        std::cout << "Do you want to add another exhibition? (y/n)\n> ";
        std::cin >> enter;
        if (!std::cin.good() || (enter != 'y' && enter != 'Y' && enter != 'n' && enter != 'N')) {
            std::cout << "Wrong input.\n";
            return -1;
        }

    } while (enter == 'Y' || enter == 'y');

    return 0;
}

int option_add_new_pedigree_info(SQLHDBC dbc) {
    
    int animal_id;

    animal_id = select_animal(dbc);
    if (animal_id == -1) {
        return -1;
    } 

    Animal* animal = Animal::find(dbc, animal_id);

    std::cout << "Pedigree:\n";

    printFamilyTree(animal);

    int mother_id = select_animal(dbc, "female", false);
    if (mother_id == -1) return -1;
    int father_id = select_animal(dbc, "male", false);
    if (father_id == -1) return -1;

    animal->setMother(Animal::find(dbc, mother_id));
    animal->setFather(Animal::find(dbc, father_id));

    std::cout << "Pedigree:\n";

    printFamilyTree(animal);

    return 0;
}

void printFamilyTree(const Animal* animal, const std::string& prefix) {
    if (animal == nullptr) {
        return;
    }

    std::cout << prefix << "+-- " << animal->getName() << std::endl;

    std::string newPrefix = prefix;
    if (prefix.empty()) {
        newPrefix = "    ";
    }
    else {
        newPrefix += "|   ";
    }

    printFamilyTree(animal->getMother(), newPrefix);
    printFamilyTree(animal->getFather(), newPrefix);
}

int option_update_animal(SQLHDBC dbc) {

    int animal_id = select_animal(dbc, false);
    if (animal_id == -1) {
        return -1;
    }

    Animal* record = Animal::find(dbc, animal_id);

    std::cout << "Select attribute to update:\n";
    std::cout << "1. name\n";
    std::cout << "2. age\n";
    std::cout << "3. gender\n";
    std::cout << "4. breed_id\n";
    std::cout << "5. appearance\n";
    std::cout << "6. client_id\n";
    std::cout << "7. vet_id\n";
    std::cout << "> ";

    int option = -1;
    std::cin >> option;

    if (!std::cin.good() || option < 1 || option > 7) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    std::string name;
    int age;
    std::string gender;
    int breed_id;
    std::string appearance;
    int client_id;
    int vet_id;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (option)
    {
    case 1:
        std::cout << "New name: ";
        getline(std::cin, name);
        record->setName(name);
        break;
    case 2:
        std::cout << "New age: ";
        std::cin >> age;
        if (!std::cin.good() || age < 0) {
            std::cout << "Wrong input.\n";
            return -1;
        }
        record->setAge(age);
        break;
    case 3:
        gender = select_gender();
        if (gender == "") {
            return -1;
        }
        record->setGender(gender);
        break;
    case 4:
        breed_id = select_breed(dbc);
        if (breed_id == -1) {
            return -1;
        }
        record->setBreed(Breed::find(dbc, breed_id));
        break;
    case 5:
        std::cout << "New appearance: ";
        getline(std::cin, appearance);
        record->setAppearance(appearance);
        break;
    case 6:
        client_id = select_client(dbc);
        if (client_id == -1) {
            return -1;
        }
        record->setClient(Client::find(dbc, client_id));
        break;
    case 7:
        vet_id = select_vet(dbc);
        if (vet_id == -1) {
            return -1;
        }
        record->setVet(Employee::find(dbc, vet_id));
        break;
    
    default:
        break;
    }

    try {
        record->update(dbc);
        std::cout << "Animal data updated\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to update animal data.\nError occured: " << e.what();
        return -1;
    }

    return record->getId();

}

int option_update_breed(SQLHDBC dbc) {

    int breed_id = select_breed(dbc, false);
    if (breed_id == -1) {
        return -1;
    }

    Breed* record = Breed::find(dbc, breed_id);

    std::string name;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "New name: ";
    getline(std::cin, name);
    record->setName(name);
        
    try {
        record->update(dbc);
        std::cout << "Breed data updated\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to update breed data.\nError occured: " << e.what() << "\n";
        return -1;
    }

    return record->getId();

}

int option_update_client(SQLHDBC dbc) {

    int client_id = select_client(dbc, false);
    if (client_id == -1) {
        return -1;
    }

    Client* record = Client::find(dbc, client_id);

    std::cout << "Select attribute to update:\n";
    std::cout << "1. last name\n";
    std::cout << "2. first name\n";
    std::cout << "3. patronymic\n";
    std::cout << "4. address\n";
    std::cout << "> ";

    int option = -1;
    std::cin >> option;

    if (!std::cin.good() || option < 1 || option > 4) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string address;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (option)
    {
    case 1:
        std::cout << "New last name: ";
        getline(std::cin, last_name);
        record->setLastName(last_name);
        break;
    case 2:
        std::cout << "New first name: ";
        getline(std::cin, first_name);
        record->setFirstName(first_name);
        break;
    case 3:
        std::cout << "New patronymic: ";
        getline(std::cin, patronymic);
        record->setPatronymic(patronymic);
        break;
    case 4:
        std::cout << "New address: ";
        getline(std::cin, address);
        record->setAddress(address);
        break;
    
    default:
        break;
    }

    try {
        record->update(dbc);
        std::cout << "Client data updated\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to update client data.\nError occured: " << e.what();
        return -1;
    }

    return record->getId();

}

int option_update_employee(SQLHDBC dbc) {

    int employee_id = select_employee(dbc, false);
    if (employee_id == -1) {
        return -1;
    }

    Employee* record = Employee::find(dbc, employee_id);

    std::cout << "Select attribute to update:\n";
    std::cout << "1. last name\n";
    std::cout << "2. first name\n";
    std::cout << "3. patronymic\n";
    std::cout << "4. address\n";
    std::cout << "5. position_id\n";
    std::cout << "4. salary\n";
    std::cout << "> ";

    int option = -1;
    std::cin >> option;

    if (!std::cin.good() || option < 1 || option > 4) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    std::string last_name;
    std::string first_name;
    std::string patronymic;
    std::string address;
    int position_id;
    int salary;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (option)
    {
    case 1:
        std::cout << "New last name: ";
        getline(std::cin, last_name);
        record->setLastName(last_name);
        break;
    case 2:
        std::cout << "New first name: ";
        getline(std::cin, first_name);
        record->setFirstName(first_name);
        break;
    case 3:
        std::cout << "New patronymic: ";
        getline(std::cin, patronymic);
        record->setPatronymic(patronymic);
        break;
    case 4:
        std::cout << "New address: ";
        getline(std::cin, address);
        record->setAddress(address);
        break;
    case 5:
        position_id = select_position(dbc, false);
        if (position_id == -1) {
            return -1;
        }
        record->setPosition(Position::find(dbc, position_id));
        break;
    case 6:
        std::cout << "New salary: ";
        std::cin >> salary;
        if (!std::cin.good() || salary < 0) {
            std::cout << "Wrong input.\n";
            return -1;
        }
        record->setSalary(salary);
        break;
    
    default:
        break;
    }

    try {
        record->update(dbc);
        std::cout << "Employee data updated\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to update employee data.\nError occured: " << e.what();
        return -1;
    }

    return record->getId();

}

int option_update_position(SQLHDBC dbc) {

    int position_id = select_position(dbc, false);
    if (position_id == -1) {
        return -1;
    }

    Position* record = Position::find(dbc, position_id);

    std::string name;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "New name: ";
    getline(std::cin, name);
    record->setName(name);
        
    try {
        record->update(dbc);
        std::cout << "Position data updated\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to update position data.\nError occured: " << e.what() << "\n";
        return -1;
    }

    return record->getId();

}

int option_update_request(SQLHDBC dbc) {

    int request_id = select_request(dbc, false);
    if (request_id == -1) {
        return -1;
    }

    Request* record = Request::find(dbc, request_id);

    std::cout << "Select attribute to update:\n";
    std::cout << "1. client_id\n";
    std::cout << "2. breed_id\n";
    std::cout << "3. gender\n";
    std::cout << "4. request_date\n";
    std::cout << "> ";

    int option = -1;
    std::cin >> option;

    if (!std::cin.good() || option < 1 || option > 4) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    int client_id;
    int breed_id;
    std::string gender;
    int day, month, year;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (option)
    {
    case 1:
        client_id = select_client(dbc);
        if (client_id == -1) {
            return -1;
        }
        record->setClient(Client::find(dbc, client_id));
        break;
    case 2:
        breed_id = select_breed(dbc);
        if (breed_id == -1) {
            return -1;
        }
        record->setBreed(Breed::find(dbc, breed_id));
        break;
    case 3:
        gender = select_gender();
        if (gender == "") {
            return -1;
        }
        record->setGender(gender);
        break;
    case 4:
        if (select_date(&day, &month, &year) == -1) {
            std::cout << "Wrong input.\n";
            return -1;
        }
        record->setDay(day);
        record->setMonth(month);
        record->setYear(year);
        break;
    
    default:
        break;
    }

    try {
        record->update(dbc);
        std::cout << "Request data updated\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to update request data.\nError occured: " << e.what();
        return -1;
    }

    return record->getId();

}

int option_update_exhibition(SQLHDBC dbc) { 

    int exhibition_id = select_exhibition(dbc, false);
    if (exhibition_id == -1) {
        return -1;
    }

    Exhibition* record = Exhibition::find(dbc, exhibition_id);

    std::cout << "Select attribute to update:\n";
    std::cout << "1. name\n";
    std::cout << "2. address\n";
    std::cout << "3. exhibition_date\n";
    std::cout << "> ";

    int option = -1;
    std::cin >> option;

    if (!std::cin.good() || option < 1 || option > 3) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    std::string name;
    std::string address;
    int day, month, year;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (option)
    {
    case 1:
        std::cout << "New name: ";
        getline(std::cin, name);
        record->setName(name);
        break;
    case 2:
        std::cout << "New address: ";
        getline(std::cin, address);
        record->setAddress(address);
        break;
    case 3:
        if (select_date(&day, &month, &year) == -1) {
            std::cout << "Wrong input.\n";
            return -1;
        }
        record->setDay(day);
        record->setMonth(month);
        record->setYear(year);
        break;
    
    default:
        break;
    }

    try {
        record->update(dbc);
        std::cout << "Exhibition data updated\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to update exhibition data.\nError occured: " << e.what();
        return -1;
    }

    return record->getId();

}

int option_update_participation(SQLHDBC dbc) { 
    
    int animal_id;
    std::string reward;

    animal_id = select_animal(dbc, false);
    if (animal_id == -1) {
        return -1;
    }

    std::map<int, pair> participations = Participation::get_values(dbc, "animal_id", std::to_string(animal_id));

    std::map<int, int> exhibitions;

    for (const auto& [order, p] : participations) {
        exhibitions.insert({order, p.second});
    }

    std::cout << "Select exhibition to update reward:\n";
    Exhibition::display(dbc, exhibitions, animal_id);
    std::cout << "> ";

    int option;
    std::cin >> option;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    int exhibition_id = exhibitions[option];

    Exhibition* ex = Exhibition::find(dbc, exhibition_id);
    if (ex->getId() == 0) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    std::cout << "New reward: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin, reward);

    Participation* record = Participation::find(dbc, animal_id, exhibition_id);
    record->setReward(reward);

    try {
        record->update(dbc);
        std::cout << "Participation data updated\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to update participation data.\nError occured: " << e.what();
        return -1;
    }

    return 0;

}

int option_remove_animal(SQLHDBC dbc) {

    int record_id = select_animal(dbc, false);
    if (record_id == -1) {
        return -1;
    }

    Animal* animal = Animal::find(dbc, record_id);

    try {
        animal->remove(dbc);
        std::cout << "Deleted succesfully.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to delete entry.\nError occured: " << e.what() << "\n";
    }

    return 0;
}

int option_remove_breed(SQLHDBC dbc) {

    int record_id = select_breed(dbc, false);
    if (record_id == -1) {
        return -1;
    }

    Breed* breed = Breed::find(dbc, record_id);

    std::map<int,int> animals = Animal::get_values(dbc, "breed_id", std::to_string(breed->getId()));
    std::map<int,int> requests = Request::get_values(dbc, "breed_id", std::to_string(breed->getId()));

    if (animals.size() > 0 || requests.size() > 0) {
        std::cout << "Some other records depends on this breed. Run cascade delete? (y/n)\n> ";
        char deletion = '?';
        std::cin >> deletion;
        if (!std::cin.good() || (deletion != 'y' && deletion != 'Y' && deletion != 'n' && deletion != 'N')) {
            std::cout << "Wrong input.\n";
            return -1;
        }
        if (deletion == 'n' || deletion == 'N') {
            std::cout << "Deletion canceled.\n";
            return 0;
        }
    }

    try {
        breed->remove(dbc);
        std::cout << "Deleted succesfully.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to delete entry.\nError occured: " << e.what() << "\n";
    }

    return 0;
}

int option_remove_client(SQLHDBC dbc) {

    int record_id = select_client(dbc, false);
    if (record_id == -1) {
        return -1;
    }

    Client* client = Client::find(dbc, record_id);

    std::map<int,int> animals = Animal::get_values(dbc, "client_id", std::to_string(client->getId()));
    std::map<int,int> requests = Request::get_values(dbc, "client_id", std::to_string(client->getId()));

    if (animals.size() > 0 || requests.size() > 0) {
        std::cout << "Some other records depends on this client. Run cascade delete? (y/n)\n> ";
        char deletion = '?';
        std::cin >> deletion;
        if (!std::cin.good() || (deletion != 'y' && deletion != 'Y' && deletion != 'n' && deletion != 'N')) {
            std::cout << "Wrong input.\n";
            return -1;
        }
        if (deletion == 'n' || deletion == 'N') {
            std::cout << "Deletion canceled.\n";
            return 0;
        }
    }

    try {
        client->remove(dbc);
        std::cout << "Deleted succesfully.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to delete entry.\nError occured: " << e.what() << "\n";
    }

    return 0;
}

int option_remove_employee(SQLHDBC dbc) {

    int record_id = select_employee(dbc, false);
    if (record_id == -1) {
        return -1;
    }

    Employee* employee = Employee::find(dbc, record_id);

    std::map<int,int> animals = Animal::get_values(dbc, "vet_id", std::to_string(employee->getId()));

    if (animals.size() > 0) {
        std::cout << "Some other records depends on this employee. Run cascade delete? (y/n)\n> ";
        char deletion = '?';
        std::cin >> deletion;
        if (!std::cin.good() || (deletion != 'y' && deletion != 'Y' && deletion != 'n' && deletion != 'N')) {
            std::cout << "Wrong input.\n";
            return -1;
        }
        if (deletion == 'n' || deletion == 'N') {
            std::cout << "Deletion canceled.\n";
            return 0;
        }
    }

    try {
        employee->remove(dbc);
        std::cout << "Deleted succesfully.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to delete entry.\nError occured: " << e.what() << "\n";
    }

    return 0;
}

int option_remove_position(SQLHDBC dbc) {

    int record_id = select_position(dbc, false);
    if (record_id == -1) {
        return -1;
    }

    Position* position = Position::find(dbc, record_id);

    std::map<int,int> employees = Employee::get_values(dbc, "position_id", std::to_string(position->getId()));

    if (employees.size() > 0) {
        std::cout << "Some other records depends on this position. Run cascade delete? (y/n)\n> ";
        char deletion = '?';
        std::cin >> deletion;
        if (!std::cin.good() || (deletion != 'y' && deletion != 'Y' && deletion != 'n' && deletion != 'N')) {
            std::cout << "Wrong input.\n";
            return -1;
        }
        if (deletion == 'n' || deletion == 'N') {
            std::cout << "Deletion canceled.\n";
            return 0;
        }
    }

    try {
        position->remove(dbc);
        std::cout << "Deleted succesfully.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to delete entry.\nError occured: " << e.what() << "\n";
    }

    return 0;
}

int option_remove_request(SQLHDBC dbc) {

    int record_id = select_request(dbc, false);
    if (record_id == -1) {
        return -1;
    }

    Request* request = Request::find(dbc, record_id);

    try {
        request->remove(dbc);
        std::cout << "Deleted succesfully.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to delete entry.\nError occured: " << e.what() << "\n";
    }

    return 0;
}

int option_remove_exhibition(SQLHDBC dbc) {

    int record_id = select_exhibition(dbc, false);
    if (record_id == -1) {
        return -1;
    }

    Exhibition* exhibition = Exhibition::find(dbc, record_id);

    try {
        exhibition->remove(dbc);
        std::cout << "Deleted succesfully.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to delete entry.\nError occured: " << e.what() << "\n";
    }

    return 0;
}

int option_remove_participation(SQLHDBC dbc) {

    int animal_id;

    animal_id = select_animal(dbc, false);
    if (animal_id == -1) {
        return -1;
    }

    std::map<int, pair> participations = Participation::get_values(dbc, "animal_id", std::to_string(animal_id));

    std::map<int, int> exhibitions;

    for (const auto& [order, p] : participations) {
        exhibitions.insert({order, p.second});
    }

    std::cout << "Select exhibition to delete:\n";
    Exhibition::display(dbc, exhibitions, animal_id);
    std::cout << "> ";

    int option;
    std::cin >> option;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    int exhibition_id = exhibitions[option];

    Exhibition* ex = Exhibition::find(dbc, exhibition_id);
    if (ex->getId() == 0) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    Participation* record = Participation::find(dbc, animal_id, exhibition_id);

    try {
        record->remove(dbc);
        std::cout << "Deleted succesfully.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to delete entry.\nError occured: " << e.what() << "\n";
    }

    return 0;
}

int option_show_data(SQLHDBC dbc) {

    std::cout << "Select option:\n";
    std::cout << "1. Show ANIMALS\n";
    std::cout << "2. Show BREEDS\n";
    std::cout << "3. Show CLIENTS\n";
    std::cout << "4. Show EMPLOYEES\n";
    std::cout << "5. Show POSITIONS\n";
    std::cout << "6. Show EXHIBITIONS\n";
    std::cout << "7. Show REQUESTS\n";
    std::cout << "8. Show PARTICIPATIONS of selected animal\n";
    std::cout << "9. Show PEDIGREE of selected animal\n";
    std::cout << "> ";

    int option;
    std::cin >> option;
    if (!std::cin.good() || option < 1 || option > 9) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    std::map<int, int> records;

    switch (option)
    {
    case 1:
        records = Animal::get_values(dbc);
        Animal::display(dbc, records);
        break;
    case 2:
        records = Breed::get_values(dbc);
        Breed::display(dbc, records);
        break;
    case 3:
        records = Client::get_values(dbc);
        Client::display(dbc, records);
        break;
    case 4:
        records = Employee::get_values(dbc);
        Employee::display(dbc, records);
        break;
    case 5:
        records = Position::get_values(dbc);
        Position::display(dbc, records);
        break;
    case 6:
        records = Exhibition::get_values(dbc);
        Exhibition::display(dbc, records);
        break;
    case 7:
        records = Request::get_values(dbc);
        Request::display(dbc, records);
        break;
    case 8:
    {
        int animal_id = select_animal(dbc);
        if (animal_id == -1) {
            return -1;
        }
        std::map<int, pair> participations = Participation::get_values(dbc, "animal_id", std::to_string(animal_id));
        std::map<int, int> records;
        for (const auto& [order, p] : participations) {
            records.insert({order, p.second});
        }
        Exhibition::display(dbc, records, animal_id);
    }
        break;
    case 9:
        //option_show_pedigree_info(dbc);
        break;
    default:
        break;
    }

    return 0;

}

int select_animal(SQLHDBC dbc, bool addition) {
    int animal_id;
    std::cout << "Select animal:\n";
    std::map<int, int> record_map = Animal::get_values(dbc);
    Animal::display(dbc, record_map);
    if (addition) std::cout << "or\n" << (int)(record_map.size())+1 << ". Add new animal\n";
    std::cout << "> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (record_map.find(number) != record_map.end()) {
        animal_id = record_map[number];
    }
    else if (addition && number == (int)(record_map.size())+1) {
        animal_id = option_add_new_animal(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    return animal_id;

}

int select_animal(SQLHDBC dbc, std::string gender, bool addition) {
    int animal_id;
    std::map<int, int> record_map = Animal::get_values(dbc, "gender", gender);
    Animal::display(dbc, record_map);
    if (addition) std::cout << "or\n" << (int)(record_map.size())+1 << ". Add new animal\n";
    std::cout << "> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (record_map.find(number) != record_map.end()) {
        animal_id = record_map[number];
    }
    else if (addition && number == (int)(record_map.size())+1) {
        animal_id = option_add_new_animal(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    return animal_id;

}

int select_request(SQLHDBC dbc, bool addition) {
    int request_id;
    std::cout << "Select request:\n";
    std::map<int, int> record_map = Request::get_values(dbc);
    Request::display(dbc, record_map);
    if (addition) std::cout << "or\n" << (int)(record_map.size())+1 << ". Add new request\n";
    std::cout << "> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (record_map.find(number) != record_map.end()) {
        request_id = record_map[number];
    }
    else if (addition && number == (int)(record_map.size())+1) {
        request_id = option_add_new_request(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    return request_id;

}

int select_exhibition(SQLHDBC dbc, bool addition) { 
    int exhibition_id;

    std::cout << "Select exhibition:\n";
    std::map<int, int> record_map = Exhibition::get_values(dbc);
    Exhibition::display(dbc, record_map);
    if (addition) std::cout << "or\n" << (int)(record_map.size())+1 << ". Add new exhibition\n";
    std::cout << "> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (record_map.find(number) != record_map.end()) {
        exhibition_id = record_map[number];
    }
    else if (addition && number == (int)(record_map.size())+1) {
        exhibition_id = option_add_new_exhibition(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    return exhibition_id;
}

int select_breed(SQLHDBC dbc, bool addition) {

    int breed_id; 

    std::cout << "Select breed:\n";
    std::map<int, int> record_map = Breed::get_values(dbc);
    Breed::display(dbc, record_map);
    if (addition) std::cout << "or\n" << (int)(record_map.size())+1 << ". Add new breed\n";
    std::cout << "> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (record_map.find(number) != record_map.end()) {
        breed_id = record_map[number];
    }
    else if (addition && number == (int)(record_map.size())+1) {
        breed_id = option_add_new_breed(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    return breed_id;
}

int select_client(SQLHDBC dbc, bool addition) {

    int client_id;

    std::cout << "Select client:\n";
    std::map<int, int> record_map = Client::get_values(dbc);
    Client::display(dbc, record_map);
    if (addition) std::cout << "or\n" << (int)(record_map.size())+1 << ". Add new client\n";
    std::cout << "> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (record_map.find(number) != record_map.end()) {
        client_id = record_map[number];
    }
    else if (addition && number == (int)(record_map.size())+1) {
        client_id = option_add_new_client(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    return client_id;
}

int select_employee(SQLHDBC dbc, bool addition) {

    int employee_id;

    std::cout << "Select employee:\n";
    std::map<int, int> record_map = Employee::get_values(dbc);
    Employee::display(dbc, record_map);
    if (addition) std::cout << "or\n" << (int)(record_map.size())+1 << ". Add new employee\n";
    std::cout << "> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (record_map.find(number) != record_map.end()) {
        employee_id = record_map[number];
    }
    else if (addition && number == (int)(record_map.size())+1) {
        employee_id = option_add_new_employee(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    return employee_id;
}

int select_position(SQLHDBC dbc, bool addition) {

    int position_id;
    std::cout << "Select position:\n";
    std::map<int, int> record_map = Position::get_values(dbc);
    Position::display(dbc, record_map);
    if (addition) std::cout << "or\n" << (int)(record_map.size())+1 << ". Add new position\n";
    std::cout << "> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (record_map.find(number) != record_map.end()) {
        position_id = record_map[number];
    }
    else if (addition && number == (int)(record_map.size())+1) {
        position_id = option_add_new_position(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    return position_id;
}

std::string select_gender() {
    int gen;
    std::cout << "Select gender:\n";
    std::cout << "\t1. male\n\t2. female\n> ";
    std::cin >> gen;
    if (!std::cin.good() || (gen != 1 && gen != 2)) {
        std::cout << "Wrong input.\n";
        return "";
    }

    return (gen == 1) ? "male" : "female";
}

int select_vet(SQLHDBC dbc, bool addition) {

    int vet_id;
    std::cout << "Select vet:\n";

    Position* pos = new Position();
    std::map<int,int> vet = Position::get_values(dbc, "name", "vet");

    if (vet.size() == 0) {
        pos->setName("vet");
        pos->insert(dbc);
    } else {
        pos = Position::find(dbc, vet[1]);
    }
    int position_vet_id = pos->getId();

    std::map<int, int> record_map = Employee::get_values(dbc, "position_id", std::to_string(position_vet_id));
    Employee::display(dbc, record_map);
    if (addition) std::cout << "or\n" << (int)(record_map.size())+1 << ". Add new vet\n";
    std::cout << "> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (record_map.find(number) != record_map.end()) {
        vet_id = record_map[number];
    }
    else if (addition && number == (int)(record_map.size())+1) {
        vet_id = option_add_new_vet(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }
    return vet_id;
}

int select_date(int* day, int* month, int* year) {

    std::cout << "Date [dd.mm.yyyy]: ";
    std::string date;
    getline(std::cin, date);
    std::regex dateRegex(R"((\d{2})\.(\d{2})\.(\d{4}))");
    std::smatch match;

    if (!std::regex_match(date, match, dateRegex)) {
        std::cout << "Date doesn't match regex.\n";
        return -1;
    }

    int d = std::stoi(match.str(1));
    int m = std::stoi(match.str(2));
    int y = std::stoi(match.str(3));

    if (!isValidDate(d, m, y)) {
        std::cout << "Date is not valid.\n";
        return -1;
    }

    *day = d;
    *month = m;
    *year = y;

    return 0;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int day, int month, int year) {
    if (year < 1 || month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    } else if (month == 2) {
        if (isLeapYear(year))
            daysInMonth = 29;
        else
            daysInMonth = 28;
    }

    return day <= daysInMonth;
}