//
// Created by Eden Bar on 04/12/2022.
//

#ifndef MTA_TOWNDISTANCE_NODE_H
#define MTA_TOWNDISTANCE_NODE_H


class Node {

    int data;
    Node *next;
   // bool visited = false; // This is color. white = false, black = true.

public:
    Node();
    Node(int data);
    ~Node();
    int getData() const;
    void setData(int _data);
    Node* getNext();
    void setNext(Node *_next);

};


#endif //MTA_TOWNDISTANCE_NODE_H
