#include <iostream>
#include "Windows.h"
#include <odbcinst.h>
#include "connection.hpp"
#include "ActiveRecord/Test.hpp"

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

    //if (init_tables(dbc) == 0) std::cout<<"ok\n";
    //print_table(dbc, "test");

    Test record = Test::find_by_id(dbc, 1);
    std::cout<< "record: id = " + std::to_string(record.id_) + ", value = " + std::to_string(record.value_) + "\n";

    record.value_ = 5;
    record.update(dbc);



    disconnect_from_db(env, dbc);

    return 0;
}

