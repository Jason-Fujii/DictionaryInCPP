//
// Created by Jason Fujii on 10/13/20.
//

#include "dictionary.h"
#include "mapVector.h"
#include "Entry.h"
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <fstream>

dictionary::dictionary()
{
    fstream file;
    map.addFile(file);
}

void dictionary::userInterface()
{
    int searchNum = 1;
    cout << "Enter '!help' to learn how to format your search." << endl;
    cout << "Enter '!q' to quit the program." << endl;
    cout << "Enter '!list' to see a list of searchable entries." << endl;

    while(!quit)
    {
        string input;
        cout << "Search [" << searchNum << "]: ";
        getline(cin, input);
//        cin >> input;
        if(input.empty())
        {
            input = "";
        }
        checkInput(input);
        searchNum++;
    }
}

void dictionary::checkInput(string &userInput) {

    if (userInput.empty() || userInput == " ")
        printAdmin("");
    else
    {
    vector<string> input;
    stringParser(input, userInput);

    input.at(0) = setLower(input.at(0));
    if (input.size() > 4)
        cout << "\t|\n\t<This dictionary accepts input of up to 4 words.>\n\t<Any words beyond that have been ignored>\n\t|"
                << endl;

    if (input.empty() || input.at(0).at(0) == '!' || input[0].empty())
        printAdmin(input[0]);
    else if (checkSameInput(input))
        printAdmin("");
    else {
        if (input.size() == 1)
        {
            map.Search(input[0]);
        }

        else if (input.size() == 2) {
            input[1] = setLower(input[1]);
            if (checkDistinct(input[1]))
                map.Search(input[0], "", true, false);
            else if (checkReverse(input[1]))
                map.Search(input[0], "", false, true);
            else if (checkPOS(input[1]))
                map.Search(input[0], input[1]);
            else {
                printErrors(2, input[1], checkPOS(input[1]), checkDistinct(input[1]), checkReverse(input[1]));
                map.Search(input[0]);
            }
        } else if (input.size() == 3) {
            input[1] = setLower(input[1]);
            input[2] = setLower(input[2]);
            if (checkDistinct(input[1])) {
                if (checkReverse(input[2]))
                    map.Search(input[0], "", true, true);
                else {
                    printErrors(3, input[2], checkPOS(input[2]), checkDistinct(input[2]), checkReverse(input[2]));
                    map.Search(input[0], "", true, false);
                }
            } else if (checkReverse(input[1])) {
                cout << "\t|\n\t<'Reverse' should be the last value input>\n\t|" << endl;
                map.Search(input[0], "", false, true);
            } else if (checkPOS(input[1])) {
                //check if distinct or reverse is in 3
                if (checkDistinct(input[2]))
                    map.Search(input[0], input[1], true, false);
                else if (checkReverse(input[2]))
                    map.Search(input[0], input[1], false, true);
                    //Search(input[0],input[1],"reverse");
                else {
                    printErrors(3, input[2], checkPOS(input[2]), checkDistinct(input[2]), checkReverse(input[2]));
                    map.Search(input[0], input[1]);
                }
            } else {
                printErrors(2, input[1], checkPOS(input[1]), checkDistinct(input[1]), checkReverse(input[1]));
                if (checkDistinct(input[2])) {

                    map.Search(input[0], "", true, false);
                } else if (checkReverse(input[2])) {
                    map.Search(input[0], "", false, true);
                } else if (checkPOS(input[2])) {
                    map.Search(input[0], input[2]);
                } else {
                    printErrors(3, input[2], checkPOS(input[2]), checkDistinct(input[2]), checkReverse(input[2]));
                    map.Search(input[0]);
                }
            }
        } else if (input.size() >= 4) {
            input[1] = setLower(input[1]);
            input[2] = setLower(input[2]);
            input[3] = setLower(input[3]);
            //check input[1]
            //check if distinct is in 2 or 3
            //check if reverse is in 2, 3, or 4
            if (checkDistinct(input[1])) {
                if (checkReverse(input[2])) {
                    //Search(input[0], "distinct", "reverse");
                    cout << "\t<The entered 4th parameter '" << input[3] << "' was disregarded.>\n\t|" << endl;
                    map.Search(input[0], "", true, true);
                } else {
                    printErrors(3, input[2], checkPOS(input[2]), checkDistinct(input[2]), checkReverse(input[2]));
                    if (checkReverse(input[3])) {
                        map.Search(input[0], "", true, true);
                    } else {
                        printErrors(4, input[3], checkPOS(input[3]), checkDistinct(input[3]), checkReverse(input[3]));
                        map.Search(input[0], "", true, false);
                    }
                }
            } else if (checkReverse(input[1])) {
                cout << "\t|\n\t<'Reverse' should be the last qualifier included.>\n\t|" << endl;
                map.Search(input[0], "", false, true);
            } else if (checkPOS(input[1])) {
                //check if distinct or reverse is in 3
                if (checkDistinct(input[2])) {
                    if (checkReverse(input[3]))
                        map.Search(input[0], input[1], true, true);
                    else {
                        cout << "\t|\n\t<The entered 4th parameter should be 'reverse.'>" << endl;
                        printErrors(4, input[3], checkPOS(input[3]), checkDistinct(input[3]), checkReverse(input[3]));
                        map.Search(input[0], input[1], true, false);
                    }
                } else if (checkReverse(input[2])) {
                    //Search(input[0],input[1],"reverse");
                    cout << "\t|\n\t<'Reverse' should be the last command>" << endl;
                    map.Search(input[0], input[1], false, true);
                } else {
                    printErrors(3, input[2], checkPOS(input[2]), checkDistinct(input[2]), checkReverse(input[2]));
                    if (checkReverse(input[3])) {
                        map.Search(input[0], input[1], false, true);
                        //Search(input[0[, input[1], "reverse");
                    } else if (checkDistinct(input[3])) {
                        map.Search(input[0], input[1], true, false);
                    } else {
                        printErrors(4, input[3], checkPOS(input[3]), checkDistinct(input[3]), checkReverse(input[3]));
                        map.Search(input[0], input[1], false, false);
                    }
                }
            } else {
                //input[1] is bad
                printErrors(2, input[1], checkPOS(input[1]), checkDistinct(input[1]), checkReverse(input[1]));
                if (checkDistinct(input[2])) {
                    if (checkReverse(input[3])) {
                        map.Search(input[0], "", true, true);
                    } else {
                        printErrors(4, input[3], checkPOS(input[3]), checkDistinct(input[3]), checkReverse(input[3]));
                        map.Search(input[0], "", true, false);
                    }
                } else if (checkReverse(input[2])) {
                    cout << "\t|\n\t<'Reverse' should be the last command>\n\t|" << endl;
                    map.Search(input[0], "", false, true);
                } else if (checkPOS(input[2])) {
                    if (checkDistinct(input[3])) {
                        map.Search(input[0], input[2], true, false);
                    } else if (checkReverse(input[3])) {
                        map.Search(input[0], input[2], false, true);
                    } else {
                        printErrors(4, input[3], checkPOS(input[3]), checkDistinct(input[3]), checkReverse(input[3]));
                        map.Search(input[0], input[2]);
                    }
                } else {
                    printErrors(3, input[2], checkPOS(input[2]), checkDistinct(input[2]), checkReverse(input[2]));
                    if (checkDistinct(input[3])) {
                        map.Search(input[0], "", true, false);
                    } else if (checkReverse(input[3])) {
                        map.Search(input[0], "", false, true);
                    } else if (checkPOS(input[3])) {
                        map.Search(input[0], input[3]);
                    } else {
                        printErrors(4, input[3], checkPOS(input[3]), checkDistinct(input[3]), checkReverse(input[3]));
                        map.Search(input[0]);
                    }
                }
            }
        }
    }
}
}

void dictionary::printAdmin(string input)
{
    if(input.empty() || input == "!help")
    {
        cout << "\t|\n\tPARAMETER HOW-TO, please enter:" << endl;
        cout << "\t1. A search key -then 2. An optional part of speech -then\n\t3. An optional 'distinct' -then";
        cout << " 4. An optional 'reverse'\n\t|" << endl;
    }
    //input == "q"
    if(input  == "!q" ||input == "!quit")
    {
        quit = true;
        cout << "-----THANK YOU-----" << endl;
    }
    //input == "!list"
    if(input == "!list")
    {
        map.printAllKeys();
    }
}

bool dictionary::checkPOS(string str)
{
    string s = setLower(str);
    return (s == "noun" || s == "adjective" || s == "adverb" ||
            s == "conjunction" || s == "interjection" || s == "preposition" ||
            s == "pronoun" || s == "verb");
}

bool dictionary::checkDistinct(string str)
{
    string s = setLower(str);
    return s == "distinct";
}

bool dictionary::checkReverse(string str)
{
    string s = setLower(str);
    return s == "reverse";
}

void dictionary::printErrors(int place, string in, bool pos, bool dist, bool rev)
{
    string pl;
    switch(place)
    {
        case 2:
        {
            pl = "2nd";
            break;
        }
        case 3:
        {
            pl = "3rd";
            break;
        }
        case 4:
        {
            pl = "4th";
            break;
        }
        default:
            pl = "2nd";
    }
    cout << "\t|" << endl;
    //not a part of speech
    if(!pos)
        cout << "\t<The entered " << pl << " parameter \"" << in << "\" is NOT a part of speech.>" << endl;
    //not "distinct"
    if(!dist)
        cout << "\t<The entered " << pl << " parameter \"" << in << "\" is NOT 'distinct.'>" << endl;
    //not "reverse"
    if(!rev)
        cout << "\t<The entered " << pl << " parameter \"" << in << "\" is NOT 'reverse.'>" << endl;
    //none of them
    if(!pos && !dist && !rev)
        cout << "\t<The " << pl << " parameter should be a part of speech, 'distinct,' or 'reverse'>" << endl;

    //Always print
    cout << "\t<The entered "  << pl << " parameter \"" << in << "\" was disregarded.>" << endl;
    cout << "\t|" << endl;
}

bool dictionary::checkSameInput(vector<string> &currInput)
{
    int min;
    if(currInput.size() < lastInput.size())
        min = currInput.size();
    else
    {
        //current is longer
        for(int i = 0; i < 4; i++)
        {
            lastInput[i] = currInput[i];
            return false;
        }
    }
        min = lastInput.size();

    int numSame = 0;
    for(int i = 0; i < min; i++)
    {
        if(lastInput[i] == currInput[i])
            numSame++;
    }

    for(string s: lastInput)
    {
        s = "";
    }
    for(int i = 0; i < currInput.size(); i++)
    {
        lastInput[i] = currInput[i];
    }

    if(numSame == currInput.size())
        return true;
    else
        return false;
}

void dictionary::stringParser(vector<string> &input, string &userInput)
{

    if(userInput.find(' ') == 0)
    {
        string str = userInput.substr(1);
        stringParser(input, str);
    }
    else if(userInput.find(' ') == -1)
    {
        input.push_back(userInput);
    }
    else
    {
        int nextSpace(userInput.find(' '));
        string word = userInput.substr(0, nextSpace);
        input.push_back(word);

        string str = userInput.substr(nextSpace + 1);
        stringParser(input, str);
    }
}

string dictionary::setLower(string& str)
{
    string lowerCase;
    for(char c: str)
    {
        lowerCase.push_back((char)tolower(c));
    }
    return lowerCase;
}