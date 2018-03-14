#include <iostream>

#include "Unit.h"

Unit::Unit(int init_health, int kung_fu, int speed, node_id_t location) {
  this->health = init_health;
  this->kung_fu = kung_fu;
  this->speed = speed;
  this->location = location;
  this->movement_counter = BASE_MOVEMENT_COUNTER;
  this->destination = -1;
}

node_id_t Unit::get_destination(){
  return destination;
}

void Unit::set_destination(node_id_t node){
  destination = node;
}

node_id_t Unit::get_location(){
  return location;
}

void Unit::set_location(node_id_t node){
  location = node;
}

int Unit::get_health() {
  return health;
}

int Unit::get_kung_fu(){
  return kung_fu;
}

bool Unit::do_movement_tick(){
  movement_counter --;

  if (movement_counter <= speed) {
    movement_counter = BASE_MOVEMENT_COUNTER;
    location = destination;
    return true;
  }

  return false;
}

void Unit::take_damage() {
  health -= ATTACK_DAMAGE;
}

void Unit::die() {
  destination = location;
  location = HELL_NODE_ID;
  movement_counter = BASE_MOVEMENT_COUNTER;
}
