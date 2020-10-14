//
// Created by Jason Fujii on 10/12/20.
//

#include "Entry.h"
#include <iostream>
using namespace std;


Entry::Entry()
{
    word = "Placeholder";
    partOfSpeech = "noun";
    def = "To be updated...";
}

Entry::Entry(string &w, string &pos, string &d)
{
    this->word = w;
    this->partOfSpeech = pos;
    this->def = d;
}

string Entry::getWord()
{
    return this->word;
}

string Entry::getPOS()
{
    return this->partOfSpeech;
}

string Entry::getDef()
{
    return this->def;
}

string Entry::print()
{
    return this->word + " [" + this->partOfSpeech + "] : " + this->def;
}

bool Entry::compareTo(Entry e)
{
    return (this->word.compare(e.getWord()) + this->partOfSpeech.compare(e.getPOS()) + this->def.compare(e.getDef()) == 0);
}

