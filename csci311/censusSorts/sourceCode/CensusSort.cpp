/**
 * @file CensusSort.cpp   Sorts census population data.
 *
 * @brief
 *    Implementation of sorting for population data. Several different types
 * of sorts are supported. This file contains driver and timing functions.
 *
 * @author Judy Challinger
 * @date 9/10/15
 */

#include <fstream>
#include <iostream>
#include <chrono>
#include "CensusData.h"

/**
 * printTime
 *
 * Prints a line of output with the timing information to sort
 * a given number of Records.
 *
 * @param records The number of Records that were sorted.
 * @param start   The starting time.
 * @param end     The ending time.
 */

void printTime(int records,
               std::chrono::steady_clock::time_point start,
               std::chrono::steady_clock::time_point end) {
   std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>> (end - start);
   std::cout << "CPU time: " << time_span.count()
      << " seconds on " << records << " records" << std::endl;
}

/**
 * runInsertionSorts
 *
 * Creates a CensusData object and initializes it from the census
 * data file. Runs two sorts - one by population and one by city name - using
 * insertion sort.
 *
 * @param fp   File pointer to the census data file.
 */
void runInsertionSorts(ifstream& fp) {
   CensusData myCensusData;
   std::chrono::steady_clock::time_point startTime;
   std::chrono::steady_clock::time_point endTime;

   std::cout << std::endl << "**********INSERTION SORT**********" << std::endl;
   myCensusData.initialize(fp);
   std::cout << std::endl << "Original Data" << std::endl;
   myCensusData.print();

   startTime = std::chrono::steady_clock::now();
   myCensusData.insertionSort(myCensusData.POPULATION);
   endTime = std::chrono::steady_clock::now();
   std::cout  << std::endl << "Sorted by POPULATION" << std::endl;
   printTime(myCensusData.getSize(), startTime, endTime);
   myCensusData.print();

   startTime = std::chrono::steady_clock::now();
   myCensusData.insertionSort(myCensusData.NAME);
   endTime = std::chrono::steady_clock::now();
   std::cout << std::endl << "Sorted by NAME" << std::endl;
   printTime(myCensusData.getSize(), startTime, endTime);
   myCensusData.print();
}

/**
 * runMergeSorts
 *
 * Creates a CensusData object and initializes it from the census
 * data file. Runs two sorts - one by population and one by city name - using
 * merge sort.
 *
 * @param fp   File pointer to the census data file.
 */
void runMergeSorts(ifstream& fp) {
   CensusData myCensusData;
   std::chrono::steady_clock::time_point startTime;
   std::chrono::steady_clock::time_point endTime;

   std::cout << std::endl << "**********MERGE SORT**********" << std::endl;
   myCensusData.initialize(fp);
   std::cout << std::endl << "Original Data" << std::endl;
   myCensusData.print();

   startTime = std::chrono::steady_clock::now();
   myCensusData.mergeSort(myCensusData.POPULATION);
   endTime = std::chrono::steady_clock::now();
   std::cout  << std::endl << "Sorted by POPULATION" << std::endl;
   printTime(myCensusData.getSize(), startTime, endTime);
   myCensusData.print();

   startTime = std::chrono::steady_clock::now();
   myCensusData.mergeSort(myCensusData.NAME);
   endTime = std::chrono::steady_clock::now();
   std::cout << std::endl << "Sorted by NAME" << std::endl;
   printTime(myCensusData.getSize(), startTime, endTime);
   myCensusData.print();
}

/**
 * runQuickSorts
 *
 * Creates a CensusData object and initializes it from the census
 * data file. Runs two sorts - one by population and one by city name - using
 * quicksort.
 *
 * @param fp   File pointer to the census data file.
 */
void runQuickSorts(ifstream& fp) {
   CensusData myCensusData;
   std::chrono::steady_clock::time_point startTime;
   std::chrono::steady_clock::time_point endTime;

   std::cout << std::endl << "**********QUICK SORT**********" << std::endl;
   myCensusData.initialize(fp);
   std::cout << std::endl << "Original Data" << std::endl;
   myCensusData.print();

   startTime = std::chrono::steady_clock::now();
   myCensusData.quickSort(myCensusData.POPULATION);
   endTime = std::chrono::steady_clock::now();
   std::cout  << std::endl << "Sorted by POPULATION" << std::endl;
   printTime(myCensusData.getSize(), startTime, endTime);
   myCensusData.print();

   startTime = std::chrono::steady_clock::now();
   myCensusData.quickSort(myCensusData.NAME);
   endTime = std::chrono::steady_clock::now();
   std::cout << std::endl << "Sorted by NAME" << std::endl;
   printTime(myCensusData.getSize(), startTime, endTime);
   myCensusData.print();
}

/**
 * The main entry point and driver for the program. The program expects the
 * file name of a csv file to be entered on the command line. Output goes to
 * stdout - use redirection to capture it in a file.
 */
int main(int argc, char *argv[])
{
   if ( argc != 2 ) {
      std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
      return 0;
   }

   ifstream fp;
   fp.open(argv[1], std::ios::in);
   if (!fp.is_open()) {
      std::cout << "can't open file " << argv[1] << std::endl;
      return 0;
   }

   runInsertionSorts(fp);

   runMergeSorts(fp);

   runQuickSorts(fp);

   fp.close();
   return 0;
}

