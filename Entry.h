//
// Created by Jason Fujii on 10/12/20.
//
#include <iostream>
using namespace std;
#ifndef CSC340_PROJECT3_ENTRY_H
#define CSC340_PROJECT3_ENTRY_H


class Entry {
private:
    string word;
    string partOfSpeech;
    string def;

public:
    Entry();
    Entry(string&, string&, string&);
    string getWord();
    string getPOS();
    string getDef();
    string print();
    bool compareTo(Entry);
};


#endif //CSC340_PROJECT3_ENTRY_H
