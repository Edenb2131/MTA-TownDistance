//
// Created by Eden Bar on 04/12/2022.
//

#include "Functions.h"
#include <iostream>
using namespace std;

#define ABNORMAL_LEN 10000

// Getting input from the user about how many towns, roads and from where to where
void getInput(int& numOfTowns, int& numOfRoads, char* roadsBetweenTowns , int& currTown, int& destTown){
  cout << "Enter number of towns and roads:" << endl;
  cin >> numOfTowns >> numOfRoads;

  // Getting the roads between the towns and checking the input is valid
  if(numOfTowns < 1 || numOfTowns > ABNORMAL_LEN){
    if(numOfTowns < 0)
      cout << "Number of towns must be positive!" << endl;
    else
      cout << "Invalid number of towns. Enter again number of towns and roads:" << endl;
    while(numOfTowns < 1 || numOfTowns > ABNORMAL_LEN){
      cin >> numOfTowns >> numOfRoads;
    }
  }


  // Checking if there are too many roads for the towns
  // There cannot be more the n*(n-1)/2 roads for n towns
  // For example: 5 towns can have 10 roads at most (5*4/2 = 10)
  // 6 towns can have 15 roads at most (6*5/2 = 15)
  if(numOfRoads > numOfTowns*(numOfTowns-1)/2 || numOfRoads < 0){
    cout << "Invalid number of roads. Enter again number of towns and roads:" << endl;
    while(numOfRoads > numOfTowns*(numOfTowns-1)/2){
      cin >> numOfTowns >> numOfRoads;
    }
  }

  cin.ignore(); // This is to flush the buffer

  numOfTowns++; // This is because we want to start from 1 and not from 0
  // There is no harm in complexity because we are not using the 0 index, so it's not a waste of memory in big numbers

  cout << "Enter roads between towns" << endl;
  cin.getline(roadsBetweenTowns, LEN); // We assume that there is LEN space in the array. Can change LEN in the header file

  // Checking the input of the roads between the towns and asking the user to enter again if the input is invalid
  if(strlen(roadsBetweenTowns) >= numOfRoads*4){
    cout << "Invalid roads. Enter again roads between towns" << endl;
    while(strlen(roadsBetweenTowns) != numOfRoads*3){
      cin.getline(roadsBetweenTowns, LEN); // We assume that there is LEN space in the array. Can change LEN in the header file
    }
  }


  cout << "Enter current town and destination town:" << endl;
  cin >> currTown >> destTown;
  while(currTown < 1 || currTown > numOfTowns || destTown < 1 || destTown > numOfTowns){
    cout << "Invalid towns! Please enter current town and destination town again:" << endl;
    cin >> currTown >> destTown;
  }

  cin.ignore(); // This is to flush the buffer
}

// Creating a structure for the towns
void createCountryStructure(char* roadsBetweenTowns, Node** country) {
  int size = strlen(roadsBetweenTowns); // Getting the size of the roadsBetweenTowns array

  for (int i = 0; i < size; i += 4) {
    bool isInTheNodeArray = false;
    int num1 = roadsBetweenTowns[i] - '0'; // Getting the first town
    int num2 = roadsBetweenTowns[i + 2] - '0'; // Getting the second town

    // Checking if the town is already in the list
    Node *temp = country[num1];
    while (temp != nullptr) {
      if (temp->getData() == num2) {
        isInTheNodeArray = true;

        break;
      }
      temp = temp->getNext();
    }

    if (!isInTheNodeArray) { // Meaning that the town is not in the list

      Node *town1 = new Node(num1); // Creating a new node for the first town
      Node *town2 = new Node(num2); // Creating a new node for the second town

      if (country[num1] == nullptr)  // If the list is empty we just add the new node (Only first case)
        country[num1] = town2;
      else {
        Node *temp = country[num1];
        while (temp->getNext() != nullptr)
          temp = temp->getNext();

        temp->setNext(town2);
      }

      if (country[num2] == nullptr) // If the list is empty we just add the new node (Only first case)
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
int townDistanceRec(Node **country, int currTown, int destTown,int* color){

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

    if(!flag) // Meaning that there is no town that has not been visited
      return -1;

    else{ // If there is a town that has not been visited
      Node* curr = country[currTown];
      while (curr != nullptr) {
        if (color[curr->getData()] == 0) {
          // Calculate the distance from the current town to the destination town
          int distance = townDistanceRec(country, curr->getData(), destTown, color);
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

  while(!stack.isEmpty()){
    curr = stack.pop();
    if(curr->getLine() == START){ // If we are at the start of the town
      if(curr->getCurrTown() == curr->getDestTown()){ // If we are at the destination town
        return curr->getDistance();
      }
      else{
        curr->setLine(AFTER);
        color[curr->getCurrTown()] = 1;//turn town into black = visited
        stack.push(curr);
      }
    }
    else {
      if(curr->getLine() == AFTER){

        Node* temp = country[curr->getCurrTown()];

        // This stack is to reverse the order of the towns so at the end we will get the right order
        Stack toReverseStack;

        while(temp != nullptr){ // Pushing the towns to the stack and counting the number of towns in distance
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

