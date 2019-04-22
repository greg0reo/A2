all: BestFirstSearch

BestFirstSearch: BestFirstSearch.o
	g++ BestFirstSearch.o -o BestFirstSearch

BestFirstSearch.o: BestFirstSearch.cpp
	g++ -g -c BestFirstSearch.cpp

clean:
	rm -f *.o

