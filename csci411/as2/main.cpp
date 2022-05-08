// CSCI 411 - Spring 2021
// Assignment 2 Skeleton
// Author: Carter Tillquist
// Feel free to use all, part, or none of this code for the coding problem on assignment 2.

#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm>
using namespace std;

/******************************************************************************
 * A simple Node struct                                                       *
 * id - int - the id or name of the node                                      *
 * dist - int - the distance from some given node to this node                *
 * inI - bool - true if the node is a member of the set I and false otherwise *
 * visited - bool - whether or not this node has been visited                 *
 * ****************************************************************************/
struct Node {
    int id;
    int dist;
    bool inI;
    bool visited;
};

/**************************************************************************
 * A simple Edge struct                                                   *
 * from - Node* - the node where this edge starts                         *
 * to - Node* - the node where this edge ends                             *
 * weight - int - the weight of this edge                                 *
 * ************************************************************************/
struct Edge {
    Node* from;
    Node* to;
    int weight;
};

/************************************************************************
 * Searches a vector of integers for a specific integer                 *
 * I - the vector to be searched                                        *
 * i - the integer to be found                                          *
 * return - true if i is found. false if not                            *
 * **********************************************************************/
bool contains(vector<int> I, int i)
{
    for (unsigned j = 0; j < I.size(); j++)
    {
        if (I[j] == i) return true;
    }
    return false;
}

/*****************************************************************************************************************
 * Given a graph, find the set of nodes that belong to the set I, that is, the set of vertices v such that there *
 * is at least one path of length negative infinity ending at v.                                                 *
 * A - vector<vector<Edge*>> - an adjacency list representation of a graph where each element is a weighted edge *
 * return - vector<int> - the integer ids of nodes in the set I                                                  *
 * ***************************************************************************************************************/
vector<int> findSetI(vector<vector<Edge*>> A)
{
    //Count number of edges for use in Bellman-Ford [ITERATIONS]
    unsigned numEdges = 0;
    for (unsigned q = 1; q < A.size(); q++)
    {
        numEdges += A[q].size();
    }

    vector<int> I;
    Node* s;

    //Repeat the algorithm for each node in A
    for (unsigned i = 1; i < A[0].size(); i++)
    {
        //Set starting distances to infinity
        for (unsigned q = 1; q < A[0].size(); q++)
        {
            A[0][q]->to->dist = INT_MAX;
        }
        s = A[0][i]->to;
        s->dist = 0;

        //Loop a number of times equal to the number of edges
        for (unsigned j = 0; j < numEdges; j++)
        {
            //for (u, v) in E
            for (unsigned u = 1; u < A.size(); u++)
            {
                for (unsigned v = 0; v < A[u].size(); v++)
                {
                    //Relax edge
                    if (A[u][v]->to->dist > A[u][v]->from->dist + A[u][v]->weight)
                    {
                        A[u][v]->to->dist = A[u][v]->from->dist + A[u][v]->weight;
                    }
                }
            }
        }
        //Loop once more, any smaller paths found belong to a negative cycle
        for (unsigned u = 1; u < A.size(); u++)
        {
            for (unsigned v = 0; v < A[u].size(); v++)
            {
                if (A[u][v]->to->dist > A[u][v]->from->dist + A[u][v]->weight)
                {
                    I.push_back(A[u][v]->to->id);
                    I.push_back(A[u][v]->from->id);
                }
            }
        }
    }

    //Remove duplicates from I
    sort(I.begin(), I.end());
    for (unsigned i = 1; i < I.size(); i++)
    {
        if (I[i-1] == I[i])
        {
            I.erase(I.begin()+i);
            i = 0;
        }
    }

    //Add every node visible to nodes already in I
    for (unsigned i = 0; i < I.size(); i++)
    {
        for (unsigned j = 0; j < A[I[i]].size(); j++)
        {
            s = A[I[i]][j]->to;
            if (!contains(I, s->id))
            {
                I.push_back(s->id);
            }
        }
    }
    return I;
}

int main()
{
    //get the number of nodes and number of edges from cin separated by a space
    int n = -1, m = -1;
    cin >> n >> m;

    //add the nodes to an adjacency list
    //in this case, A[i] is a vector of all edges leaving A[i]
    //note that A[0] is a list of self loops representing all nodes in the graph
    //these are not actual edges in the graph, just a way to keep track of all nodes
    //Furthermore, A[0][0] is a dummy edge with a dummy node
    //this means that A[i] is the node with id i where ids start at 1
    vector<vector<Edge*>> A(n+1);
    A[0].push_back(new Edge());
    for (int i=1; i<n+1; i++){
        Node* v = new Node();
        v->id = i;
        v->dist = INT_MAX;
        v->inI = false;
        v->visited = false;
        Edge* e = new Edge();
        e->from = v;
        e->to = v;
        e->weight = 0;
        A[0].push_back(e);
    }
    //get edges from cin and add them to the adjacency list
    //the start, end, and weight of a single edge are on the same line separated by spaces
    int u = -1, v = -1, w = -1;
    for (int i=0; i<m; i++){
        cin >> u >> v >> w;
        Edge* e = new Edge();
        e->from = A[0][u]->from;
        e->to = A[0][v]->to;
        e->weight = w;
        A[u].push_back(e);
    }

    //find nodes belonging to the set I and print them out in ascending order
    vector<int> I = findSetI(A);
    sort(I.begin(), I.end());
    for (int i=0; i<(int)I.size()-1; i++){
        cout << I[i] << " ";
    }
    if (I.size() > 1){ cout << I[I.size()-1] << endl; }

    return 0;
}












