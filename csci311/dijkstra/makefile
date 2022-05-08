CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS = 

sspapp:sspapp.o graph.o minpriority.o
	$(CXX) $(LDFLAGS) graph.o minpriority.o sspapp.o -o sspapp
	rm *.o

minpriority.o: minpriority.cpp minpriority.h
	$(CXX) $(CXXFLAGS) minpriority.cpp

graph.o: graph.cpp graph.h minpriority.h
	$(CXX) $(CXXFLAGS) graph.cpp

sspapp.o: sspapp.cpp sspapp.h graph.h
	$(CXX) $(CXXFLAGS) sspapp.cpp

clean:
	rm *.o sspapp
