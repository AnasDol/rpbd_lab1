#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>
#include <map>
#include "../connection.hpp"

class Animal {

public:
    Animal() : id(0), name(""), age(0), gender(""), breed_id(0), appearance(""), client_id(0), vet_id(0) {}

    Animal(int id, std::string name, int age, std::string gender, int breed_id, std::string appearance, int client_id, int vet_id) :
        id(id), name(name), age(age), gender(gender),
        breed_id(breed_id), appearance(appearance), client_id(client_id), vet_id(vet_id) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Animal find(SQLHDBC dbc, int id);
    static std::map<int, int> get_values(SQLHDBC dbc);
    static std::map<int, int> get_values(SQLHDBC dbc, std::string attribute, std::string value);
    static void display(SQLHDBC dbc, std::map<int, int> record_map);

    // getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getGender() const { return gender; }
    int getBreedId() const { return breed_id; }
    std::string getAppearance() const { return appearance; }
    int getClientId() const { return client_id; }
    int getVetId() const { return vet_id; }

    // setters
    void setName(std::string name) { this->name = name; }
    void setAge(int age) { this->age = age; }
    void setGender(std::string gender) { this->gender = gender; }
    void setBreedId(int breed_id) { this->breed_id = breed_id; }
    void setAppearance(std::string appearance) { this->appearance = appearance; }
    void setClientId(int client_id) { this->client_id = client_id; }
    void setVetId(int vet_id) { this->vet_id = vet_id; }

private:

    static inline const std::string table_name {"animals"};

    int id;
    std::string name;
    int age;
    std::string gender;
    int breed_id;
    std::string appearance;
    int client_id;
    int vet_id;

};


#endif // ANIMAL_HPP
