#include <iostream>
#include "prqueue.h"

using namespace std;

bool isValidInput(const string &input)
{
    if (input.empty())
        return false;

    //determine that there are only numbers
    for (int i = 1; i < input.size(); i++)
        if (!isdigit(input[i]))
            return false;
    
    if (stoi(input) <= 0 || stoi(input) > 2147483647)
        return false;
    return true;
}

int main()
{
    //intro text
    cout << "Welcome to Christopher Harrison's implementation of a priority queue!" << endl;
    cout << "How many strings would you like to enter? ";
    string numStringsInput;
    cin >> numStringsInput;
    while (!isValidInput(numStringsInput))
    {
        cout << "Please enter a valid number." << endl;
        cin >> numStringsInput;
    }
    //convert string to int
    int numStrings = stoi(numStringsInput);

    prqueue<string> stringsQueue;
    for (int i = 0; i < numStrings; i++)
    {
        string tmpStr;
        string tmpPInput;
        cout << "Please enter a string: ";
        cin >> tmpStr;
        cout << "Please enter a priority for your string: ";
        cin >> tmpPInput;
        while (!isValidInput(tmpPInput))
        {
            cout << "Please enter a valid number." << endl;
            cin >> tmpPInput;
        }
        int tmpP = stoi(tmpPInput);

        stringsQueue.enqueue(tmpStr,tmpP);
    }

    stringsQueue.begin();
    string value;
    int priority;
    int count = 1;
    cout << "Here is the ordering of your strings: " << endl;
    stringsQueue.begin();
    while (stringsQueue.next(value, priority)) 
    {
        cout << count << ": " << value << " with priority ";
        cout << priority << endl;
        count++;
    }
    while (true)
    {
        string userChoice;
        cout << "Would you like to dequeue, enqueue, reset, or quit? ";
        cin >> userChoice;

        if (userChoice == "dequeue")
        {
            stringsQueue.dequeue();
        }
        else if (userChoice == "enqueue")
        {
            string tmpStr;
            string tmpPInput;
            cout << "Please enter a string: ";
            cin >> tmpStr;
            cout << "Please enter a priority: ";
            cin >> tmpPInput;
            while (!isValidInput(tmpPInput))
            {
                cout << "Please enter a valid number." << endl;
                cin >> tmpPInput;
            }
            int tmpP = stoi(tmpPInput);
            stringsQueue.enqueue(tmpStr,tmpP);
        }
        else if (userChoice == "reset")
        {
            stringsQueue.clear();
        }
        else if (userChoice == "quit")
        {
            break;
        }
        else
        {
            cout << "Please try again!" << endl;
            continue;
        }

        cout << "Here is the ordering of your strings: " << endl;
        stringsQueue.begin();
        count = 1;
        while (stringsQueue.next(value, priority)) 
        {
            cout << count << ": " << value << " with priority ";
            cout << priority << endl;
            count++;
        }
        
    }


    cout << "Thanks for using my priority queue!";
}
