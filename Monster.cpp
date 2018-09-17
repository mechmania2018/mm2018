#include <iostream>

#include "json.hpp"

#include "Monster.h"

using json = nlohmann::json;
using namespace std;

Monster::Monster() : Unit("", 0, INVALID_STANCE, 0, 0, DeathEffects(0, 0, 0, 0, 0)){}

Monster::Monster(json j) :
  Unit(j["Name"], j["Health"], get_stance_val(j["Stance"]), j["Speed"], j["Location"], DeathEffects(j["Death Effects"])) {
    _base_health = get_health();
    _attack = j["Attack"];
}

Monster::Monster(string name, int health, int speed, int stance, int attack, node_id_t location, DeathEffects effects) :
  Unit(name, health, stance, speed, location, effects){
    _base_health = health;
    _attack = attack;
}

bool Monster::is_player(){
  return false;
}

bool Monster::is_monster() {
  return true;
}

string Monster::get_string() {
  return "Name: " + get_name() + ", health = " + to_string(get_health()) + ", movement_counter = " + to_string(get_movement_counter());
}

json Monster::to_json() {
  json j = Unit::to_json();

  j["Type"] = "Monster";
  j["Base Health"] = _base_health;
  j["Attack"] = _attack;

  return j;
}

void Monster::attack(Unit* other) {
  other->set_health(other->get_health() - _attack);
}

void Monster::decrement_movement_counter() {
  Unit::decrement_movement_counter();

  if (time_to_move() && dead()) {
    revive(_base_health);
  }
}
