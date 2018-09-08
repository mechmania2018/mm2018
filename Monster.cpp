#include <iostream>

#include "./includes/json.hpp"

#include "Monster.h"

using json = nlohmann::json;
using namespace std;

Monster::Monster() : Unit("", 0, 0, 0, 0, DeathEffects(0, 0, 0, 0, 0)){}

Monster::Monster(json::basic_json j) :
  Unit(j["Name"], j["Health"], j["Kung_fu"], j["Speed"], j["Location"], DeathEffects(j["DeathEffects"])) {
    _base_health = get_health();
}

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

json Monster::to_json() {
  json j;
  j["Name"] = get_name();
  j["Health"] = get_health();
  j["Kung_fu"] = get_kung_fu();
  j["Speed"] = get_speed();
  j["Movement_counter"] = get_movement_counter();
  j["Location"] = get_location();
  j["Destination"] = get_destination();
  j["Dead"] = dead();

  return j;
}

void Monster::decrement_movement_counter() {
  Unit::decrement_movement_counter();

  if (time_to_move()) {
    revive(_base_health);
  }
}
