/* This assignment originated at UC Riverside */

#include "hash.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setprecision;

int
main ( ) {

  Hash hashTable;
  cout << setprecision ( 10 );
  /*cout << "Test 1 - print empty table" << endl;
  hashTable.print ( );
  cout << "-------------------------------------------------------------"
       << endl;
  cout << "Test 2 - processing input file" << endl;
  */hashTable.processFile ( "dict5.txt" );
  hashTable.print ( );
  /*cout << "-------------------------------------------------------------"
       << endl;
  cout << "Test 3 - searching" << endl;
  if ( hashTable.search ( "heath" ) ) 
    cout << "Passed - searching for valid item" << endl;
  else
    cout << "FAILED - searching for valid item" << endl;

  if ( hashTable.search ( "hello" ) ) 
    cout << "Passed - searching for valid item" << endl;
  else
    cout << "FAILED - searching for valid item" << endl;

  if ( hashTable.search ( "ttttt" ) ) 
    cout << "Passed - searching for valid item" << endl;
  else
    cout << "FAILED - searching for valid item" << endl;

  if ( hashTable.search ( "empty" ) ) 
    cout << "FAILED - searching for invalid item" << endl;
  else
    cout << "Passed - searching for invalid item" << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  cout << "Test 4 - testing remove" << endl;
  hashTable.remove ( "happy" );
  hashTable.print ( );
  cout << endl;
  hashTable.remove ( "hello" );
  hashTable.remove ( "harps" );
  hashTable.print ( );
  cout << endl;
  hashTable.remove ( "heath" );
  hashTable.remove ( "heath" );
  hashTable.remove ( "heath" );
  hashTable.print ( );
  cout << endl;
  hashTable.remove ( "rrrrr" );
  hashTable.remove ( "ooooo" );
  hashTable.print ( );
  cout << "-------------------------------------------------------------"
       << endl;
  cout << "Test 5 - output to file" << endl;
  hashTable.output ( "hash.out" );
  cout << endl << endl;
  cout << "-------------------------------------------------------------"
       << endl;
  cout << "Test 6 - Stats" << endl;
  */hashTable.printStats ( );
  //cout << "-------------------------------------------------------------"
  //     << endl;
  return 1;
}
