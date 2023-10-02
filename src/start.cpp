#include "ActiveRecord/Breed.hpp"
#include "ActiveRecord/Client.hpp"
#include "ActiveRecord/Test.hpp"
#include "Windows.h"
#include "connection.hpp"
#include "menu.hpp"
#include <iostream>
#include <odbcinst.h>

int main() {

    std::string dsn = "PostgresDataSource";
    std::string uid = "rpbd_user";
    std::string pwd = "1234";

    SQLHENV env;
    SQLHDBC dbc;

    int result = connect_to_db(dsn, uid, pwd, &env, &dbc);

    if (result == 1) {
        std::cout << "Connection failed.";
        return 1;
    }

    if (init_tables(dbc) != 0) {
        std::cout << "Tables initialization failed.";
        return 1;
    }

    // print_table(dbc, "animals");

    /*Test record = Test::find_by_id(dbc, 1);
    std::cout<< "record: id = " + std::to_string(record.id_) + ", value = " +
    std::to_string(record.value_) + "\n";

    record.value_ = 5;
    record.update(dbc);*/

    // Breed record = Breed::find_by_id(dbc, 1);
    // std::cout<< "record: id = " + std::to_string(record.id) + ", name = " +
    // record.name + "\n";

    // Breed new_breed;
    // new_breed.setName("Pony");

    // new_breed.insert(dbc);
    // std::cout<<"new_breed: id = " + std::to_string(new_breed.id) + ", name =
    // "
    // + new_breed.name + "\n";

    // Breed rem_breed;
    // rem_breed = Breed::find_by_id(dbc, 1);

    // try {
    //     rem_breed.remove(dbc);
    // } catch (std::runtime_error const& e) {
    //     std::cout << e.what() << ".\n";
    // }

    // std::cout<<"new_breed: id = " + std::to_string(rem_breed.id) + ", name =
    // "
    // + rem_breed.name + "\n";

    // print_table(dbc, "breeds");

    // option_add_new_animal(dbc);

    // Client client;
    // client.setLastName("Spanch");
    // client.setFirstName("Bob");
    // client.setAddress("in a pineapple under the sea");

    // client.insert(dbc);

    // Client client = Client::find_by_id(dbc, 2);
    // client.setPatronymic("");

    // client.update(dbc);

    // std::cout << client.getLastName() << " " << client.getFirstName() <<
    // client.getPatronymic() << client.getAddress();

    // option_add_new_employee(dbc);

    // Position::display_and_return_all(dbc);

    // Client::display_and_return_all(dbc);

    //std::cout << get_record_num(dbc, "breeds");

    
    option_add_new_animal(dbc);

    //option_add_new_vet(dbc);

    //Employee::display_and_return_vets(dbc);

    //Animal a(0, "Kir", 7, "male", 3, "super cute", 2, 1);
    //a.insert(dbc);



    disconnect_from_db(env, dbc);

    return 0;
}
