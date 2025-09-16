# include "functions.h"
// add any includes

using std::cout, std::cin, std::endl, std::string;

void deobfuscate() {
    string obfuscated;
    int details;
    cout << "Please enter obfuscated sentence: ";
    cin >> obfuscated;
    cout << "Please enter deobfuscation details: ";
    cin >> details;

    int details_digit = details % 10;
    int details_total = details_digit;
    details = details / 10;

    while (details != 0) {
        obfuscated.insert(obfuscated.length() - details_total, " "); // Inserting spaces at correct spots
        
        details_digit = details % 10;
        details = details / 10;
        details_total += details_digit + 1;

    }

    cout << "Deobfuscated sentence: " << obfuscated << endl;

}

void wordFilter() {
    // TODO
    string sentence;
    string filter;

    cout << "Please enter the sentence: ";
    cin >> sentence;
    cout << endl;
    cout << "Please enter the filter word: ";
    cin >> filter;
    cout << endl;
}

void passwordConverter() {
    string password;
    cin >> password;
    cout << "Please enter your text input: input: "<< password << endl;;
    


    for (long unsigned int i = 0; i < password.length(); ++i) { // Iterates through whole password
        if (password.at(i) == 'a') { // Replacing
            password.replace(i, 1, "@");
        } else if (password.at(i) == 'e') {
            password.replace(i, 1, "3");
        } else if (password.at(i) == 'i') {
            password.replace(i, 1, "!");
        } else if (password.at(i) == 'o') {
            password.replace(i, 1, "0");
        } else if (password.at(i) == 'u') {
            password.replace(i, 1, "^");
        }
    }

    int length = password.length();
    for(int i = 0; i < length; i++) { // Reversing the password
        password.push_back(password.at(length - 1 - i));
    }

    cout << "output: " << password << endl;
}

void wordCalculator() {
    // TODO
}

void palindromeCounter() {
    // TODO
}