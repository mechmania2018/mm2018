#include <iostream>

#include "Monster.h"

using namespace std;

Monster::Monster(string name, int health, int kung_fu, int speed, node_id_t location, DeathEffects effects) :
  Unit(name, health, kung_fu, speed, location, effects){
    _base_health = health;
}

bool Monster::is_player(){
  return false;
}

bool Monster::is_monster() {
  return true;
}

string Monster::get_string() {
  return "Name: " + get_name() + ", health = " + to_string(get_health()) + ", kung fu = " + to_string(get_kung_fu()) + ", speed = " + to_string(get_speed());
}

void Monster::die(node_id_t hell_node_id) {
  Unit::die(hell_node_id);
  set_health(_base_health);
}
