#include "graph.h"
#include <algorithm>
#include <climits>

using std::string;
using std::vector;
using std::sort;

void Graph::addVertex(string name)
{
    Vertex v;
    v.pi = "";
    v.key = INT_MAX;
    vertices[name] = v;
}

void Graph::addEdge(string from, string to, int weight)
{
    Neighbor n;
    n.name = to;
    n.weight = weight;
    adjList[from].push_back(n);
    sort(adjList[from].begin(), adjList[from].end());
}

string Graph::getShortestPath(string from, string to)
{
    //If path to self is requested, solution is already known
    if (from == to)
    {
        return (to + "->" + to + " with length 0");
    }

    string solution, tracer;
    //current SSP tree is not applicable, build new one
    if (currentSource != from)
    {
        currentSource = from;
        buildSSPTree(from);
    }

    //track "pi" from destination to source, building string along the way
    solution = to;
    tracer = vertices[to].pi;
    while (tracer != from)
    {
        solution = tracer + "->" + solution;
        tracer = vertices[tracer].pi;
    }
    
    //Add source to path
    solution = tracer + "->" + solution;
    //Add length portion of answer
    solution += " with length " + std::to_string(vertices[to].key);
    return solution;
}

void Graph::buildSSPTree(string source)
{
    string u;

    //Reinitialize vertices
    std::map<string, Vertex>::iterator a;
    for (a = vertices.begin(); a != vertices.end(); a++)
    {
        a->second.pi = "";
        a->second.key = INT_MAX;
        minQ.insert(a->first, a->second.key);
    }
    vertices[source].key = 0;
    minQ.decreaseKey(source, 0);

    while (!minQ.isEmpty())
    {
        u = minQ.extractMin();
        for (unsigned i = 0; i < adjList[u].size(); ++i)
        {
            relax(u, adjList[u].at(i).name, adjList[u].at(i).weight);
        }
    }
}

void Graph::relax(string u, string v, int weight)
{
    if (vertices[v].key > (vertices[u].key + weight))
    {
        vertices[v].key = vertices[u].key + weight;
        minQ.decreaseKey(v, vertices[u].key + weight);
        vertices[v].pi = u;
    }
}
