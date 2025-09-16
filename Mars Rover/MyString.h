// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
using namespace std;

class MyString {

    public:

      // Constructors
        MyString(); // Default
        MyString(const MyString& copyThis); // Copy constructor
        MyString(const char* string); // Copy null-terminated sequence
        ~MyString(); // Destructor

        void resize(unsigned int n);
        unsigned int capacity() const;
        unsigned int size() const;
        unsigned int length() const;
    
        const char* data() const;
        bool empty() const;

        const char& front() const;
        const char& at(unsigned int pos) const;

        void clear();

        friend ostream& operator<<(ostream& os, const MyString& text);
        MyString& operator=(const MyString& copyThis);
        MyString& operator+=(const MyString& text);
        
        int find(const MyString& str, unsigned int pos = 0) const; 

        bool friend operator==(const MyString& left, const MyString& right); // Bonus

    private:

        char* array;
        unsigned int size_value;
        unsigned int capacity_value;

};

#endif