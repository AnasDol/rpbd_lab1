#include "menu.hpp"

void start(SQLHDBC dbc) {

    int option;
    do {
        std::cout << "-------- Choose option --------\n";
        std::cout << "1. Add new animal\n";
        std::cout << "2. Add new breed\n";
        std::cout << "3. Add new client\n";
        std::cout << "4. Add new employee\n";
        std::cout << "5. Add new position\n";
        std::cout << "6. Add new exhibition\n";
        std::cout << "\n";
        std::cout << "7. Enter data on the participation of animals in exhibitions\n";
        std::cout << "8. Enter pedigree information\n";
        std::cout << "\n";
        std::cout << "9. Create new request\n";
        std::cout << "\n";
        std::cout << "10. Show data\n";
        std::cout << "\n";
        std::cout << "11. Update information\n";
        std::cout << "12. Delete information\n";
        std::cout << "\n";
        std::cout << "-1. Exit\n";
        std::cout << "-------------------------------\n";
        std::cout << "\n> ";

        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> option;

        proceed(dbc, option);

        
    } while (option != -1);

}

void proceed(SQLHDBC dbc, int option) {

    switch (option)
    {
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

    case 9:
        option_add_new_request(dbc);
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

    int option;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Name: ";
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

    gender = (option == 1) ? "male" : "female";

    std::cout << "Select breed:\n";
    std::map<int, int> breed_map = Breed::display_and_return_all(dbc);
    std::cout << "or\n" << (int)(breed_map.size())+1 << ". Add new breed\n> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (breed_map.find(number) != breed_map.end()) {
        breed_id = breed_map[number];
    }
    else if (number == (int)(breed_map.size())+1) {
        breed_id = option_add_new_breed(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Appearance: ";
    getline(std::cin, appearance);

    std::cout << "Select client:\n";
    std::map<int, int> client_map = Client::display_and_return_all(dbc);
    std::cout << "or\n" << (int)(client_map.size())+1 << ". Add new client\n> ";

    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (client_map.find(number) != client_map.end()) {
        client_id = client_map[number];
    }
    else if (number == (int)(client_map.size())+1) {
        client_id = option_add_new_client(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    std::cout << "Select vet:\n";
    std::map<int, int> vet_map = Employee::display_and_return_vets(dbc);
    std::cout << "or\n" << (int)(vet_map.size())+1 << ". Add new vet\n> ";

    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (vet_map.find(number) != vet_map.end()) {
        vet_id = vet_map[number];
    }
    else if (number == (int)(vet_map.size())+1) {
        vet_id = option_add_new_vet(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }





    // ... (родословная)

    Animal new_record;
    new_record.setName(name);
    new_record.setAge(age);
    new_record.setGender(gender);
    new_record.setBreedId(breed_id);
    new_record.setAppearance(appearance);
    new_record.setClientId(client_id);
    new_record.setVetId(vet_id);

    try {
        new_record.insert(dbc);
        std::cout << "New entry added to animals.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to add new entry to animals.\nError occured: " << e.what();
        return -1;
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

    std::cout << "Select position:\n";
    std::map<int, int> positions = Position::display_and_return_all(dbc);
    std::cout << "or\n" << (int)(positions.size())+1 << ". Add new position\n> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (positions.find(number) != positions.end()) {
        position_id = positions[number];
    }
    else if (number == (int)(positions.size())+1) {
        position_id = option_add_new_position(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
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
    new_record.setPositionId(position_id);
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

    Position pos = Position::find(dbc, "name", "vet");
    if (pos.getId() == 0) {
        pos.setName("vet");
        pos.insert(dbc);
    }

    position_id = pos.getId();

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
    new_record.setPositionId(position_id);
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

    if (select_date(&day, &month, &year) == -1) {
        std::cout << "Wrong input.\n";
        return -1;
    }

    Request new_record(0, client_id, breed_id, gender, day, month, year);

    try {
        new_record.insert(dbc);
        std::cout << "New entry added to requests.\n";
    } catch (std::runtime_error const& e) {
        std::cout << "Failed to add new entry to requests.\n";
        return -1;
    }

    return new_record.getId();

}

int select_breed(SQLHDBC dbc) {

    int breed_id; 

    std::cout << "Select breed:\n";
    std::map<int, int> breed_map = Breed::display_and_return_all(dbc);
    std::cout << "or\n" << (int)(breed_map.size())+1 << ". Add new breed\n> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (breed_map.find(number) != breed_map.end()) {
        breed_id = breed_map[number];
    }
    else if (number == (int)(breed_map.size())+1) {
        breed_id = option_add_new_breed(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    return breed_id;
}

int select_client(SQLHDBC dbc) {

    int client_id;

    std::cout << "Select client:\n";
    std::map<int, int> client_map = Client::display_and_return_all(dbc);
    std::cout << "or\n" << (int)(client_map.size())+1 << ". Add new client\n> ";

    int number;
    std::cin >> number;

    if (!std::cin.good()) {
        std::cout << "Wrong input.\n";
        return -1;
    }
    
    // ключ найден
    if (client_map.find(number) != client_map.end()) {
        client_id = client_map[number];
    }
    else if (number == (int)(client_map.size())+1) {
        client_id = option_add_new_client(dbc);
    }
    else {
        std::cout << "Wrong input.\n";
        return -1;
    }

    return client_id;
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

int select_date(int* day, int* month, int* year) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Date [dd.mm.yyyy]: ";
    std::string date;
    getline(std::cin, date);
    std::regex dateRegex(R"((\d{2})\.(\d{2})\.(\d{4}))");
    std::smatch match;

    if (!std::regex_match(date, match, dateRegex)) {
        return -1;
    }

    int d = std::stoi(match.str(1));
    int m = std::stoi(match.str(2));
    int y = std::stoi(match.str(3));

    if (!isValidDate(d, m, y)) {
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