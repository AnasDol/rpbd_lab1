#include "ActiveRecord/Breed.hpp"
#include "ActiveRecord/Client.hpp"
#include "ActiveRecord/Request.hpp"
#include "ActiveRecord/Participation.hpp"
#include "ActiveRecord/Exhibition.hpp"
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

    start(dbc);

    //option_add_new_pedigree_info(dbc);
 
    disconnect_from_db(env, dbc);

    return 0;
}
