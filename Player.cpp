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

//void Player::do_decision(const vector<node_id_t>& adjacent, string decision) {
  //cout << get_name() << "'s decision" << endl;
  //cout << "Enter destination (options = ";
  //for (node_id_t node : adjacent) {
    //cout << node << ", ";
  //}
  //cout << ") :";

void Player::do_decision(string decision) {
  int new_dest = 0;
  int stat = 0;
  //cin>> new_dest;
  int num_decisions = sscanf(decision.c_str(), "%d %d", &new_dest, &stat);
  if (num_decisions != 1 && num_decisions != 2){
    new_dest = 0;
    stat = 0;
  }
  printf("new_dest = %d, stat = %d\n", new_dest, stat);
  change_destination(new_dest);

  if (_exp_points > 1) {
    //cout << "Enter stat to boost (0=nothing, 1=kung-fu, 2=health, 3=speed):";
    //int stat;
    //cin>> stat;

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
