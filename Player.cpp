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
  // TODO: dont reset movement counter if destination decision doesnt change, or handle them deciding not to change destination.
  int new_dest = 0;
  int stat = 0;
  if (decision.size() != 2) {
    cout << "not enough decisions, performing default. \n";
    change_destination(new_dest);
    return;
  }
  printf("new_dest = %c, stat = %c\n", decision[1], decision[0]);
  new_dest = (int)decision[1] - 48;
  stat = (int)decision[0] - 48;
  if (new_dest != _destination) change_destination(new_dest);

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
