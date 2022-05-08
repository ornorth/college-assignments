/**
 *  @file   minpriority.cpp
 *
 *  @brief  implementation of class MinPriorityQueue,
 *          the declaration of which can be found in minpriority.h
 *
 *  @author Owen North
 *  @date   10/19/2020
 */
#include "minpriority.h"

/**
 *  MinPriorityQueue Destructor
 *
 *  @brief  minHeap is a vector containing pointers to Element items
 *          those must be deleted before the vector is deallocated from memory
 */
MinPriorityQueue::~MinPriorityQueue()
{
    for (auto a : minHeap)
    {
        delete a;
    }
}

/**
 *  MinPriorityQueue::insert
 *
 *  @brief  adds a new element to the min heap
 *          the element is inserted at the end of the min heap,
 *          then a call to minPriorityQueue::decreaseKey() is made
 *          to preserve the min heap property
 *
 *  @param  id  The element's id
 *          key The key that determines the element's place in the queue
 *
 *  @return none
 */
void MinPriorityQueue::insert(const string &id, int key)
{
    Element *newEl = new Element(id, key);
    minHeap.push_back(newEl);
    decreaseKey(id, key);
}

/**
 *  MinPriorityQueue::decreaseKey
 *
 *  @brief  lowers the key value of an element in the queue,
 *          thereby increasing its place in the queue
 *
 *          the algorithm first performs a search to find the element,
 *          then updates the key and iterates up the tree,
 *          swapping elements to ensure the min heap property is preserved
 *
 *  @param  id      The id of the element to be updated
 *          newKey  The new key value
 *  
 *  @return none
 */
void MinPriorityQueue::decreaseKey(string id, int newKey)
{
    //find id
    unsigned i;
    for (i = 0; i < minHeap.size(); i++)
    {
        if (*minHeap[i]->id == id) break;
    }

    //update minHeap
    if (newKey > minHeap[i]->key) return;
    minHeap[i]->key = newKey;
    while (i > 0 && minHeap[parent(i)]->key > minHeap[i]->key)
    {
        Element *tmp = minHeap[parent(i)];
        minHeap[parent(i)] = minHeap[i];
        minHeap[i] = tmp;
        i = parent(i);
    }
}

/**
 *  MinPriorityQueue::extractMin
 *
 *  @brief  returns and removes the element with the smallest key,
 *          which will be the root of the min heap
 *          minHeapify() is then called to rebuild the min heap
 *
 *  @param  none
 *
 *  @return the id of the element that was extracted
 */
string MinPriorityQueue::extractMin()
{
    if (minHeap.size() < 1) return "empty";

    Element *min = minHeap[0];
    minHeap[0] = minHeap[minHeap.size()-1];
    minHeap.pop_back();
    minHeapify(0);

    string id = *min->id;
    delete min;
    return id;
}

/**
 *  MinPriorityQueue::buildMinHeap()
 *
 *  @brief  builds a min heap out of vector minHeap
 *          by calling minHeapify() on all non-leaf nodes
 *
 *  @param  none
 *  
 *  @return none
 */
void MinPriorityQueue::buildMinHeap()
{
    for (int i = (minHeap.size()-1)/2; i >= 0; i--)
    {
        minHeapify(i);
    }
}

/**
 *  MinPriorityQueue::minHeapify
 *
 *  @brief  preserves the min heap property at node i
 *          algorithm assumes that the subtrees of i are both min heaps
 *          
 *          if either child of i is smaller than its parent,
 *          that child is swapped with i
 *          and minHeapify is recursively called on that subtree
 *
 *  @param  i   index of the subtree to be min heapified
 *
 *  @return none
 */
void MinPriorityQueue::minHeapify(int i)
{
    int smallest;
    int l = left(i);
    int r= right(i);
    int end = minHeap.size()-1;
    
    //find smallest key
    if (l <= end && minHeap[l]->key < minHeap[i]->key)
    {
        smallest = l;
    }
    else smallest = i;

    if (r <= end && minHeap[r]->key < minHeap[smallest]->key)
    {
        smallest = r;
    }

    //swap and recurse if necessary
    if (smallest != i)
    {
        Element *tmp = minHeap[i];
        minHeap[i] = minHeap[smallest];
        minHeap[smallest] = tmp;

        minHeapify(smallest);
    }

}

/**
 *  MinPriorityQueue::parent
 *
 *  @brief  returns the index of a given node's parent
 *
 *  @param  i   the index of the node
 *  @return the index of the node's parent
 */
int MinPriorityQueue::parent(int i)
{
    return (i-1)/2;
}

/**
 *  MinPriorityQueue::left
 *
 *  @brief  returns the index of a given node's left child
 *
 *  @param  i   the index of the node
 *  @return the index of the node's left child
 */
int MinPriorityQueue::left(int i)
{
    return (2*i) + 1;
}

/**
 *  MinPriorityQueue::right
 *
 *  @brief  returns the index of a given node's right child
 *
 *  @param  i   the index of the node
 *  @return the index of the node's right child
 */
int MinPriorityQueue::right(int i)
{
    return (2*i) + 2;
}
