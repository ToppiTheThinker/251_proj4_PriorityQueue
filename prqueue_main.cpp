#include <iostream>
#include "prqueue.h"

using namespace std;

int main()
{
    cout << "Welcome to Christopher Harrison's implementation of a priority queue!" << endl;
    cout << "How many strings would you like to enter? ";
    int numStrings;
    cin >> numStrings;
    if (numStrings <= 0)
        cout << "Please enter a number greater than 0." << endl;
    if (numStrings > 2147483647)
    {
        cout << "Please enter a number less than 2147483648." << endl;
    }
    prqueue<string> stringsQueue;
    for (int i = 0; i < numStrings; i++)
    {
        string tmpStr;
        int tmpP;
        cout << "Please enter a string: ";
        cin >> tmpStr;
        cout << "Please enter a priority: ";
        cin >> tmpP;

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
            int tmpP;
            cout << "Please enter a string: ";
            cin >> tmpStr;
            cout << "Please enter a priority: ";
            cin >> tmpP;
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
