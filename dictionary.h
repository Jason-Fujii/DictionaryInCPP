//
// Created by Jason Fujii on 10/13/20.
//

#ifndef CSC340_PROJECT3_DICTIONARY_H
#define CSC340_PROJECT3_DICTIONARY_H

#include <iostream>
using namespace std;
#include <vector>
#include "mapVector.h"

class dictionary {
private:
    //instance variables
    bool quit = false;
    vector<string> lastInput = {"one", "two", "three", "four"};
    //functions

    /*
     * returns true if the string is a verified part of speech
     * returns false if the string isn't a part of speech
     */
    static bool checkPOS(string);

    /*
     * returns true if the string is "distinct"
     * returns false otherwise
     */
    static bool checkDistinct(string);

    /*
     * returns true if the string is "reverse"
     * returns false otherwise
     */
    static bool checkReverse(string);

    /*
     * Takes an int of either 2, 3, or 4 and uses that to know which part of the input is erroneous.
     * The string is the input that the user entered and prints out so they know their exact mistakes
     * The booleans refer to part of speech, distinct, and reverse (respectively) and whether the string is one of them
     */
    static void printErrors(int, string, bool, bool, bool);

    /*
     * returns true if the user input the same search as their previous search.
     * Completed using the instance variable lastInput
     */
    bool checkSameInput(vector<string>&);

    /*
     * The string is the user's input
     * This method takes that string, splits it into an array and performs the operations on those words.
     */
    void checkInput(string&);

    /*
     * Prints the administrative replies
     */
    void printAdmin(string);

    /*
     * Helps to parse the user's input into readable chunks that the program can use.
     */
    static void stringParser(vector<string>&, string&);

    /*
     * sets the entire string to lowercase
     */
    static string setLower(string&);

public:
    //instance variables
    mapVector map;
    //functions

    //Constructor
    dictionary();

    /*
     * The function that facilitates interaction between the dictionary and the user
     */
    void userInterface();




};


#endif //CSC340_PROJECT3_DICTIONARY_H
