#include "Heap.h"
/*
 * Title: Heaps, Priority Queues
 * Author: Alperen CAN 
 * ID: 21601740
 * Section: 1
 * Assignment: 3
 * Description: heap implementation customized for request heap
*/

// Default constructor 
Heap::Heap() : size(0) {
    items = NULL;
}

// Constructor wit max size 
Heap::Heap(const int maxSize) throw(HeapException){
    this -> maxSize = maxSize;
    this -> size = 0;
	items = new HeapItemType[maxSize];
    if (items == NULL) {
        throw HeapException("Heap memory cannot be allocated for this size.");
    }
}

Heap::~Heap() {  
    items = NULL;
}

bool Heap::heapIsEmpty() const{
	return (size == 0);
}

/**
 * item with higher priority is prior  
 * item with smaller request time is prior when priorities are equal
 */
bool Heap::comparePriority(HeapItemType heapItem1, HeapItemType heapItem2){
	return heapItem1.getPriority() > heapItem2.getPriority() || 
            (heapItem1.getPriority() == heapItem2.getPriority() 
                && heapItem1.getRequestTime() < heapItem2.getRequestTime());
}

void Heap::heapInsert(const HeapItemType &newItem) throw(HeapException) {

	// Place the new item at the end of the heap
	items[size] = newItem;

	// Trickle new item up to its proper position
	int place = size;
	int parent = (place - 1)/2;
	while ((place > 0) && (comparePriority(items[place], items[parent]))){
		HeapItemType temp = items[parent];
		items[parent] = items[place];
		items[place] = temp;
		place = parent;
		parent = (place - 1)/2;
	}
 	++size;
}


void Heap::heapDelete(HeapItemType &rootItem) throw(HeapException) {
	if (heapIsEmpty())
		throw HeapException("HeapException: Heap empty");
	else {
		rootItem = items[0];
		items[0] = items[--size];
		heapRebuild(0);
	}
}


void Heap::heapRebuild(int root) {   
	int child = 2 * root + 1; 	// index of root's left child, if any
	if ( child < size ) {		
		// root is not a leaf so that it has a left child
		int rightChild = child + 1; 	// index of a right child, if any
		// If root has right child, find larger child
		if ( (rightChild < size) &&
		     (comparePriority(items[rightChild], items[child])) )
			child = rightChild; 	// index of larger child

		// If root’s item has smaller priority than larger child, swap values
		if (comparePriority(items[child], items[root])) {
			HeapItemType temp = items[root];
			items[root] = items[child];
			items[child] = temp;

			// transform the new subtree into a heap
			heapRebuild(child);
		}
    }
}