//
// Created by Eden Bar on 04/12/2022.
//

#include "Functions.h"
#include <iostream>
using namespace std;


// Getting input from the user about how many towns, roads and from where to where
void getInput(int& numOfTowns, int& numOfRoads, char* roadsBetweenTowns , int& currTown, int& destTown){
  cout << "Enter number of towns and roads:" << endl;
  cin >> numOfTowns >> numOfRoads;
  cin.ignore(); // This is to flush the buffer

  numOfTowns++; // This is because we want to start from 1 and not from 0

  cout << "Enter roads between towns" << endl;
  cin.getline(roadsBetweenTowns, LEN);

  cout << "Enter current town and destination town:" << endl;
  cin >> currTown >> destTown;
  while(currTown < 1 || currTown > numOfTowns || destTown < 1 || destTown > numOfTowns){
    cout << "Invalid towns! Please enter valid towns:" << endl;
    cin >> currTown >> destTown;
  }

  cin.ignore(); // This is to flush the buffer
}

// Creating a structure for the towns
void createCountryStructure(char* roadsBetweenTowns, Node** country){
  int size = strlen(roadsBetweenTowns);

  for(int i = 0 ; i<size ; i+=4){
    bool isInTheNodeArray = false;
    int num1 = roadsBetweenTowns[i] - '0';
    int num2 = roadsBetweenTowns[i+2] - '0';

    // Checking if the town is already in the list
    Node *temp = country[num1];
    while(temp != nullptr){
      if(temp->getData() == num2){
        isInTheNodeArray = true;

        break;
      }
      temp = temp->getNext();
    }

    if(!isInTheNodeArray) { // Meaning that the town is not in the list
      Node *town1 = new Node(num1);
      Node *town2 = new Node(num2);

      if (country[num1] == nullptr)
        country[num1] = town2;
      else {
        Node *temp = country[num1];
        while (temp->getNext() != nullptr)
          temp = temp->getNext();

        temp->setNext(town2);
      }

      if (country[num2] == nullptr)
        country[num2] = town1;
      else {
        Node *temp = country[num2];
        while (temp->getNext() != nullptr)
          temp = temp->getNext();

        temp->setNext(town1);
      }
    }
  }

}

// Printing the country structure
void printCountry(Node** country, int numOfTowns) {
  for(int i = 1 ; i<numOfTowns ; i++){
    Node* curr = country[i];
    cout << "town " << i << " is connected to: ";
    while(curr != nullptr){
      cout  << curr->getData() << " ";
      curr = curr->getNext();
    }
    cout << endl;
  }
  cout << endl;
}

// The recursive function that checks if there is a path between the towns
int townDistance(Node **country, int currTown, int destTown,int* color){

  color[currTown] = 1; //turn town into black = visited

  if(currTown == destTown){
    return 0 ;
  }

  else{
    // Check if there is a town that has not been visited
    bool flag = false;
    Node* curr = country[currTown];
    while(curr != nullptr){
      if(color[curr->getData()] == 0){
        flag = true;
      }
      curr = curr->getNext();
    }

    if(!flag)
      return -1;

    else{ // If there is a town that has not been visited
      Node* curr = country[currTown];
      while (curr != nullptr) {
        if (color[curr->getData()] == 0) {
          // Calculate the distance from the current town to the destination town
          int distance = townDistance(country, curr->getData(), destTown, color);
          if (distance != -1)
            return distance + 1;
        }
        curr = curr->getNext();
      }
    }
  }
  return -1;
}

// iterative function that checks if there is a path between the towns using stack
int townDistanceIterative(Node **country, int currTown, int destTown, int* color){

  Item *curr = new Item(country, currTown, destTown, START , 0, color);
  Stack stack;
  stack.push(curr);
  color[currTown] = 1; //turn town into black = visited
//  int distance = 0;

  while(!stack.isEmpty()){
    curr = stack.pop();
    if(curr->getLine() == START){
      if(curr->getCurrTown() == curr->getDestTown()){
        return curr->getDistance();
      }
      else{
        curr->setLine(AFTER);
        color[curr->getCurrTown()] = 1;//turn town into black = visited
        stack.push(curr);

//        next = new Item(country, curr->getCurrTown(), curr->getDestTown(), START, curr->getColor());
//        stack.push(next);
      }
    }
    else{
      if(curr->getLine() == AFTER){
//        color[curr->getCurrTown()] = 1; //turn town into black = visited
//        curr->setLine(AFTER);
//        stack.push(curr);

        Node* temp = country[curr->getCurrTown()];
        Stack toReverseStack;
        while(temp != nullptr){
          if(color[temp->getData()] == 0){

            Item *newItem = new Item(country, temp->getData(), curr->getDestTown(), START, curr->getDistance() + 1, color);
            toReverseStack.push(newItem);

          }
          temp = temp->getNext();
        }
        // We want to flip the stack to get the right order
        while(!toReverseStack.isEmpty()) {
          stack.push(toReverseStack.pop());
        }
      }
    }
  }
  return -1;
}

// Merging to NodeArrays to one
void merge(Node* source, Node** left, Node** right) {
  Node* fast;
  Node* slow;
  slow = source;
  fast = source->getNext();

  while (fast != nullptr) {
    fast = fast->getNext();
    if (fast != nullptr) {
      slow = slow->getNext();
      fast = fast->getNext();
    }
  }

  *left = source;
  *right = slow->getNext();
  slow->setNext(nullptr);
}

// Sorting the NodeArray
Node* SortedMerge(Node* a, Node* b) {
  Node* result = nullptr;

  if (a == nullptr)
    return (b);
  else if (b == nullptr)
    return (a);

  if (a->getData() <= b->getData()) {
    result = a;
    result->setNext(SortedMerge(a->getNext(), b));
  }
  else {
    result = b;
    result->setNext(SortedMerge(a, b->getNext()));
  }
  return (result);
}

//sort list with merge sort
void mergeSort(Node** country) {
  Node* head = *country;
  Node* a;
  Node* b;

  if ((head == nullptr) || (head->getNext() == nullptr)) {
    return;
  }

  merge(head, &a, &b);

  mergeSort(&a);
  mergeSort(&b);

  *country = SortedMerge(a, b);
}

