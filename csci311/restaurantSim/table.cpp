/**
 * @file table.cpp
 *
 * @brief
 *      Implementation of Table class
 *
 * @author Owen North
 * @date 9/1/20
 **/

#ifndef CSCI_311_TABLE_CPP
#define CSCI_311_TABLE_CPP
#include "table.h"
using std::string;

///////CONSTRUCTORS///////
Table::Table()
{
        tableID = nullptr;
        serverName = nullptr;
        party = nullptr;
}//End default constructor

Table::Table(const string &tableID, int numSeats, const string &serverName)
{
        this->tableID = new string(tableID);
        this->numSeats = numSeats;
        this->serverName = new string(serverName);
        this->party = nullptr;
}//End overloaded constructor

///////DESTRUCTOR///////
Table::~Table()
{
        delete tableID;
        delete serverName;
        delete party;
}//End destructor


///////SETTER (SEAT PARTY)///////
void Table::seatParty(const Party *newParty)
{
        Party* seated = new Party(*(newParty->getReservationName()), newParty->getNumDiners(), newParty->getTimeRequired());
        this->party = seated;
}


#endif
