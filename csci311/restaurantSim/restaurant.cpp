/**
 * @file restaurant.cpp
 *
 * @brief
 *      Implementation of Restaurant class
 *      main()
 *
 * @author Owen North
 * @date 9/1/20
 **/

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include "restaurant.h"

using std::string;


/**
 * @brief populates Restaurant objects Table and Party
 * @param none
 * @return none
 *
 * Reads in an unknown amount of lines from standard input
 * and creates corresponding objects for use in serveParties()
 *
 **/
void Restaurant::getInput()
{
        bool flag = true;     //to break loop
        char delimiter = ' '; //for parsing
        string input;         //temporary container
        while (flag)
        {
                std::getline(std::cin, input);

                //begin parsing
                std::istringstream ss(input);
                std::getline(ss, input, delimiter);

                //input is a table
                if (input == "table")
                {
                        //tableID
                        string tableID;
                        std::getline(ss, tableID, delimiter);
                        //numSeats
                        string numSeats;
                        std::getline(ss, numSeats, delimiter);
                        //serverName
                        string serverName;
                        std::getline(ss, serverName, delimiter);
                        servers[serverName] = 0;

                        //create table object
                        Table *myTable = new Table(tableID, std::stoi(numSeats), serverName);
                        available.append(myTable);
                }
                //input is a party
                else if (input == "party")
                {
                        //numDiners
                        string numDiners;
                        std::getline(ss, numDiners, delimiter);
                        //reservationName
                        string reservationName;
                        std::getline(ss, reservationName, delimiter);
                        //timeReqiured
                        string timeRequired;
                        std::getline(ss, timeRequired, delimiter);

                        //create Party object
                        Party *myParty = new Party(reservationName, stoi(numDiners), stoi(timeRequired));
                        waiting.append(myParty);
                }
                //end input
                else
                {
                        flag = false;
                }
        }
}

void Restaurant::serveParties()
{
        bool restaurantIsOpen = true;
        Table* currTable = nullptr;
        Party* currParty = nullptr;

        //begin simulation
        while(restaurantIsOpen)
        {
                //occupied tables
                currTable = occupied.first();
                while(currTable != nullptr)
                {
                        currTable->decrementTimer();
                        //clear table and append to available
                        if (currTable->getTimer() == 0)
                        {
                                std::cout << *currTable->getParty()->getReservationName() << " finished at " << *currTable->getTableID() << std::endl;
                                currTable->clearTable();
                                available.append(currTable);
                                currTable = occupied.remove();
                        }

                        //advance to next occupied table
                        else
                        {
                                currTable = occupied.next();
                        }
                }

                //waiting parties
                currParty = waiting.first();
                while (currParty)
                {
                        bool partyWasSeated = false;
                        //loop through available tables
                        currTable = available.first();
                        while (currTable)
                        {
                                if (currTable->getNumSeats() >= currParty->getNumDiners())
                                {
                                        //seat party
                                        std::cout << *currParty->getReservationName() << " seated at " << *currTable->getTableID() << std::endl;
                                        currTable->seatParty(currParty);
                                        currTable->setTimer(currParty->getTimeRequired());
                                        //update server info
                                        servers.at(*currTable->getServerName()) += currParty->getNumDiners();
                                        //move currTable to occupied
                                        occupied.append(currTable);
                                        currTable = available.remove();
                                        partyWasSeated = true;
                                        break;
                                }
                                else
                                {
                                        currTable = available.next();
                                }
                        }
                        if (partyWasSeated)
                        {
                                currParty = waiting.remove();
                        }
                        else
                        {
                            currParty = waiting.next();
                        }
                }

                //all parties served
                if (waiting.empty() && occupied.empty())
                {
                        //print server information
                        for (std::pair<string, int> a : servers)
                        {
                                std::cout << a.first << " served " << a.second << std::endl;
                        }
                        //close restaurant
                        restaurantIsOpen = false;
                }
        }
}


int main()
{
        Restaurant myRestaurant;

        myRestaurant.getInput();
        myRestaurant.serveParties();

        return 0;
}
