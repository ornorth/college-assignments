CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS = 

queue: minpriority.o main.o
	$(CXX) $^ -o $@ $(LDFLAGS)
	rm *.o

main.o: main.cpp minpriority.h
	$(CXX) $(CXXFLAGS) -c $<

minpriority.o: minpriority.cpp minpriority.h 
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o queue
