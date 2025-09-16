#include <iostream>
#include "functions.h"
using namespace std;

void function_one(int i, int& j) {
    i += 2;
    j += 1;

}

void function_two(example& x) {
    x.value += 1;

}

void function_three(int* k, int& l) {
    *k += 1;
    l += 1;

}

void function_four(int array[], int size, int& lowest, int& highest) {
    
    for (int i = 0; i < size; ++i) {
        array[i] += 2;

    }
    lowest = array[0];
    highest = array[0];

    for (int i = 0; i < size; ++i) {
        if (array[i] < lowest) {
            lowest = array[i];
        }
        else if (array[i] > highest) {
            highest = array[i];
        }
    }

}