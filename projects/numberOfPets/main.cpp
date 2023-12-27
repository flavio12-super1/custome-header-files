#include <ArrayList.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "CreateArrayList.h"

using namespace std;

int main() {
    CreateArrayList dogs;

    dogs.addData("dog_pets.csv");
    CreateArrayList old_dogs_list = dogs;
    dogs.append("cupcake", 6);

    CreateArrayList cats;

    cats.addData("cat_pets.csv");
    CreateArrayList old_cats_list;
    old_cats_list = cats;
    cout << "removing -> " << cats.removeFirst() << endl;
    cout << "removing -> " << cats.removeLast() << endl;
    cats.append("pussy", 10);

    CreateArrayList birds("chirpy", 4);
    birds.append("flappy", 3);

    cout << dogs << endl;
    cout << old_dogs_list << endl;
    cout << cats << endl;
    cout << old_cats_list << endl;

    // Example 1
    string pet_name = "Tiger";
    Success output;
    output = cats.find(pet_name);
    cout << output.response << endl;

    // Example 2
    string pet_name2 = "furry";
    Success output2(cats.find(pet_name2));
    cout << output2.response << endl;

    // Example 3
    Success output3(cats.find("destroyer9000"));
    cout << output3.response << endl;

    // Example 4
    std::cout << Success(cats.find("Oreo")).response << std::endl;

    // search by both name and age
    //  Pet tempPet("Cleo", 3);

    // search only by name
    Pet tempPet("Cleo");

    string successResponse = "Pet: " + tempPet.name + " found in cats";
    string response = cats.search(tempPet) ? successResponse : "not found";
    cout << Success(cats.search(tempPet), response).response << endl;

    int index = 0;
    cout << "bird number[" << index << "]: " << birds[index] << endl;

    cout << endl;
    cout << "cat list" << endl;
    cout << cats << endl;
    cout << endl;
    CreateArrayList reverseCatsList(cats);
    reverseCatsList.reverse();
    cout << "reverse cat list" << endl;
    reverseCatsList.remove(2);
    {
        Pet tempPet("milo", 1);
        reverseCatsList.insert(tempPet, 0);
    }
    { reverseCatsList.deleteItem("Shadow"); }

    cout << reverseCatsList << endl;

    return 0;
}