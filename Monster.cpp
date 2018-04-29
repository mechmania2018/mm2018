#include <iostream>

#include "json.hpp"

#include "Monster.h"

using json = nlohmann::json;
using namespace std;

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
  return "Name: " + get_name() + ", health = " + std::to_string(get_health()) + ", kung fu = " + std::to_string(get_kung_fu()) + ", speed = " + std::to_string(get_speed());
}

std::string Monster::to_json() {
    std::string as_json = "{";
    as_json = as_json + "\"name\": " + "\"" + _name + "\",";
    as_json = as_json + "\"health\": " + std::to_string(_health)+ ",";
    as_json = as_json + "\"kung_fu\": " + std::to_string(_kung_fu)+ ",";
    as_json = as_json + "\"speed\": " + std::to_string(_speed)+ ",";
    as_json = as_json + "\"movement_counter\": " + std::to_string(_movement_counter)+ ",";
    as_json = as_json + "\"location\": " + std::to_string(_location)+ ",";
    as_json = as_json + "\"destination\": " + std::to_string(_destination);
    as_json = as_json + "}";

    return as_json;
}

void Monster::die(node_id_t hell_node_id) {
  Unit::die(hell_node_id);
  set_health(_base_health);
}
