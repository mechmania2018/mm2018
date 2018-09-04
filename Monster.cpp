#include <iostream>

#include "json.hpp"

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
  j["name"] = get_name();
  j["health"] = get_health();
  j["kung_fu"] = get_kung_fu();
  j["speed"] = get_speed();
  j["movement_counter"] = get_movement_counter();
  j["location"] = get_location();
  j["destination"] = get_destination();

  return j;
}

void Monster::die(node_id_t hell_node_id) {
  Unit::die(hell_node_id);
  set_health(_base_health);
}
