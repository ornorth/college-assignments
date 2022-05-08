/**
 *  @file hash.cpp  Implement member functions of class Hash
 *
 *  @brief
 *      Implements all member functions of class Hash, as declared in  hash.h,
 *      with the exception of hf(string),
 *      the implementation of which can be found in hash_function.cpp
 *
 *  @author Owen North
 *  @date 10/7/20
 */

#include "hash.h"
#include <iostream>
#include <fstream>

using std::list;
using std::cout;

/**
 * Hash::avgListLength
 *
 *  @brief
 *      Returns the current average list length of the table
 *      Defined as the total number of items in the table
 *      Divided by the number of non-empty lists
 *
 *  @param  none
 *  @return double, average list length
 */
double Hash::avgListLength()
{
    double nonEmpty = 0;
    double numElements = 0;

    for (unsigned i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (!hashTable[i].empty())
        {
            nonEmpty += 1;
            numElements += hashTable[i].size();
        }
    }
    return numElements / nonEmpty;
}

/**
 *  Hash::loadFactor
 *
 *  @brief
 *      Returns the load factor of the hash table
 *      The load factor is equal to the number of keys
 *      Divided by the number of slots
 *
 *  @param  none
 *  @return double, the load factor
 */
double Hash::loadFactor()
{
    double numElements = 0;
    for (unsigned i = 0; i < HASH_TABLE_SIZE; i++)
    {
        numElements += hashTable[i].size();
    }
    return numElements / (double)HASH_TABLE_SIZE;
}



/**
 *  Hash constructor
 *  @param  none
 */
Hash::Hash()
{
    collisions = 0;
    longestList = 0;
    runningAvgListLength = 0;
}

/**
 *  Hash::remove
 *
 *  @brief
 *      Removes the given key from the hash table
 *      Updates running average list length
 *
 *  @param  key to be removed
 *  @return none
 */
void Hash::remove(string key)
{
    int i = hf(key);
    list<std::string>::iterator j;
    for (j = hashTable[i].begin(); j != hashTable[i].end(); j++)
    {
        if (*j == key)
        {
            break;
        }
    }
    if (j != hashTable[i].end())
    {
        hashTable[i].erase(j);

        //update runningAvgListLength
        runningAvgListLength = (avgListLength() + runningAvgListLength) / 2.0;
    }
}

/**
 *  Hash::print
 *
 *  @brief
 *      Displays the contents of the hash table
 *      Each index gets a newline
 *      Chained values are separated by comma
 *
 *  @param   none
 *  @return  none
 */
void Hash::print()
{
    for (unsigned i = 0; i < HASH_TABLE_SIZE; i++)
    {
        cout << i << ":\t";
        list<std::string>::iterator j;
        for (j = hashTable[i].begin(); j != hashTable[i].end(); j++)
        {
            cout << *j << ", ";
        }
        cout << std::endl;
    }
}


/**
 *  Hash::processFile
 *
 *  @brief
 *      Reads in data from a file and adds it to the hash table
 *      Assumes values are separated by a newline (\n)
 *      Also updates running statistics
 *
 *  @param   filename   Name of the file to be read
 *  @return  none
 */
void Hash::processFile(string filename)
{
    std::ifstream toRead(filename);
    string toInsert;
    while (std::getline(toRead, toInsert))
    {
        int i = hf(toInsert);
        //update stats
        if (!hashTable[i].empty())
        {
            hashTable[i].push_back(toInsert);

            //collisions
            collisions += 1;

            //longestList
            if (hashTable[i].size() > longestList)
            {
                longestList = hashTable[i].size();
            }
        }
        //no need to update stats
        else
        {
            hashTable[i].push_back(toInsert);
        }
        //update runningAvgListLength
        runningAvgListLength = (avgListLength()+runningAvgListLength)/2.0;
    }
}


/**
 *  Hash::search
 *
 *  @brief
 *      Searches for a key in the hash table
 *      Only returns whether the key was found or not
 *
 *  @param   key    the key to be searched
 *  @return  True is the key was found, False if not
 */
bool Hash::search(string key)
{
    int index = hf(key);
    bool keyFound = false;
    for (auto curr : hashTable[index])
    {
        if (curr == key)
        {
            keyFound = true;
        }
    }
    return keyFound;
}

/**
 *  Hash::output
 *
 *  @brief
 *      Writes the hash table to a file
 *      Format equivalent to Hash::print above
 *
 *  @param   filename   Name of the file to be written to
 *  @return  none
 */
void Hash::output(string filename)
{
    std::ofstream outputfile(filename);

    //print function but replace cout with outputfile
    for (unsigned i = 0; i < HASH_TABLE_SIZE; i++)
    {
        outputfile << i << ":\t";
        list<std::string>::iterator j;
        for (j = hashTable[i].begin(); j != hashTable[i].end(); j++)
        {
            outputfile << *j << ", ";
        }
        outputfile << "\n";
    }
}

/**
 *  Hash::printStats
 *
 *  @brief
 *      Prints the statistics of the hash table
 *      That have been tracked during program execution
 *
 *  @stat   collisions
 *          Number of collisions that occur during insert
 *          (This hash table solves collisions by chaining)
 *
 *  @stat   longestList
 *          The longest list ever generated by chaining
 *          May not be the current longest list
 *
 *  @stat   runningAvgListLength
 *          Tracks list length as a running average
 *          Updated after every successful insert and remove operation
 *
 *  @stat   loadFactor (not a member variable)
 *          calculates and prints the load factor for the table
 *
 *  @param  none
 *  @return none
 */
void Hash::printStats()
{
    //load factor = number of [entries?] / number of "buckets"
    //number of keys / number of slots
    //items/HASH_SIZE
    cout <<   "Total Collisions = "             << collisions
        << "\nLongest List Ever = "             << longestList
        << "\nAverage List Length Over Time = " << runningAvgListLength
        << "\nLoad Factor = "                   << loadFactor()
        << std::endl;
}
