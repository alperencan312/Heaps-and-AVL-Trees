#include "Heap.h"// ADT heap operations
#include "PQException.h"
typedef HeapItemType PQItemType;
/*
 * Title: Heaps, Priority Queues
 * Author: Alperen CAN 
 * ID: 21601740
 * Section: 1
 * Assignment: 3
 * Description: PriorityQueue header file
*/
class PriorityQueue {
public:
	// default constructor, copy constructor, and destructor 
	// are supplied by the compiler
    PriorityQueue(const int size);
    ~PriorityQueue();
	// priority-queue operations:
	bool pqIsEmpty() const;
	void pqInsert(const PQItemType& newItem) throw (PQException);
	void pqDelete(PQItemType& priorityItem) throw (PQException);

private:
	Heap h;
};