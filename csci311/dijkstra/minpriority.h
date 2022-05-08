/**
 *  @file   minpriority.h
 *
 *  @brief  Declaration of class MinPriorityQueue
 *          And nested class Element
 *          Member function implementation can be found in minpriority.cpp
 *
 *  @author Owen North
 *  @date   10/19/2020
 */
#ifndef MIN_PRIORITY_H
#define MIN_PRIORITY_H

#include <iostream>
#include <vector>
#include <string>
using std::string;
using std::vector;

class MinPriorityQueue
{
    public:
        MinPriorityQueue() {};              
        ~MinPriorityQueue();                
        void insert(const string &, int);   
        void decreaseKey(string, int);
        string extractMin();

        //Added for use in Dijkstra's algorithm
        bool isEmpty() { return (minHeap.size() == 0); }

    private:
        class Element
        {
            public:
                string *id; //the element's ID
                int key;    //the priority key - lower value is higher priority

                Element() {};                         //Constructor
                Element(const string &hid, int hkey)  //Overloaded Constructor
                  : id(new string(hid)) , key(hkey)
                  {};
                ~Element() { delete id; };            //Destructor
        };
        
    private:
        void buildMinHeap();
        void minHeapify(int);
        int parent(int);
        int left(int);
        int right(int);

    private:
        vector<Element*> minHeap;   //Vector implementation of a min heap
};

#endif
