// Testing file provided for EECS 281 Lab 7

#include "hashtable.h"
#include <string>
#include <iostream>

int main() {

    // VERY BASIC EXAMPLE (will likely not compile with default/empty hashtable.h file)
    HashTable<std::string, int> midterm;
    std::cout << midterm.insert("sam", 50) << " ";
    std::cout << midterm.insert("fee", 100) << " ";
    std::cout << midterm.insert("milo", 95) << " ";
    std::cout << midterm.insert("gabe", 88) << " \n";
    std::cout << midterm["sam"] << " ";
    std::cout << midterm["fee"] << " ";
    std::cout << midterm["milo"] << " ";
    std::cout << midterm["gabe"] << " \n";
    std::cout << midterm.erase("sam") << " ";
    std::cout << midterm["sam"] << "\n";
    // ADD MORE TESTS OF YOUR OWN

    return 0;
}
