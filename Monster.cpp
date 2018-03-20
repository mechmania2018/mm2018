#include <iostream>

#include "Monster.h"

Monster::Monster(int health, int kung_fu, int speed, node_id_t location, DeathEffects effects) :
  Unit(health, kung_fu, speed, location, effects){
    base_health = health;
}

bool Monster::is_player(){
  return false;
}

bool Monster::is_monster() {
  return true;
}

void Monster::die(node_id_t hell_node_id) {
  Unit::die(hell_node_id);
  set_health(base_health);
}
