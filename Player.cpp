#include <iostream>
#include <string>
#include <vector>

#include "Player.h"

Player::Player(std::string name) : Unit(name, INIT_PLAYER_HEALTH, 0, 0, 0, DeathEffects(0, 0, 0, 0, 0)){
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

void Player::do_decision(const std::vector<node_id_t>& adjacent) {
  std::cout << get_name() << "'s decision" << std::endl;
  std::cout << "Enter destination (options = ";
  for (node_id_t node : adjacent) {
    std::cout << node << ", ";
  }
  std::cout << ") :";

  int new_dest;
  std::cin>> new_dest;
  change_destination(new_dest);

  if (_exp_points > 1) {
    std::cout << "Enter stat to boost (0=nothing, 1=kung-fu, 2=health, 3=speed):";
    int stat;
    std::cin>> stat;

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

std::string Player::to_string() {
    return "Name: " + get_name() + ", health = " + std::to_string(get_health()) + ", kung fu = " + std::to_string(get_kung_fu()) + ", speed = " + std::to_string(get_speed()) + ", exp = " + std::to_string(_exp_points);
}
