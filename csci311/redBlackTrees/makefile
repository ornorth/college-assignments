CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic

rbapp: rbapp.o rbtree.o
	$(CXX) -o rbapp rbapp.o rbtree.o
	rm *.o

rbapp.o: rbapp.cpp rbapp.h rbtree.h

rbtree.o: rbtree.cpp rbtree.h

clean:
	rm -f *.o rbapp
