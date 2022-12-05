//
// Created by Eden Bar on 04/12/2022.
//

#include "Node.h"


Node::Node(int data):data(data),next(nullptr){}

Node::Node():data(0),next(nullptr){};

Node::~Node() {
    delete next;
}

int Node::getData() const {
    return data;
}

void Node::setData(int _data) {
    this->data = _data;
}

Node* Node::getNext() {
    return next;
}

void Node::setNext(Node *_next) {
    this->next = _next;
}

