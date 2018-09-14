#include <iostream>
#include <string>

#include "Unit.h"

using namespace std;

Unit::Unit(string name, int init_health, int stance, int speed, node_id_t location, DeathEffects effects) : _effects(effects) {
  _name = name;
  _stance = stance;
  _health = init_health;
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

int Unit::get_stance() {
  return _stance;
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
  j["Stance"] = get_stance_str(_stance);
  j["Health"] = _health;
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

void Unit::die() {
  _destination = _location;
  _movement_counter = BASE_MOVEMENT_COUNTER;
  _dead = true;
}

int Unit::get_stance_val(string stance_str) {
  if (stance_str == "Rock") return STANCE_ROCK;
  else if (stance_str == "Paper") return STANCE_PAPER;
  else if (stance_str == "Scissors") return STANCE_SCISSORS;
  else return INVALID_STANCE;
}

string Unit::get_stance_str(int stance_val) {
  if (stance_val == STANCE_ROCK) return "Rock";
  else if (stance_val == STANCE_PAPER) return "Paper";
  else if (stance_val == STANCE_SCISSORS) return "Scissors";
  else return "Invalid Stance";
}

int Unit::stance_result(int stance_id_1, int stance_id_2) {
  if (stance_id_1 == stance_id_2) return 0; // tie

  // unit loses if they have an invalid stance
  else if (stance_id_1 == INVALID_STANCE) return -1;
  else if (stance_id_2 == INVALID_STANCE) return 1;

  else if (stance_id_1 == STANCE_ROCK){
    if (stance_id_2 == STANCE_PAPER) return -1;
    else return 1;
  }
  else if (stance_id_1 == STANCE_PAPER) {
    if (stance_id_2 == STANCE_ROCK) return 1;
    else return -1;
  }
  else {
    if (stance_id_2 == STANCE_ROCK) return -1;
    return 1;
  }
}

void Unit::set_health(int new_health) {
  _health = new_health;
}

void Unit::set_stance(int new_stance){
  _stance = new_stance;
}

void Unit::add_speed(int speed_added) {
  _speed = min(_speed + speed_added, MAX_SPEED);
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
