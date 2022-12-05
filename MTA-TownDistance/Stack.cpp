//
// Created by Eden Bar on 04/12/2022.
//
#include "iostream"
#include "Stack.h"
using namespace std;

// Constructor
Stack::Stack() : top(0), stack(nullptr), phySize(1){
    stack = new Item*[phySize];
}

// Destructor
Stack::~Stack() {
    for(int i = 0; i < top; i++){
        delete stack[i];
    }
    delete[] stack;
}

// Push an element to the stack
void Stack::push(Item* data){
    if (isFull()){
        phySize *= 2;
        Item** temp = new Item*[phySize];
        for (int i = 0; i < top; i++){
            temp[i] = stack[i];
        }
        delete stack;
        stack = temp;
    }
    stack[top++] = data;
}

// Pop an element from the stack
Item* Stack::pop(){
    if (isEmpty()){
        cout << "The stack is empty" << endl;
        return nullptr;
    }

    return stack[--top];
}

// Make the stack empty
void Stack::makeEmpty(){
    top = 0;
}

// Check if the stack is empty
bool Stack::isEmpty() const{
    return top == 0;
}

// Check if the stack is full
bool Stack::isFull() const{
    return top == phySize;
}

// Get top
int Stack::getTop() {
  return top;
}