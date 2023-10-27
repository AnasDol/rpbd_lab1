#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "../defaults.hpp"

#include "Breed.hpp"
#include "Client.hpp"
#include "Employee.hpp"

class Animal {

public:

    Animal() : id(-1), name(""), age(-1), gender(""),
               breed(nullptr), appearance(""),
               client(nullptr), vet(nullptr), mother(nullptr), father(nullptr) {}
               
    Animal(std::string name, int age, std::string gender,
           Breed* breed, std::string appearance, Client* client,
           Employee* vet, Animal* mother, Animal* father) :
        id(-1), name(name), age(age), gender(gender),
        breed(breed), appearance(appearance), client(client),
        vet(vet), mother(mother), father(father) {}

    void insert(SQLHDBC dbc);
    void update(SQLHDBC dbc);
    void remove(SQLHDBC dbc);

    static Animal* find(SQLHDBC dbc, int id);
    static std::map<int, int> get_values(SQLHDBC dbc);
    static std::map<int, int> get_values(SQLHDBC dbc, std::string attribute, std::string value);
    static void display(SQLHDBC dbc, std::map<int, int> record_map);

    // getters
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getAge() const { return age; }
    std::string getGender() const { return gender; }
    Breed* getBreed() const { return breed; }
    std::string getAppearance() const { return appearance; }
    Client* getClient() const { return client; }
    Employee* getVet() const { return vet; }
    Animal* getMother() const { return mother; }
    Animal* getFather() const { return father; }

    // setters
    void setId(int i) { id = i; }
    void setName(const std::string &n) { name = n; }
    void setAge(int a) { age = a; }
    void setGender(const std::string &g) { gender = g; }
    void setBreed(Breed* b) { breed = b; }
    void setAppearance(const std::string &a) { appearance = a; }
    void setClient(Client* c) { client = c; }
    void setVet(Employee* v) { vet = v; }
    void setMother(Animal* m) { mother = m; }
    void setFather(Animal* f) { father = f; }

    ~Animal() {
        delete breed;
        delete client;
        delete vet;
        delete mother;
        delete father;
    }

private:

    static inline const std::string table_name {"animals"};

    int id;
    std::string name;
    int age;
    std::string gender;
    Breed* breed;
    std::string appearance;
    Client* client;
    Employee* vet;
    //std::shared_ptr<Animal> mother, father;
    Animal* mother, *father;

};


#endif // ANIMAL_HPP
