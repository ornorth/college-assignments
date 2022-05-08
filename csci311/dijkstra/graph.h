/**
 *  @file graph.h   an application that simulates a weighted, directed graph,
 *                  accepts queries for shortest paths,
 *                  and prints the shortest path to stdout
 *
 *  @author Owen North
 *  @date   11/23/2020
 */
#ifndef GRAPH_H
#define GRAPH_H
#include "minpriority.h"
#include <map>
#include <string>
#include <limits.h>

using std::string;

class Graph
{
    public:
        //Graph();
        //~Graph();
        void addVertex(string name);
        void addEdge(string from, string to, int weight);
        string getShortestPath(string from, string to);

    private:
        struct Vertex
        {
            string pi;
            int key;
        };
        struct Neighbor
        {
            string name;
            int weight;
            bool operator<(const Neighbor& n) const { return name < n.name; }
        };
        string currentSource;
        std::map<string, Vertex> vertices;
        std::map<string, vector<Neighbor>> adjList;
        MinPriorityQueue minQ;
        
        void buildSSPTree(string source);
        void relax(string u, string v, int weight);
};



#endif
