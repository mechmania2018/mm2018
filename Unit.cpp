#include <iostream>
#include <string>

#include "Unit.h"

using namespace std;

Unit::Unit(string name, int init_health, int kung_fu, int speed, node_id_t location, DeathEffects effects) : _effects(effects) {
  _name = name;
  _health = init_health;
  _kung_fu = kung_fu;
  _speed = speed;
  _location = location;
  _movement_counter = BASE_MOVEMENT_COUNTER;
  _destination = location;
  _dead = false;
}

Unit::DeathEffects Unit::get_death_effects() {
  return _effects;
}

node_id_t Unit::get_destination(){
  return _destination;
}

void Unit::change_destination(node_id_t node){
  if (node != _destination) {
    _movement_counter = BASE_MOVEMENT_COUNTER;
    _destination = node;
  }
}

node_id_t Unit::get_location(){
  return _location;
}

void Unit::set_location(node_id_t node){
  _location = node;
}

int Unit::get_health() {
  return _health;
}

int Unit::get_kung_fu(){
  return _kung_fu;
}

string Unit::get_name() {
  return _name;
}

bool Unit::dead() {
  return _dead;
}

json Unit::to_json(){
  json j;
  j["Name"] = _name;
  j["Health"] = _health;
  j["Kung_fu"] = _kung_fu;
  j["Speed"] = _speed;
  j["Movement_counter"] = _movement_counter;
  j["Location"] = _location;
  j["Destination"] = _destination;
  j["Dead"] = _dead;
  j["Death Effects"] = _effects.to_json();

  return j;
}

void Unit::decrement_movement_counter() {
  _movement_counter --;
}

bool Unit::time_to_move() {
  return (_movement_counter <= _speed);
}

void Unit::reset_movement_counter(){
  _movement_counter = BASE_MOVEMENT_COUNTER;
}

void Unit::take_damage() {
  _health --;
}

void Unit::die() {
  _destination = _location;
  _movement_counter = BASE_MOVEMENT_COUNTER;
  _dead = true;
}

void Unit::set_health(int new_health) {
  _health = new_health;
}

void Unit::add_speed(int speed_added) {
  _speed = min(_speed + speed_added, MAX_SPEED);
}

void Unit::add_kung_fu(int kung_fu_added) {
  _kung_fu += kung_fu_added;
}

int Unit::get_speed() {
  return _speed;
}

int Unit::get_movement_counter() {
  return _movement_counter;
}

void Unit::revive(int health) {
  _dead = false;
  _health = health;
}
