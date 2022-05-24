/*
 * Title: Heaps, Priority Queues
 * Author: Alperen CAN 
 * ID: 21601740
 * Section: 1
 * Assignment: 3
 * Description: Keyed Item (Request)
*/

class KeyedItem { 	
public:
	KeyedItem() { }
	KeyedItem(const int id, const int priority, const int requestTime, const int processTime) 
            : id(id), priority(priority), requestTime(requestTime), processTime(processTime){}

    int getId() const { 
        return id;
    }

    int getPriority() const { 
        return priority;
    }

    int getRequestTime() const { 
        return requestTime;
    }

    int getProcessTime() const { 
        return processTime;
    }

private:
    int id;
    int priority; 	
    int requestTime;	
    int processTime;

};