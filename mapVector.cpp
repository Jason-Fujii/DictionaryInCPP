//
// Created by Jason Fujii on 10/13/20.
//

#include "mapVector.h"
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <fstream>
#include "Entry.h"

mapVector::mapVector()
{
    std::map<string, vector<Entry>> map;
}

void mapVector::add(Entry &e)
{
    string key = e.getWord();
    //if the key isn't in the map
    if(map.find(key) == map.end())
    {
        vector<Entry> v = {e};
        map.insert({e.getWord(), v});
    }
    //if the key is in the map
    else
    {
        map[e.getWord()].push_back(e);
    }
}

void mapVector::addFile(fstream &file)
{
    string line;
    file.open("/Users/jasonfujii/CLionProjects/CSC340_Project3/Data.CS.SFSU.txt", ios::in);
    if(!file.is_open())
    {
        cout << "The file entered cannot be opened. Please check the file name provided in mapVector.cpp in function addFile(fstream)" << endl;
        exit(1);
    }

    while(getline(file, line))
    {
        //the first section will be the word
        string name = line.substr(0, line.find("|"));
        vector<Entry> list;
        //the next sections are between "|". take a substring between those and then take the info between those
        string pos, def;
        string newString = line.substr(line.find("|") + 1);
        wordParse(list, name, newString, pos, def);

        map.insert({name, list});
    }

    file.close();
    cout << "File closed" << endl;
}

void mapVector::wordParse(vector<Entry>& list, string& name, string& line, string& pos, string& def)
{
    if(line.find("|") == 0 )
    {
        string s = line.substr(1);
        wordParse(list, name, s, pos, def);
    }
    else if(line.find("|") == -1)
    {
        int endPos = line.find("-=>>");
        pos = line.substr(0, endPos - 1);
        def = line.substr(endPos + 5);
        Entry entry(name, pos, def);
        list.push_back(entry);
    }
    else
    {
        int endPos = line.find("-=>>");
        int endDef = line.find('|');
        int defLength = endDef - (endPos + 5);
        pos = line.substr(0, endPos - 1);
        def = line.substr(endPos + 5, defLength);
        Entry entry(name, pos, def);
        list.push_back(entry);

        string newString = line.substr(line.find("|") + 1);
        wordParse(list, name, newString, pos, def);
    }
}
//book|noun -=>> A set of pages.|verb -=>> To arrange something on a particular date.|verb -=>> to arrange for someone to have a seat on a plane.|noun -=>> A written work published in printed or electronic form.

void mapVector::remove(string key)
{
    if(map.find(key) != map.end())
        map.erase(key);
    else
        cout << "\"" << key << "\" is not in the dictionary." << endl;
}

void mapVector::remove(Entry &e)
{
    if(!map.empty()) {
        string key = e.getWord();
        if (map.find(key) != map.end()) {
            vector<Entry>::iterator it;
            for (it = map.at(key).begin(); it < map.at(key).end(); it++) {
                int index = std::distance(map.at(key).begin(), it);
                if (map.at(key).at(index).compareTo(e)) {
                    map.at(key).erase(it);
                    cout << "Entry successfully removed." << endl;
                }
            }
        } else
            cout << "| \n<NOT FOUND> To be considered for the next release.\n|" << endl;
    } else
        cout << "\tThe dictionary is empty..." << endl;
}

void mapVector::Search(string key)
{
    cout << "\t|" << endl;
    printKey(key);
    cout << "\t|" << endl;
}

void mapVector::Search(string key, string pos)
{
    cout << "\t|" << endl;
    printPOS(key, pos);
    cout << "\t|" << endl;
}


void mapVector::Search(string key, string pos, bool dist, bool rev)
{
    if(pos.empty() && !dist && !rev)
    {
        //only key provided
        Search(key);
    }
    else if(!dist && !rev)
    {
        //key and POS
        Search(key, pos);
    } else
        qualifiedPrint(key, pos, dist, rev);
}

void mapVector::printAll()
{
    if(!map.empty())
    {
        for(auto m: map)
        {
            for(int i = 0; i < m.second.size(); i++)
            {
                cout << "\t" << m.second.at(i).print() << endl;
            }
        }
    } else
        cout << "\tThe dictionary is empty..." << endl;
}

void mapVector::printAllKeys()
{
    if(!map.empty())
    {
        int count = 0;
        cout << "Choose from these entries: \n\t";
        for(auto m: map)
        {
            if(count%6 == 5) {
                cout << "\n\t" << m.second.at(0).getWord() << ", ";
                count = 0;
            }
            else
                cout << m.second.at(0).getWord() << ", ";
            count++;
        }
    } else
        cout << "\tThe dictionary is empty..." << endl;
}

void mapVector::printKey(string key)
{
    if(!map.empty())
    {
        if(map.find(key) != map.end())
        {
            for(Entry e: map.at(key))
            {
                cout << "\t" << e.print() << endl;
            }
        } else
            cout << "\t|\n\t<NOT FOUND> To be considered for the next release.\n\t|" << endl;
    } else
        cout << "\tThe dictionary is empty..." << endl;
}

void mapVector::printPOS(string key, string pos)
{
    if(!map.empty())
    {
        if(map.find(key) != map.end())
        {
            int count = 0;
            for(Entry e: map.at(key))
            {
                if(e.getPOS().compare(pos) == 0) {
                    cout << "\t" << e.print() << endl;
                    count++;
                }
            }
            if(count ==0)
                cout << "\t|\n\t<NOT FOUND> To be considered for the next release.\n\t|" << endl;
        }
        else
            cout << "\t|\n\t<NOT FOUND> To be considered for the next release.\n\t|" << endl;
    } else
        cout << "\tThe dictionary is empty..." << endl;
}

void mapVector::printDistinct(vector<Entry> &list, string pos)
{
    if(!map.empty())
    {
        if(!pos.empty())
        {
            int count = 0;
            for(Entry e: list)
            {
                if(e.getPOS().compare(pos) == 0)
                {
                    cout << "\t" << e.print() << endl;
                    count++;
                } else
                    cout << "\t|\n\t<NOT FOUND> To be considered for the next release.\n\t|" << endl;
            }
        } else
        {
            for(Entry e: list)
                cout << "\t" << e.print() << endl;
        }
    } else
        cout << "\tThe dictionary is empty..." << endl;
}

void mapVector::qualifiedPrint(string key, string pos, bool dist, bool rev)
{
    if(!map.empty())
    {
        if(map.find(key) != map.end())
        {
            if(!pos.empty())
            {
                //if dist & rev are *BOTH* true
                if(dist && rev)
                {
                    vector<Entry> distinct = distinctify(key);
                    cout << "\t|" << endl;
                    reversePrint(distinct, pos);
                    cout << "\t|" << endl;
                }
                //only dist is true
                else if(dist)
                {
                    vector<Entry> distinct = distinctify(key);
                    cout << "\t|" << endl;
                    printDistinct(distinct, pos);
                    cout << "\t|" << endl;
                }
                //only rev is true
                else if(rev)
                {
                    cout << "\t|" << endl;
                    reversePrint(map.at(key), pos);
                    cout << "\t|" << endl;
                }
                //dist and rev are *BOTH* false
                else
                {
                    cout << "\t|" << endl;
                    printPOS(key, pos);
                    cout << "\t|" << endl;
                }
            } else
            {
                if(dist && rev)
                {
                    vector<Entry> distinct = distinctify(key);
                    cout << "\t|" << endl;
                    reversePrint(distinct, "");
                    cout << "\t|" << endl;
                }
                else if(dist)
                {
                    vector<Entry> distinct = distinctify(key);
                    cout << "\t|" << endl;
                    printDistinct(distinct, "");
                    cout << "\t|" << endl;
                }
                else if(rev)
                {
                    cout << "\t|" << endl;
                    reversePrint(map.at(key), "");
                    cout << "\t|" << endl;
                } else
                {
                    cout << "\t|" << endl;
                    printPOS(key, "");
                    cout << "\t|" << endl;
                }
            }
        } else
            cout << "\t|\n\t<NOT FOUND> To be considered for the next release.\n\t|" << endl;
    } else
        cout << "\tThe dictionary is empty..." << endl;
}

vector<Entry> mapVector::distinctify(string key)
{
    vector<Entry> entries;
    if(!map.empty())
    {
        if(map.find(key) != map.end())
        {
            entries.push_back(map.at(key).at(0));
            for(Entry e: map.at(key))
            {
                bool dist = true;
                for(Entry e2: entries)
                {
                    if(e.compareTo(e2))
                        dist = false;
                }
                if(dist)
                    entries.push_back(e);
            }
        } else
            cout << "\t|\n\t<NOT FOUND> To be considered for the next release.\n\t|" << endl;
    } else
        cout << "\tThe dictionary is empty..." << endl;

    return entries;
}

void mapVector::reversePrint(vector<Entry> &list, string pos)
{
    if(pos.empty())
    {
        for(int i = list.size(); i >= 0; i--)
        {
            cout << "\t" << list.at(i).print() << endl;
        }
    } else
    {
        int count = 0;
        for(int i = list.size(); i >= 0; i--)
        {
            if(list.at(i).getPOS().compare(pos) == 0)
            {
                cout << "\t" << list.at(i).print() << endl;
                count++;
            }
        }
        if(count == 0)
            cout << "\t|\n\t<NOT FOUND> To be considered for the next release.\n\t|" << endl;
    }
}
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