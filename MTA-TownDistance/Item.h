//
// Created by Eden Bar on 04/12/2022.
//

#ifndef MTA_TOWNDISTANCE_ITEM_H
#define MTA_TOWNDISTANCE_ITEM_H

class Node;

class Item {

  Node **country{};
  int currTown{};
  int destTown{};
  int* color{};
  int line{};
  int distance = -1;

public:


  Item() = default;
  Item(Node** c, int _currTown, int _destTown, int _line, int _distance, int* _color);
  ~Item();
  int getCurrTown() const;
  int getDestTown() const;
  int* getColor();
  int getLine() const;
  void setLine(int line);
  int getDistance() const;
  void setDistance(int _distance);

};


#endif //MTA_TOWNDISTANCE_ITEM_H
