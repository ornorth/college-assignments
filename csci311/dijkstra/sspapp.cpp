#include "sspapp.h"
#include <iostream>
#include <sstream>
#include <string>

using std::getline;
using std::cin;

void SSPapp::readGraph()
{
    unsigned numInputs,         //how many vertices/edges to process
             weight;            //weight of the edges being added
    string   input,             //feeds initial getline to istringstream,
                                    //then acts as a temp variable
             to;                //for myGraph::addEdge(): input=from, to=to
    char     delimiter = ' ';   //needed for parsing

    //vertices
    cin >> numInputs;
    cin.ignore();
    getline(cin, input);

    std::istringstream ss(input);
    for (unsigned i = 0; i < numInputs; ++i)
    {
        getline(ss, input, delimiter);
        myGraph.addVertex(input);
    }

    //edges
    cin >> numInputs;
    cin.ignore();
    for (unsigned i = 0; i < numInputs; ++i)
    {
        //set up istringstream
        getline(cin, input);
        std::istringstream ss(input);

        //read values of from, to, and weight
        getline(ss, input, delimiter);
        getline(ss, to, delimiter);
        ss >> weight;

        //add edge
        myGraph.addEdge(input, to, weight);
    }
}

void SSPapp::processQueries()
{
    string input, from, to;
    char delimiter = ' ';

    while(getline(cin, input))
    {
        if (input == "quit") break;

        std::istringstream ss(input);
        getline(ss, from, delimiter);
        getline(ss, to, delimiter);

        input = myGraph.getShortestPath(from, to);
        std::cout << input << std::endl;
    }
}

int main()
{
    SSPapp myapp;
    myapp.readGraph();
    myapp.processQueries();
    return 0;
}
