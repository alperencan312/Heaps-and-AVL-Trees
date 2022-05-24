#include "PriorityQueue.h"
/*
 * Title: Heaps, Priority Queues
 * Author: Alperen CAN 
 * ID: 21601740
 * Section: 1
 * Assignment: 3
 * Description: PriorityQueue implementation using heap
*/
PriorityQueue::PriorityQueue(const int size){
    h = Heap(size);
}

PriorityQueue::~PriorityQueue() {  
}

bool PriorityQueue::pqIsEmpty() const {
	return h.heapIsEmpty();
}

void PriorityQueue::pqInsert(const PQItemType& newItem) throw (PQException){
	try {
		h.heapInsert(newItem);
	}
	catch (HeapException e) {
		throw PQException("Priority queue is full");
	}
}

void PriorityQueue::pqDelete(PQItemType& priorityItem) throw (PQException) {
	try {
		h.heapDelete(priorityItem);
	}
	catch (HeapException e) {
		throw PQException("Priority queue is empty");
	}
}