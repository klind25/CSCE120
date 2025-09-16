// TODO: Implement this source file
# include <iostream>
# include "MyString.h"

using namespace std;

MyString::MyString() : array(new char[1]), size_value(0), capacity_value(1) { // Default
    array[0] = '\0';
} 

MyString::MyString(const MyString& copyThis) : array(new char[copyThis.capacity()]), size_value(copyThis.size()), capacity_value(copyThis.capacity()) {
    array[size_value] = '\0';

    for (unsigned int i = 0; i < size_value; ++i) {
        array[i] = copyThis.array[i];
    }
}

MyString::MyString(const char* string) : array(nullptr), size_value(0), capacity_value(1) {
    unsigned int length = 0;
    while (string[length] != '\0') {
        ++length;
    }
    size_value = length;
    capacity_value = size_value + 1;

    array = new char[capacity_value];

    for (unsigned int i = 0; i < length; ++i) {
        array[i] = string[i];
    }
    array[length] = '\0';

}

MyString::~MyString() { // Destructor
    delete[] array;
}

void MyString::resize(unsigned int n) {
    char* new_array;
    new_array = new char[n]; // New size

    for (unsigned int i = 0; i < size_value; ++i) { // Copy
        new_array[i] = array[i];
    }
    delete[] array; // No memory leak
    array = new_array; // Update array
    capacity_value = n;
}

unsigned int MyString::capacity() const {
    return capacity_value;
}
unsigned int MyString::size() const {
    return size_value;
}
unsigned int MyString::length() const {
    return size_value;
}

const char* MyString::data() const {
    return array;
}

bool MyString::empty() const {
    if (size_value == 0) {
        return true;
    }
    return false;
}

const char& MyString::front() const {
    return array[0];
}

const char& MyString::at(unsigned int pos) const {
    if (pos >= size_value) { // Checking out of bounds
        throw std::out_of_range("Out of bounds");
    }
    else {
        return array[pos];
    }
}

void MyString::clear() {

    delete[] array;
    size_value = 0; // Update parameters
    capacity_value = 1;
    array = new char[1];
    array[0] = '\0';
}

ostream& operator<<(ostream& os, const MyString& text) {
    
    for (unsigned int i = 0; i < text.size(); ++i) { // cout everything
        os << text.array[i];
    }
    return os;
}

MyString& MyString::operator=(const MyString& copyThis) {
    if (this == &copyThis) { // Already equal
        return *this;
    }
    delete[] array;

    size_value = copyThis.size_value; // Copy
    capacity_value = copyThis.capacity_value;

    array = new char[capacity_value];

    for (unsigned int i = 0; i < size_value; ++i) { // Copy array
        array[i] = copyThis.array[i];
    }

    array[size_value] = '\0'; // Null terminator
    

    return *this;
}

MyString& MyString::operator+=(const MyString& text) {

    unsigned int new_capacity = size_value + text.size_value + 1;

    char* new_array = new char[new_capacity];

    for (unsigned int i = 0; i < size_value; ++i) { // Old array
        new_array[i] = array[i];
    }

    for (unsigned int i = 0; i < text.size_value; ++i) { // add in new array
        new_array[i+size_value] = text.array[i];
    }

    size_value += text.size_value; // Update
    capacity_value = new_capacity;

    delete[] array; // Free old memory
    array = new_array;
    new_array[size_value] = '\0';

    return *this;
}
    
int MyString::find(const MyString& str, unsigned int pos) const { // Int because -1
    bool good = false;

    for (unsigned int i = pos; i < size_value; ++i) { // Starting at pos
        if (str.array[0] == array[i]) {
            for (unsigned int j = 0; j < str.size_value; ++j) { // Search size amount
                if (i + j >= size_value) {
                    break;
                }
                if (str.array[j] != array[i+j]) { // Keep going
                    good = false;
                    break;
                }
                else {
                    good = true;
                }
            }
            if (good) { // Whole sequence matches
                return i;
            }
        }
    }
    return -1;
}

bool operator==(const MyString& left, const MyString& right) {
    if (left.size() == right.size() && left.capacity() == right.capacity()) { // Check size and capacity first
        for (unsigned int i = 0; i < left.size(); ++i) {
            if (left.array[i] != right.array[i]) { // Not same
                return false;
            }
        }
        return true;
    }
    return false;
}