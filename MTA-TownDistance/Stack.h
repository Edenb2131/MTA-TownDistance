//
// Created by Eden Bar on 04/12/2022.
//

#ifndef MTA_TOWNDISTANCE_STACK_H
#define MTA_TOWNDISTANCE_STACK_H

#include "Item.h"

class Stack {
    int top;
    Item** stack;
    int phySize = 1;


public:
    Stack(); // Constructor
    ~Stack();// Destructor
    void push(Item*); // Push an element to the stack
    Item* pop(); // Pop an element from the stack
    void makeEmpty(); // Make the stack empty
    bool isEmpty() const; // Check if the stack is empty
    bool isFull() const; // Check if the stack is full
    int getTop();
};


#endif //MTA_TOWNDISTANCE_STACK_H
