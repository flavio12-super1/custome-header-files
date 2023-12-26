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
    cats.append("pussy", 10);

    cout << dogs << endl;
    cout << old_dogs_list << endl;
    cout << cats << endl;
    cout << old_cats_list << endl;

    return 0;
}