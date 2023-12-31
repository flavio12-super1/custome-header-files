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

    Success find(std::string nameToFind) {
        return myArray.find(nameToFind, &Pet::name);
    }

    void reverse() { myArray.reverse(); }

    void remove(int index) { myArray.remove(index); }

    void insert(Pet value, int index) { myArray.insert(value, index); }

    void deleteItem(std::string value) {
        Success item = find(value);
        if (item.index == -1) {
            std::cout << "item not found" << std::endl;
        } else {
            std::cout << "deleted item: " << myArray[item.index] << std::endl;
            remove(item.index);
        }
    }

    Pet get(int index) { return myArray.get(index); }

    int size() const { return myArray.size(); }
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
