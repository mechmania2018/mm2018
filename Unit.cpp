#include <iostream>

#include "Unit.h"

Unit::Unit(int init_health, int kung_fu, int speed, node_id_t location) {
  this->health = init_health;
  this->kung_fu = kung_fu;
  this->speed = speed;
  this->location = location;
  this->movement_counter = BASE_MOVEMENT_COUNTER;
  this->destination = NO_MOVEMENT_DEST;
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

void Unit::decrement_movement_counter() {
  if (destination != NO_MOVEMENT_DEST) {
    movement_counter --;
  }
}

bool Unit::time_to_move() {
  return (movement_counter <= speed);
}

void Unit::reset_movement_counter(){
  movement_counter = BASE_MOVEMENT_COUNTER;
}

void Unit::take_damage() {
  health -= ATTACK_DAMAGE;
}

void Unit::die(node_id_t hell_node_id) {
  destination = location;
  location = hell_node_id;
  movement_counter = BASE_MOVEMENT_COUNTER;
}

void Unit::set_health(int new_health) {
  health = new_health;
}
