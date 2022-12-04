//
// Created by Eden Bar on 04/12/2022.
//

#ifndef MTA_TOWNDISTANCE_ITEM_H
#define MTA_TOWNDISTANCE_ITEM_H

class Node;

class Item {

  Node **country;
  int currTown;
  int destTown;
  int* color;
  int line;


public:
    int distance = -1;

  Item() = default;
  Item(Node** c, int _currTown, int _destTown, int _line, int _distance, int* _color);
  ~Item();
  int getCurrTown();
  void setCurrTown(int currTown);
  int getDestTown();
  int* getColor();
  void setDestTown(int destTown);
  int getLine();
  void setLine(int line);
  Node** getCountry();
  int getDistance();

};


#endif //MTA_TOWNDISTANCE_ITEM_H
