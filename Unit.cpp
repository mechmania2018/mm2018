#include "Unit.h"

Unit::Unit(int init_health, int kung_fu, int speed) {
  this->health = init_health;
  this->kung_fu = kung_fu;
  this->speed = speed;
  this->movement_counter = -1;
  this->location = 0;
  this->destination = -1;
}
