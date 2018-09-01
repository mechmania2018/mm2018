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
  change_destination(new_dest); //need to make sure destination is valid

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

void Player::do_decision(const vector<node_id_t>& adjacent, string player_decision) {
    //need to ensure response is valid format and within parameters
    int response_destination = player_decision[0] - '0';
    int response_statboost = player_decision[1] - '0';
    node_id_t a = adjacent[0];

    change_destination(response_destination); //need to make sure destination is valid
    if (_exp_points > 1) {
        if (response_statboost == 1) {
            add_kung_fu(1);
            _exp_points --;
        } else if (response_statboost == 2) {
            set_health(get_health() + 2);
            _exp_points --;
        } else if (response_statboost == 3) {
            add_speed(1);
            _exp_points --;
        }
    }
}

string Player::get_string() {
    return "Name: " + get_name() + ", health = " + std::to_string(get_health()) + ", kung fu = " + std::to_string(get_kung_fu()) + ", speed = " + std::to_string(get_speed()) + ", exp = " + std::to_string(_exp_points);
}

json Player::to_json() {

    json j;
    j["name"] = _name;
    j["health"] = _health;
    j["kung_fu"] = _kung_fu;
    j["speed"] = _speed;
    j["movement_counter"] = _movement_counter;
    j["location"] = _location;
    j["destination"] = _destination;

    return j;
}
