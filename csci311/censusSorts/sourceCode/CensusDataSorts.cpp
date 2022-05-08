/**
 * @file CensusDataSorts.cpp   Sort functions for census population data.
 * 
 * @brief
 *    Implements several different types of sorts. Data can be sorted
 * by population or by name of town. This file contains all of the sorting
 * functions and their helpers.
 *
 * @author Judy Challinger, Owen North
 * @date 9/16/20
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "CensusData.h"

/**isSmaller()
 *
 * Helper function that uses either population or city
 * to determine which value, left or right, is the smaller
 * using C++ built-in < operator
 *
 *  @param  type, integer representing either city or population
 *          left, the left side of the < operation
 *          right, the right side of the < operation
 *
 *  @return True if left is smaller, false if not
 *          (returns false if they are equal)
**/
bool CensusData::isSmaller(int type, Record* left, Record* right)
{
        return (type == 0? 
                left->population < right->population :
                *left->city < *right->city);
}

/** recurseMergeSort()
 * 
 * Private implementation of public function mergeSort()
 * Which makes an immediate call here
 *
 *  @param  "type"  determines value to be sorted by
 *          "p"     the lower bound of the subarray to be partitioned
 *          "r"     the upper bound of the subarray to be partitioned
 *
 *  @return void
 *
**/
void CensusData::recurseMergeSort(int type, int p, int r)
{
        //Base Case
        if (p < r)
        {
                /*
                 * RECURSIVE CALLS
                 */
                //Find middle
                int q = floor((p+r)/2);
                //Recurse on left half
                recurseMergeSort(type, p, q);
                //Recurse on right half
                recurseMergeSort(type, q+1, r);
                /*
                 * RECURSION RETURNS 2 SORTED SUBARRAYS
                 * NOW WE DECLARE THOSE ARRAYS
                 * AND WRITE THEM TO THE ORIGINAL ARRAY
                */
                vector<Record*> left;  //left sorted subarray
                vector<Record*> right; //right sorted subarray
                int i                  //iterator for left
                  , j;                 //iterator for right

                //Populate left array
                for (i = 1; i <= q-p+1; i++)
                {
                        left.push_back(data.at(p+i-2));
                }
                //Populate right array
                for (j = 1; j <= r-q; j++)
                {
                        right.push_back(data.at(q+j-1));
                }

                //Write to original array
                i = j = 0;
                for (int k = p; k <= r; k++)
                {
                        //Both left and right arrays still have elements
                        if (i < (int)left.size() && j < (int)right.size())
                        {
                                //Value in left is smaller
                                if (isSmaller(type, left.at(i), right.at(j)))
                                {
                                        data.at(k-1) = left.at(i++);
                                }
                                //Value in right is smaller
                                else
                                {
                                        data.at(k-1) = right.at(j++);
                                }
                        }
                        else
                        {
                                //Left array is empty, write from right
                                if (i >= (int)left.size())
                                {
                                        data.at(k-1) = right.at(j++);
                                }
                                //Right array is empty, write from left
                                else if (j >= (int)right.size())
                                {
                                        data.at(k-1) = left.at(i++);
                                }
                        }
                }
        }
}
/** recurseQuickSort()
 * 
 * Private implementation of public function quickSort()
 * Which seeds a random number generator then calls this fucntion
 *
 *  @param  "type"      determines value to be sorted by
 *          "p"         the lower bound of the subarray to be partitioned
 *          "r"         the upper bound of the subarray to be partitioned
 *          "generator" the random number generator used to determine the pivot
 *
 *  @return void
 *
**/
void CensusData::recurseQuickSort(int type, int p, int r,
                                  std::default_random_engine generator)
{
        if (p < r)
        {
                //PARTITION - not a nested function in this implementation
                //Randomly choose pivot
                std::uniform_int_distribution<int> distribution(p,r);
                int pivot = distribution(generator);
                //i and j represent subarrays that are < and > than pivot
                int i = p-1;
                for (int j = p; j <= r; j++)
                {
                        //Found value < pivot, move to "i" subarray
                        if (isSmaller(type, data.at(j), data.at(pivot)))
                        {
                                Record* tmp = data.at(++i);
                                data.at(i) = data.at(j);
                                data.at(j) = tmp;
                                //Ensure pivot still points to the right value
                                if (i == pivot)
                                {
                                        pivot = j;
                                }
                        }
                }
                //Place pivot in its final location
                Record* tmp = data.at(i+1);
                data.at(i+1) = data.at(pivot);
                data.at(pivot) = tmp;


                //Recurse on left and right sides of pivot
                recurseQuickSort(type, p, i, generator);
                recurseQuickSort(type, i+2, r, generator);
        }
}

/** insertionSort()
 *
 * Sorts census data by either city name or population
 * Using the insertion sort method
 *
 * @param   integer equal to 0 or 1 that determines which value to sort by
 *          0 for population, 1 for name
 *
 * @return void
 *
**/
void CensusData::insertionSort(int type)
{
        //Take j to be the element to the right of the sorted subarray
        for (int j = 1; j < this->getSize(); j++)
        {
                //Take the value at j at the item to be inserted
                Record* key = data[j];
                int i = j-1;
                //Shift to the right each value in the sorted subarray > key
                while (i >= 0 && isSmaller(type, key, data[i]))
                {
                        data[i+1] = data[i];
                        i--;
                }
                //At the point where key is no longer <, insert key
                data[i+1] = key;
        }
}

/** mergeSort()
 *
 * Sorts census data by either city name or population
 * Using the merge sort method
 *
 * @param   integer equal to 0 or 1 that determines which value to sort by
 *          0 for population, 1 for name
 *
 * @return void
 *
**/
void CensusData::mergeSort(int type)
{
        recurseMergeSort(type, 1, this->getSize());
}

/** quickSort()
 *
 * Sorts census data by either city name or population
 * Using the quick sort method
 *
 * @param   integer equal to 0 or 1 that determines which value to sort by
 *          0 for population, 1 for name
 *
 * @return void
 *
**/
void CensusData::quickSort(int type)
{
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator (seed);
        recurseQuickSort(type, 0, this->getSize()-1, generator);
}
