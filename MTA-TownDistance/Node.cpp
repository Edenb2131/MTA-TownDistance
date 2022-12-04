//
// Created by Eden Bar on 04/12/2022.
//

#include "Node.h"
#include <iostream>
using namespace std;


Node::Node(int data):data(data),next(nullptr){}

Node::Node():data(0),next(nullptr){};

Node::~Node() {
    delete next;
}

int Node::getData() {
    return data;
}

void Node::setData(int data) {
    this->data = data;
}

Node* Node::getNext() {
    return next;
}

void Node::setNext(Node *next) {
    this->next = next;
}

