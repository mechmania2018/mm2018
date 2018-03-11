#include "Unit.h"

Unit::Unit(int init_health, int kung_fu, int speed) {
  this->health = init_health;
  this->kung_fu = kung_fu;
  this->speed = speed;
  this->movement_counter = BASE_MOVEMENT_COUNTER;
  this->destination = -1;
}

node_id_t Unit::get_destination(){
  return destination;
}

void Unit::set_destination(node_id_t node){
  destination = node;
}

bool Unit::do_movement_tick(){
  movement_counter --;

  if (movement_counter <= speed) {
    movement_counter = BASE_MOVEMENT_COUNTER;
    return true;
  }

  return false;
}

void Unit::take_damage() {
  health -= ATTACK_DAMAGE;
}
