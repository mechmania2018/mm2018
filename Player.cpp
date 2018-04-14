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

void Player::do_decision(const vector<node_id_t>& adjacent) {
  cout << get_name() << "'s decision" << endl;
  cout << "Enter destination (options = ";
  for (node_id_t node : adjacent) {
    cout << node << ", ";
  }
  cout << ") :";

  int new_dest;
  cin>> new_dest;
  change_destination(new_dest);

  if (_exp_points > 1) {
    cout << "Enter stat to boost (0=nothing, 1=kung-fu, 2=health, 3=speed):";
    int stat;
    cin>> stat;

    if (stat == 1) {
      add_kung_fu(1);
      _exp_points --;
    } else if (stat == 2) {
      set_health(get_health() + 2);
      _exp_points --;
    } else if (stat == 3) {
      add_speed(1);
      _exp_points --;
    }
  }
}

string Player::get_string() {
    return "Name: " + get_name() + ", health = " + to_string(get_health()) + ", kung fu = " + to_string(get_kung_fu()) + ", speed = " + to_string(get_speed()) + ", exp = " + to_string(_exp_points);
}

string Player::to_json() {
    string as_json = "{";
    as_json = as_json + "\"name\": " + "\"" + _name + "\",";
    as_json = as_json + "\"health\": " + "\"" + to_string(_health)+ "\",";
    as_json = as_json + "\"kung_fu\": " + "\"" + to_string(_kung_fu)+ "\",";
    as_json = as_json + "\"speed\": " + "\"" + to_string(_speed)+ "\",";
    as_json = as_json + "\"movement_counter\": " + "\"" + to_string(_movement_counter)+ "\",";
    as_json = as_json + "\"location\": " + "\"" + to_string(_location)+ "\",";
    as_json = as_json + "\"destination\": " + "\"" + to_string(_destination)+ "\"";
    as_json = as_json + "}";
}
