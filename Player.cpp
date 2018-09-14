#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

using namespace std;


Player::Player(string name) : Unit(name, INIT_PLAYER_HEALTH, 0, 0, 0, DeathEffects(0, 0, 0, 0, 0)){
  _rock = 1;
  _paper = 1;
  _scissors = 1;
}

bool Player::is_monster() {
  return false;
}

bool Player::is_player() {
  return true;
}

void Player::attack(Unit* other) {
  switch(stance_result(get_stance(), other->get_stance())){
    case 1: // our stance wins!
      other->set_health(other->get_health() - stance_stat(get_stance()));
      break;
    case 0: // it was a tie
      other->set_health(other->get_health() - 1);
      break;
    case -1:// our stance lost :(
      // deal no damage
      break;
  }
}

void Player::activate_death_effects(DeathEffects effects) {
  add_speed(effects.speed);
  set_health(get_health() + effects.health);
  _rock += effects.rock;
  _paper += effects.paper;
  _scissors += effects.scissors;
}

void Player::do_decision(Decision dec) {
  change_destination(dec.dest);
  set_stance(dec.stance);
}

string Player::get_string() {
    return "Name: " + get_name() + ", health = " + to_string(get_health()) + ", speed = " + to_string(get_speed());
}

json Player::to_json() {
    json j = Unit::to_json();

    j["Type"] = "Player";
    j["Rock"] = _rock;
    j["Paper"] = _paper;
    j["Scissors"] = _scissors;

    return j;
}

int Player::stance_stat(int stance_id){
  if (stance_id == STANCE_ROCK) return _rock;
  else if (stance_id == STANCE_PAPER) return _paper;
  else if (stance_id == STANCE_SCISSORS) return _scissors;
  else return 0;
}
