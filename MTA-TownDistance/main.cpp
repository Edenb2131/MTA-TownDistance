
#include <iostream>
using namespace std;
#include <string>
#include "Functions.h"

// Forward declaration
class Item;
class Stack;
class Node;


int main() {

  int numOfTowns = 0 , numOfRoads = 0;
  int currTown = 0, destTown = 0;
  char roadsBetweenTowns[LEN]; // can we assume size ????
  getInput(numOfTowns, numOfRoads, roadsBetweenTowns, currTown, destTown);

  Node **country = new Node* [numOfTowns];
  int *color = new int [numOfTowns]; // 0 - white, 1 - black
  for(int i = 0 ; i<numOfTowns ; i++){
    country[i] = nullptr;
    color[i] = 0;
  }

  // building country structure
  bool countryStructure = createCountryStructure(roadsBetweenTowns, country, numOfTowns , numOfRoads) ;

  if(countryStructure) {


    //sorting country structure nodes - merge sort
    for (int i = 1; i < numOfTowns; i++)
      mergeSort(&country[i]);

    //print country structure
    //printCountry(country, numOfTowns);

    int res1 = townDistanceRec(country, currTown, destTown, color);
    cout << "The recursion result is: " << res1 << endl;

    // Reset the color array for the iterative function
    for (int i = 0; i < numOfTowns; i++) {
      color[i] = 0;
    }

    int res2 = townDistanceIterative(country, currTown, destTown, color);
    cout << "The iterative result is: " << res2 << endl;

  }
  else{
    cout << "The country structure was not built. Run again." << endl;
  }

  for(int i = 0; i<numOfTowns ; i++){
    delete country[i];
  }
  delete[] country;

  delete [] color;

  // No need to delete roadsBetweenTowns

  return 0;
}