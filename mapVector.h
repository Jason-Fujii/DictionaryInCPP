//
// Created by Jason Fujii on 10/13/20.
//

#ifndef CSC340_PROJECT3_MAPVECTOR_H
#define CSC340_PROJECT3_MAPVECTOR_H

#include <iostream>
using namespace std;

#include <map>
#include <vector>
#include "Entry.h"

class mapVector {
private:

    void wordParse(vector<Entry>&, string&, string&, string&, string&);

public:
    /*
     * Creates a new mapVector object
     */
    mapVector();
    map<string, vector<Entry>> map;
    /*
     * add() takes an Entry object and inserts it into the mapVector.
     * Checks if the word is already in a key in the mapVector
     *      if yes, add the rest of the entry to the mapVector
     *      if no, add the key, then create the vector
     */
    void add(Entry&);

    /*
     * iterates through a file, turns every element into an Entry obj, then adds that Entry object to the mapVector
     */
    void addFile(fstream&);

    /*
     * remove(string) removes all entries at that specified key value
     */
    void remove(string);

    /*
     * remove(Entry) removes an Entry object from the mapVector
     */
    void remove(Entry&);

    /*
     * Search(string) is used when the user only inputs a single word
     * It searches the map for the chosen key, then prints everything in that key's vector
     * If the key cannot be found, print out this message:
     *      <NOT FOUND> To be considered for the next release
     */
    void Search(string);

    /*
     * Search(string, string) takes the key value and a part of speech
     * It searches the map for the chosen key, then only prints the entries with the specified part of speech
     */
    void Search(string, string);

    /*
     * Search(string, string, bool, bool) takes the key, part of speech, and booleans for distinct and reverse
     * It searches the table for the chosen key, find the values with the specified part of speech, then applies the
     * distinct and reverse functions if needed.
     */
    void Search(string, string, bool, bool);

    /*
     * Prints out the entirety of the map in the format:
     * [word] [pos] : [desc]
     */
    void printAll();

    /*
     * Prints a list of all the keys for the user to view their options
     */
    void printAllKeys();

    /*
     * Prints all entries in the vector at the searched Key
     */
    void printKey(string);

    /*
     * Prints all values at Key with the chosen part of speech
     */
    void printPOS(string, string);

    /*
     * Input: vector<string>
     * takes a new vector from distinctify() and prints out the terms with the chosen part of speech
     */
    void printDistinct(vector<Entry>&, string);

    /*
     * Input: string key, string part of speech, boolean distinct, boolean reverse
     * Takes account of distinct and reverse.
     * If distinct is true, no repeat entries will be printed
     * If reverse is true, the list will print backwards
     */
    void qualifiedPrint(string, string, bool, bool);

    /*
     * Input:
     * Iterates through the vector at Key and returns a vector of unique entries
     */
    vector<Entry> distinctify(string);

    /*
     * Input: vector<Entry> list, string part of speech
     * Takes a vector of entries and prints them in reverse according to the part of speech that was input.
     */
    void reversePrint(vector<Entry>&, string);

};

/*
 * Vector Constructors!
 *      vector<T> v1(): empty vector of element T
 *      vector<T> v2(4, 100): vector of size 4 with value 100 in each index
 *      vector<T> v3(v2): a copy of v2
 * Useful vector functions!
 *      int size(): returns number of elements in the vector
 *      bool empty(); returns true if vector is empty, false otherwise
 *      vector[index]: returns the element at index. Used to instantiate the index
 *      at(index): returns the element at index. Throws an out of bounds exception if the index doesn't exist. Used to instantiate the index
 *      front(): returns/accesses the first element
 *      back(): returns/accesses the last element
 *      swap(vector& v): swaps the contents of *this* vector with the contents of v
 *      clear(): empties the vector and leaves it with a size of 0
 */

/*
 * Map Constructors!
 *      map<T, K> m: an empty map with key value T and value value of K
 *      m['a'] = 10: with T = char, K = int, declaring that key 'a' has value 10
 * Useful map functions!
 *      empty(): returns true if map container has size 0
 *      size(): returns the number of elements the map contains (number of keys)
 *      map[key]: accesses the element at key. Used to change the element or to access it
 *      at(key): accesses the element at key. Used to change the element or to access it
 *      find(key): returns map.end (an iterator) if the key isn't found
 *          if(map.find(key) != map.end()) --> Key found!
 *          else --> Key not found!
 */
#endif //CSC340_PROJECT3_MAPVECTOR_H
