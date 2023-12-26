#include <ArrayList.h>

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

struct Pet {
    std::string name;
    int age;
    Pet() {
        name = "pet-name";
        age = 0;
    }
    Pet(std::string name, int age) {
        this->name = name;
        this->age = age;
    }
};

class CreateArrayList {
   private:
   public:
    ArrayList<Pet> myArray;

    // default constructor
    CreateArrayList() {}

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
};

// overloaded operator <<
std::ostream& operator<<(std::ostream& os, const CreateArrayList& myList) {
    for (int i = 0; i < myList.myArray.size(); i++) {
        Pet pet = myList.myArray[i];
        os << "name: " << pet.name << ", "
           << "age:" << pet.age << std::endl;
    }

    return os;
}
