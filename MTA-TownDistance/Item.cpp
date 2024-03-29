//
// Created by Eden Bar on 04/12/2022.
//

#include "Item.h"
#include <iostream>
using namespace std;

// Constructor
Item::Item(Node** c, int _currTown, int _destTown, int _line, int _distance, int* _color) {
    country = c;
    currTown = _currTown;
    destTown = _destTown;
    line = _line;
    distance = _distance;
    color = _color;
}

// Destructor
Item::~Item() {
}

// Get the current town
int Item::getCurrTown() const {
    return currTown;
}

// Get line
int Item::getLine() const {
    return line;
}

// Get the dest town
int Item::getDestTown() const {
    return destTown;
}

// Get Color
int* Item::getColor() {
    return color;
}

// Set Line
void Item::setLine(int _line) {
    line = _line;
}

// Get distance
int Item::getDistance() const {
    return distance;
}

// Set distance
void Item::setDistance(int _distance) {
    distance = _distance;
}