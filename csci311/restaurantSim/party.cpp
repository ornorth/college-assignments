/* *
 * @file party.cpp 
 * 
 * @brief 
 *      Implementation of Party member functions
 *
 * @author Owen North
 * @date 9/1/20
 **/



#ifndef CSCI_311_PARTY_CPP
#define CSCI_311_PARTY_CPP

#include "party.h"

using std::string;

///////CONSTRUCTORS///////
Party::Party()
{
        reservationName = nullptr;
}//End default constructor

Party::Party(const string& reservationName, int numDiners, int timeRequired)
{
       this->reservationName = new string(reservationName);
       this->numDiners = numDiners;
       this->timeRequired = timeRequired;
}//End overloaded constructor


///////DESTRUCTOR///////
Party::~Party()
{
        delete reservationName;
}

#endif
