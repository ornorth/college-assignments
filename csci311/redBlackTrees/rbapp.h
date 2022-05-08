/**
 * @file rbapp.h An application that stores information in a red-black tree.
 *
 * Note: put main() in rbapp.cpp - it should
 *                               - instantiate an RBapp
 *                               - call mainLoop()
 *
 * Note:    ******** DO NOT MAKE ANY CHANGES IN THIS FILE ********
 * This file is not turned in. If you make changes here your code will not
 * compile for me and you will get a zero on the assignment!
 * 
 * @author Judy Challinger
 * @date 10/23/14
 **/

#ifndef CSCI_311_RBAPP_H
#define CSCI_311_RBAPP_H

#include <string>
#include "rbtree.h"

using std::string;

class RBapp {
    public:
        void mainLoop();               // read & process commands until done
    private:
        RBTree myRBT;                  // the red black tree
        bool processCommand(string&);  // process command - return false on quit
        void processInsert(string&);   // insert into red-black tree
        void processPrint();           // print tree
        void processFind(string&);     // find & print all occurances of a key
        void processDelete(string&);   // delete from the red-black tree
};

#endif // CSCI_311_RBAPP_H
