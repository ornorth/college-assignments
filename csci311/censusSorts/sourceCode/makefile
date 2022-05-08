CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS =

PROG = csort

$(PROG) : CensusSort.o CensusData.o CensusDataSorts.o
	$(CXX) $(LDFLAGS) CensusSort.o CensusData.o CensusDataSorts.o -o $(PROG)
	rm *o

CensusSort.o : CensusSort.cpp CensusData.h
	$(CXX) $(CXXFLAGS) CensusSort.cpp

CensusData.o : CensusData.cpp CensusData.h
	$(CXX) $(CXXFLAGS) CensusData.cpp

CensusDataSorts.o : CensusDataSorts.cpp CensusData.h
	$(CXX) $(CXXFLAGS) CensusDataSorts.cpp

clean :
	rm -f core $(PROG) *.o
