#include "Player.h"

Player::Player() : Unit(INIT_PLAYER_HEALTH, 0, 0){
  experience_points = 0;
  victory_points = 0;
}

int Player::get_num_victory_points() {
  return victory_points;
}
