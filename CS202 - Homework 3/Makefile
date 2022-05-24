simulator: Heap.o PriorityQueue.o main.o
	g++ -o simulator Heap.o PriorityQueue.o main.o -std=c++11
main.o: main.cpp PriorityQueue.h
	g++ -c main.cpp -std=c++11
PriorityQueue.o: PriorityQueue.cpp PriorityQueue.h Heap.h PQException.h
	g++ -c PriorityQueue.cpp -std=c++11
Heap.o: Heap.cpp Heap.h KeyedItem.h
	g++ -c Heap.cpp -std=c++11
clean:
	rm Heap.o PriorityQueue.o main.o simulator