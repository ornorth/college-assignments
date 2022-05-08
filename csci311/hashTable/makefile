CXX = g++
SIZE=4000
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic -D HASH_TABLE_SIZE=$(SIZE)
LDFLAGS = 

hash5: hash.o hash_function.o main.o
	$(CXX) $^ -o $@ $(LDFLAGS)
	rm *.o

main.o: main.cpp hash.h
	$(CXX) $(CXXFLAGS) -c $<

hash.o: hash.cpp hash.h 
	$(CXX) $(CXXFLAGS) -c $<

hash_function.o: hash_function.cpp hash.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o hash5
