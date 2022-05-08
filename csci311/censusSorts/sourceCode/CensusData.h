/**
 * @file CensusData.h   Declaration of the CensusData class.
 *
 * @author Judy Challinger, Owen North
 * @date 9/28/20
 */

#ifndef CSCI_311_CENSUSDATA_H
#define CSCI_311_CENSUSDATA_H

#include <vector>
#include <chrono>
#include <random>
using std::ifstream;
using std::string;
using std::vector;

class CensusData {
public:
   static const int POPULATION = 0;       // type of sort
   static const int NAME = 1;
   ~CensusData();
   void initialize(ifstream&);            // reads in data
   int getSize(){return data.size();}
   void print();                          // prints out data
   void insertionSort(int);               // sorts data using insertionSort
   void mergeSort(int);                   // sorts data using mergeSort
   void quickSort(int);                   // sorts data using quickSort
private:
   class Record {                         // declaration of a Record
   public:
      string* city;
      string* state;
      int population;
      Record(string&, string&, int);
      ~Record();
   };
   vector<Record*> data;                  // data storage
//
// You may add your private helper functions here!
//
   //Private call to merge sort - algorithm contained here
   void recurseMergeSort(int, int, int);
   //Private call to quick sort - member function seeds RNG, passes here
   void recurseQuickSort(int, int, int, std::default_random_engine);
   //To allow sorts by population and name
   bool isSmaller(int, Record*, Record*);
};

#endif // CSCI_311_CENSUSDATA_H
