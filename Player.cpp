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

void Player::do_decision(string decision) {
  // TODO: change decision to a JSON
  int new_dest = 0;
  int stat = 0;

  int num_decisions = sscanf(decision.c_str(), "%d %d", &new_dest, &stat);

  if (num_decisions < 2){
    // both decisions weren't chosen, so just do a default move
    new_dest = 0;
    stat = 0;
  }

  printf("new_dest = %d, stat = %d\n", new_dest, stat);
  change_destination(new_dest);

  if (_exp_points > 1) {
    if (stat == BOOST_KUNG_FU) {
      add_kung_fu(1);
      _exp_points --;
    } else if (stat == BOOST_HEALTH) {
      set_health(get_health() + 2);
      _exp_points --;
    } else if (stat == BOOST_SPEED) {
      add_speed(1);
      _exp_points --;
    }
  }
}

string Player::get_string() {
    return "Name: " + get_name() + ", health = " + to_string(get_health()) + ", kung fu = " + to_string(get_kung_fu()) + ", speed = " + to_string(get_speed()) + ", exp = " + to_string(_exp_points);
}

json Player::to_json() {
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
