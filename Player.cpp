#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

using namespace std;


Player::Player(string name) : Unit(name, INIT_PLAYER_HEALTH, 0, 0, 0, DeathEffects(0, 0, 0, 0, 0)){
  _exp_points = 0;
  _victory_points = 0;
}

int Player::get_num_victory_points() {
  return _victory_points;
}

bool Player::is_monster() {
  return false;
}

bool Player::is_player() {
  return true;
}

void Player::activate_death_effects(DeathEffects effects) {
  _exp_points += effects.exp;
  add_speed(effects.speed);
  add_kung_fu(effects.kung_fu);
  set_health(get_health() + effects.health);
  _victory_points += effects.victory_points;
}

void Player::do_decision(Decision dec) {
  //printf("new_dest = %d, stat = %d\n", new_dest, stat);
  change_destination(dec.dest);

  if (_exp_points > 1) {
    if (dec.buff == BOOST_KUNG_FU) {
      add_kung_fu(1);
      _exp_points --;
    } else if (dec.buff == BOOST_HEALTH) {
      set_health(get_health() + 2);
      _exp_points --;
    } else if (dec.buff == BOOST_SPEED) {
      add_speed(1);
      _exp_points --;
    }
  }
}

string Player::get_string() {
    return "Name: " + get_name() + ", health = " + to_string(get_health()) + ", kung fu = " + to_string(get_kung_fu()) + ", speed = " + to_string(get_speed()) + ", exp = " + to_string(_exp_points);
}

json Player::to_json() {
    json j = Unit::to_json();
    j["Type"] = "Player";

    return j;
}
