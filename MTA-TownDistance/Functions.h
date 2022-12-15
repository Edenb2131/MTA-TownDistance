//
// Created by Eden Bar on 04/12/2022.
//

#ifndef MTA_TOWNDISTANCE_FUNCTIONS_H
#define MTA_TOWNDISTANCE_FUNCTIONS_H


#include "Node.h"
#include "Item.h"
#include "Stack.h"

#define LEN 100
#define START 0
#define AFTER 1

// Getting input from the user about how many towns, roads and from where to where
void getInput(int& numOfTowns, int& numOfRoads, char* roadsBetweenTowns , int& currTown, int& destTown);

// Creating a structure for the towns
bool createCountryStructure(char* roadsBetweenTowns, Node** country, int numOfTowns, int numOfRoads);

// Printing the country structure
void printCountry(Node** country, int numOfTowns);


//// The required functions for the program ////

// The recursive function that checks if there is a path between the towns
int townDistanceRec(Node **country, int currTown, int destTown,int* color);

// iterative function that checks if there is a path between the towns using stack
int townDistanceIterative(Node **country, int currTown, int destTown, int* color);

//// The required functions for the program ////


// Merging to NodeArrays to one
void merge(Node* source, Node** left, Node** right);

// Sorting the NodeArray
Node* SortedMerge(Node* a, Node* b);

//sort list with merge sort
void mergeSort(Node** country);


#endif //MTA_TOWNDISTANCE_FUNCTIONS_H
