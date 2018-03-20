#include "Player.h"

Player::Player() : Unit(INIT_PLAYER_HEALTH, 0, 0, 0){
  experience_points = 0;
  victory_points = 0;
}

int Player::get_num_victory_points() {
  return victory_points;
}

bool Player::is_monster() {
  return false;
}

bool Player::is_player() {
  return true;
}

void Player::activate_death_effects(DeathEffects effects) {
  experience_points += effects.exp;
  add_speed(effects.speed);
  add_kung_fu(effects.kung_fu);
  set_health(get_health() + effects.health);
  victory_points += effects.victory_points;
}
