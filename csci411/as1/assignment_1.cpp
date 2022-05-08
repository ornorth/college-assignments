// CSCI 411 - Spring 2021
// Assignment 1
// Author: Carter Tillquist & Owen North

#include <iostream>
#include <vector>
using namespace std;

/*****************************************************************************
 *  * A simple Node struct                                                   *
 *  * id - int - the id or name of the node                                  *
 *  * SCC - int - the strongly connected component that this node belongs to *
 *  * visited - bool - whether or not this node has been visited             *
 *  * ************************************************************************/
struct Node {
    int id;
    int SCC;
    bool visited;
};

/*****************************************************************************************************
 *  * A simple struct of strongly connected component (SCC) graph nodes                              *
 *  * id - int - the id or name of the node (this corresponds to the SCC id)                         *
 *  * size - int - the number of nodes from the original graph that belong to this SCC               *
 *  * hasInEdges - bool - true if there are edges with end points in this SCC and false otherwise    *
 *  * hasOutEdges - bool - true if there are edges with start points in this SCC and false otherwise *
 *  * ************************************************************************************************/
struct SCCNode {
    int id;
    int size;
    bool hasInEdges;
    bool hasOutEdges;
};

/******************************************************************************************
 *  * Given the adjacency list of a graph, generate a new adjacency list with the         *
 *  * same nodes but with edges reversed                                                  *
 *  * A - vector<vector<Node*>> - an adjacency list representation of a graph. Note that  * 
 *  *   A[0] is a list of all the Nodes in the graph with an additional dummy Node at     * 
 *  *   A[0][0]. As a result, A[i] are the neighbors of the Node with id i where these    *
 *  *   ids go from 1 to n, the size of the graph.                                        *
 *  * return - vector<vector<Node*>> - an adjacency list of a new graph equivalent to the *
 *  *        original but with edges reversed.                                            *
 *  * *************************************************************************************/
vector<vector<Node*>> reverseEdges(vector<vector<Node*>> A)
{
    vector<vector<Node*>> Ar(A.size());
    Ar[0] = A[0];
    for (unsigned i = 1; i < A.size(); i++)
    {
        for (unsigned j = 0; j < A[i].size(); j++)
        {
            Ar[A[i][j]->id].push_back(A[0][i]);
        }
    }
    return Ar;
}

/********************************************************************************************************
 * A variation of DFS for the first pass over a graph looking for strongly connected components.        *
 * The goal is to fill the vector L with nodes in decreasing order with respect to finishing time       *
 * A - vector<vector<Node*>> - an adjacency list                                                        *
 * v - Node* - the start node for the DFS                                                               *
 * &L - vector<Node*> - a list of nodes to be filled in decreasing order with respect to finishing time *
 * ******************************************************************************************************/
void DFSSCC(vector<vector<Node*>> A, Node* v, vector<Node*> &L)
{
    //Properly, I should reinitialize each node's "visited" to false - but this is the first DFS and will only run once
    v->visited = true;
    for (unsigned i = 0; i < A[v->id].size(); i++)
    {
        if (A[v->id][i]->visited == false)
        {
            DFSSCC(A, A[v->id][i], L);
        }
    }
    L.push_back(v);
}

/******************************************************************************************************************
 * A variation of DFS for the second pass over a graph looking for strongly connected components.                 *
 * The goal is to determine which nodes in this metagraph have incoming and outgoing edges.                                      *
 * A - vector<vector<Node*>> - an adjacency list representing the transpose or edge reverse of the original graph *
 * v - Node* - the start node for the DFS                                                                         *
 * scc - int - the current strongly connected component id                                                        *
 * &SCCs - vector<SCCNode*> - the nodes of a SCC metagraph                                                        *
 ******************************************************************************************************************/
void DFSAssign(vector<vector<Node*>> A, Node* v, int scc, vector<SCCNode*> &SCCs)
{
    v->visited = true;

    //Find the SCC that the current node belongs to
    SCCNode* currSCC = SCCs[0];
    for (unsigned q = 1; q < SCCs.size(); q++)
    {
        if (currSCC->id != v->SCC)
        {
            currSCC = SCCs[q];
        }
        else break;
    }

    //Determine if this node was found by another SCC - if so, this node's SCC has inward edges
    if (v->SCC != scc)
    {
        currSCC->hasInEdges = true;
    }

    for (unsigned i = 0; i < A[v->id].size(); i++)
    {
        //If this node points to a node belonging to a different SCC, this node has outward edges
        if (A[v->id][i]->SCC != v->SCC)
        {
            currSCC->hasOutEdges = true;
        }

        //DFS recurse
        if (A[v->id][i]->visited == false)
        {
            DFSAssign(A, A[v->id][i], v->SCC, SCCs);
        }
    }
}

/******************************************************************************************************
 * Find the strongly connected components (SCCs) of a graph. The SCC of each Node is added to the SCC *
 * member of the Node struct. In addition, a vector of SCCNode* is returned.                          *
 * A - vector<vector<Node*>> - an adjacency list                                                      *
 * return - vector<SCCNode*> - a vector of nodes in the SCC metagraph of A                            *
 * ****************************************************************************************************/
vector<SCCNode*> SCC(vector<vector<Node*>> A)
{
    //Declare a reversed graph and a metagraph of SCC's
    vector<vector<Node*>> Ar = reverseEdges(A);
    vector<SCCNode*> SCCs;

    //DFS outer function
    for (unsigned i = 1; i < A[0].size(); i++)
    {
        //All nodes start outside of a SCC - those that have been identified already can be skipped
        if (A[0][i]->SCC == -1)
        {
            //Create two vectors to track whick nodes are found in the original and reversed graphs
            vector<Node*> origL, revL;
            DFSSCC(A, A[0][i], origL);

            //Reset nodes for second DFS
            for (auto q : origL)
            {
                q->visited = false;
            }
            DFSSCC(Ar, Ar[0][i], revL);

            //Nodes shared between origL and revL are members of a SCC - add them to a new list
            vector<Node*> curComps;
            for (unsigned j = 0; j < origL.size(); j++)
            {
                for (unsigned k = 0; k < revL.size(); k++)
                {
                    if (origL[j] == revL[k])
                    {
                        curComps.push_back(origL[j]);
                    }
                }
            }

            //Label each member, construct SCC
            //(In this section we also calculate the size of the SCC)
            SCCNode* currSCC = new SCCNode();
            currSCC->id = curComps[0]->id;
            currSCC->size = 0;
            for (unsigned r = 0; r < curComps.size(); r++)
            {
                curComps[r]->SCC = curComps[0]->id;
                currSCC->size += 1;
            }
            SCCs.push_back(currSCC);
        }
    }

    //Call DFSAssign to find inward and outward edges
    for (unsigned q = 1; q < A[0].size(); q++)
    {
        A[0][q]->visited = false;
    }
    for (unsigned i = 1; i < A[0].size(); i++)
    {
        if (A[0][i]->visited == false)
        {
            DFSAssign(A, A[0][i], A[0][i]->SCC, SCCs);
        }
    }
    //SCCs are all found and labeled
    return SCCs;
}

/************************************************************************************************
 * Given the adjacency list representation of a graph, print the number of nodes that belong to *
 * the three sets A, B, and C as described in assignment 1                                      *
 * A - vector<vector<Node*>> - an adjacency list                                                *
 * **********************************************************************************************/
void printSetSizes(vector<vector<Node*>> A)
{
    vector<SCCNode*> SCCs = SCC(A);

    int a = 0,
        b = 0,
        c = 0;
    for (auto C : SCCs)
    {
        //A
        if (C->hasOutEdges && !C->hasInEdges)
        {
            a += C->size;
        }
        //B
        else if (C->hasInEdges && !C->hasOutEdges)
        {
            b += C->size;
        }
        //C
        else
        {
            c += C->size;
        }
    }
    cout << a << " " << b << " " << c << endl;
}

int main()
{
    //get the number of nodes and number of edges from cin separated by a space
    int n = -1, m = -1;
    cin >> n >> m;

    //add the nodes to an adjacency list
    //note that A[0] is a list of nodes with a dummy node in A[0][0]
    //this means that A[i] is the node with id i where ids start at 1
    vector<vector<Node*>> A(n+1);
    A[0].push_back(new Node());
    for (int i=1; i<n+1; i++)
    {
        Node* v = new Node();
        v->id = i;
        v->SCC = -1;
        v->visited = false;
        A[0].push_back(v);
    }

    //get edges from cin and add them to the adjacency list
    //the start and end of a single edge are on the same line separated by a space
    int u = -1, v = -1;
    for (int i=0; i<m; i++)
    {
        cin >> u >> v;
        A[u].push_back(A[0][v]);
    }

    //call printSetSizes to determine the size of the sets A, B, and C and print the results
    printSetSizes(A);

    return 0;
}
