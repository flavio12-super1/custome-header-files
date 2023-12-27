#include <ArrayList.h>

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

struct Success {
    bool state;
    int index;
    std::string response;
    Success() {
        state = false;
        index = 0;
        response = "not found";
    }

    Success(bool state, std::string response) {
        this->state = state;
        this->response = response;
    }

    Success(bool state, int index, std::string response) {
        this->state = state;
        this->index = index;
        this->response = response;
    }
};

struct Pet {
    std::string name;
    int age;
    Pet() {
        name = "pet-name";
        age = 0;
    }
    Pet(std::string name) { this->name = name; }
    Pet(std::string name, int age) {
        this->name = name;
        this->age = age;
    }

    // Define equality operator
    bool operator==(const Pet& other) const {
        // search by both name and age
        //  return name == other.name && age == other.age;

        // only search by nane
        return name == other.name;
    }
};

// overloaded operator <<
std::ostream& operator<<(std::ostream& os, const Pet& myPet) {
    os << "( name: " << myPet.name << ", "
       << "age: " << myPet.age << " )";

    return os;
}

class CreateArrayList {
   private:
   public:
    ArrayList<Pet> myArray;

    // default constructor
    CreateArrayList() {}

    // accepts
    CreateArrayList(std::string name, int age) {
        Pet pet(name, age);
        myArray.append(pet);
    }

    // copy constructor
    CreateArrayList(const CreateArrayList& other) {
        for (int i = 0; i < other.myArray.size(); i++) {
            myArray.append(other.myArray[i]);
        }
    }

    // overloaded constructor
    CreateArrayList& operator=(const CreateArrayList& other) {
        for (int i = 0; i < other.myArray.size(); i++) {
            myArray.append(other.myArray[i]);
        }
        return *this;
    }

    Pet& operator[](int index) const {
        if (index < 0 || index >= myArray.size()) {
            throw std::logic_error("Array index out of bounds.");
        }
        return myArray[index];
    }

    // add data from file
    void addData(std::string fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Error opening file." << std::endl;
        }

        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string name;
            int age;

            // Extract name and age from CSV line
            if (getline(ss, name, ',') && (ss >> age)) {
                // Append Pet object to ArrayList
                Pet pet(name, age);
                myArray.append(pet);
            }
        }
    }

    // append new pet object to array
    void append(std::string name, int age) {
        Pet newPet(name, age);
        myArray.append(newPet);
    }

    // remove first item
    Pet removeFirst() { return myArray.removeFirst(); }
    Pet removeLast() { return myArray.removeLast(); }

    bool search(Pet myPet) { return myArray.search(myPet); }

    // find object
    Success find(std::string name) {
        for (int i = 0; i < myArray.size(); i++) {
            if (myArray[i].name == name) {
                std::string response = "found: " + name;
                Success message(true, i, response);
                return message;
            }
        }
        Success message;
        return message;
    }

    void reverse() { myArray.reverse(); }
};

// overloaded operator <<
std::ostream& operator<<(std::ostream& os, const CreateArrayList& myList) {
    for (int i = 0; i < myList.myArray.size(); i++) {
        Pet pet = myList.myArray[i];
        os << "name: " << pet.name << ", "
           << "age: " << pet.age << std::endl;
    }
    os << "total number of entries -> " << myList.myArray.size() << std::endl;

    return os;
}
