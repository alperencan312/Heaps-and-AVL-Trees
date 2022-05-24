#include "KeyedItem.h" // definition of KeyedItem
#include "HeapException.h" 
typedef KeyedItem HeapItemType;
/*
 * Title: Heaps, Priority Queues
 * Author: Alperen CAN 
 * ID: 21601740
 * Section: 1
 * Assignment: 3
 * Description: Heap header file
*/
class Heap {
public:
	Heap();
    Heap(const int maxSize) throw(HeapException);
    ~Heap();
	bool heapIsEmpty() const;
	void heapInsert(const HeapItemType& newItem) throw(HeapException);
	void heapDelete(HeapItemType& rootItem) throw(HeapException);
    bool comparePriority(HeapItemType heapItem1, HeapItemType heapItem2);

protected:
	void heapRebuild(int root);		
private:
	HeapItemType *items;	        // array of heap items
	int          size;            	// number of heap items
    int          maxSize;            	
};