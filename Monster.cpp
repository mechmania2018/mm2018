#include "Monster.h"

Monster::Monster(int health, int kung_fu, int speed, node_id_t location) :
  Unit(health, kung_fu, speed, location){
    base_health = health;
}

bool Monster::is_player(){
  return false;
}

bool Monster::is_monster() {
  return true;
}
