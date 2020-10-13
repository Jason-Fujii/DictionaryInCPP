#include <iostream>
using namespace std;
#include <vector>
#include <iomanip>

bool isvalidcc(const string&);
int intForChar(char);

int main()
{
    //
    // PLEASE DO NOT CHANGE function main
    //
    vector<string> cardnumbers = {
            "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
            "4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
            "5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
            "4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
            "5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
            "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
            "4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
            "5556551555555557", "6011316011016011"
    };

    int i;
    vector<string>::iterator itr;

    for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
        cout << setw(2)  << i << " "
             << setw(17) << *itr
             << ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
    }

    return 0;
}

/*
 * A: double every second digit from right to left. If this results in a double digit number, add the individual digits together
 *      Once completed, add all of those numbers together
 * B: add together all the odd digits from right to left
 * C: add the sums from A and B together
 * D: if C%10 == 0, card is valid. otherwise, card is invalid.
 */
bool isvalidcc(const string &str)
{
    int evens = 0;
    int odds = 0;
    int sum = 0;
    int count = 1;
    for(int i = str.size() - 1; i >= 0; i--)
    {
        //odds
        if(count % 2 == 1){
            int x = intForChar(str.at(i));
            odds += x;
        }
            //evens
        else{
            int temp = intForChar(str.at(i))*2;
            if(temp > 9)
            {
                evens += temp % 10;
                temp /= 10;
                evens += temp;
            }
            else
                evens += temp;
        }
        count++;
    }
    sum = evens + odds;
    return sum % 10 == 0;
}

//A helper method to turn the character digit into an integer
int intForChar(char c)
{
    switch(c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return -1;
    }
}