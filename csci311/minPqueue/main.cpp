/**
 *  @file   main.cpp
 *
 *  @brief  test driver for class MinPriorityQueue
 *
 *  @author Owen North
 *  @date   10/19/2020
 */
#include <iostream>
#include <string>
#include <sstream>
#include "minpriority.h"

using std::getline;
using std::cout;


int main()
{
    MinPriorityQueue myQueue;
    string input;
    string command, id, key;
    char delimiter = ' ';

    bool flag = true;
    while (flag)
    {
        getline(std::cin, input);
        std::istringstream ss(input);

        getline(ss, command, delimiter);
        cout << input << std::endl;

        switch (command[0])
        {
            case 'a':
                getline(ss, id, delimiter);
                getline(ss, key, delimiter);

                myQueue.insert(id, stoi(key));
                break;

            case 'd':
                getline(ss, id, delimiter);
                getline(ss, key, delimiter);

                myQueue.decreaseKey(id, stoi(key));
                break;

            case 'x':
                cout << myQueue.extractMin() << std::endl;
                break;

            case 'q':
                flag = false;
                break;
        }
    }
    return 0;
}
