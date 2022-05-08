/**
 *  @file rbapp.cpp
 *      Implementation of class RBapp, first defined in rbapp.h
 *      main()
 * 
 *  @author Owen North
 *  @date 11/2/2020
 **/
#ifndef CSCI_311_RBAPP_CPP
#define CSCI_311_RBAPP_CPP

#include "rbapp.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::getline;

/**
 *  RBapp::mainLoop
 *
 *  @brief  reads in values from standard input
 *          and passes them to a private function for processing
 *
 *          this function will run until either all input has been read
 *          or until the private function processes a "quit" command
 *
 *  @param  none
 *  @return none
 */
void RBapp::mainLoop()
{
    string input;
    while (getline(std::cin, input) && processCommand(input)) {}
}

/**
 *  RBapp::processCommand
 *
 *  @brief  parses a string that was read in by mainLoop
 *          and takes action / calls another function accordingly
 *
 *          commands take the form of [command] [arg1] [arg2] (space delimited)
 *          this function passes the arguments to the appropriate function
 *          
 *          *note that arguments are expected to be valid - no error handling
 *  
 *  @param  input   string to be parsed that was read in by mainLoop
 *  @return True if the command was not to quit the program,
 *          False otherwise
 */
bool RBapp::processCommand(string& input)
{
    string command;
    string data;
    std::istringstream ss(input);
    char delimiter = ' ';
    
    getline(ss, command, delimiter);
    getline(ss, data);
    
    if (command == "insert")
    {
        processInsert(data);
    }
    else if (command == "find")
    {
        processFind(data);
    }
    else if (command == "delete")
    {
        processDelete(data);
    }
    else if (command == "print")
    {
        processPrint();
    }
    else if (command == "quit")
    {
        return 0;
    }
    //Silently ignore errors - the program ignores any unrecognized input

    return 1;
}

/**
 *  RBapp::processInsert
 *
 *  @brief  parses the string passed to the function into a key/value pair
 *          and inserts that pair into myRBT
 *
 *  @param  input   the key/value pair to be parsed
 *  @return none
 */
void RBapp::processInsert(string& input)
{
    std::istringstream ss(input);
    char delimiter = ' ';
    string key, sdata;
    getline(ss, key, delimiter);
    getline(ss, sdata, delimiter);
    myRBT.rbInsert(key, sdata);
}

/**
 *  RBapp::processPrint
 *
 *  @brief  calls RBTree::rbPrintTree() for member variable myRBT
 *  @param  none
 *  @return none
 */
void RBapp::processPrint()
{
    myRBT.rbPrintTree();
}

/**
 *  RBapp::processFind
 *
 *  @brief  searches myRBT for all Nodes with a matching key
 *          and prints their key/value pair
 *
 *  @param  input   the key to be searched for
 *  @return none
 */
void RBapp::processFind(string& input)
{
    std::vector<const string*> values = myRBT.rbFind(input);
    for (auto a : values)
    {
        std::cout << input << " " << *a << std::endl;
    }
}

/**
 *  RBapp::processDelete
 *
 *  @brief  parses the string passed to the function into a key/value pair
 *          then deletes any elements in myRBT with that matching pair
 *
 *  @param  input   the arguments to be parsed
 *  @return none
 */
void RBapp::processDelete(string& input)
{
    std::istringstream ss(input);
    char delimiter = ' ';
    string key, sdata;
    getline(ss, key, delimiter);
    getline(ss, sdata, delimiter);
    myRBT.rbDelete(key, sdata);
}

/**
 *  main() driver
 *  
 *  instantiates an RBapp, then calls RBapp::mainLoop()
 *  @return 0
 **/
int main()
{
    RBapp myapp;
    myapp.mainLoop();
    return 0;
}

#endif
