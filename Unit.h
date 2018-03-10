#ifndef UNIT_H
#define UNIT_H

#include "GameMap.h"

class Unit {
public:
  Unit(int init_health, int kung_fu, int speed);

private:
  int health;
  int kung_fu;
  int speed;
  int movement_counter;
  node_t location;
  node_t destination;
};

#endif
