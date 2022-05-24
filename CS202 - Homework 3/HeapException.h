#include <iostream>
#include <exception>
#include "string.h"

/*
 * Title: Heaps, Priority Queues
 * Author: Alperen CAN 
 * ID: 21601740
 * Section: 1
 * Assignment: 3
 * Description: Heapx exceptions
*/
class HeapException : public std::exception{
    
public:
	virtual const char* what() const throw()
	{
		return msg.c_str();
	}
    HeapException(const std::string &message = ""): exception(), msg(message) {};
    ~HeapException() throw() {};

private:
    std::string msg;

}; // end HeapException