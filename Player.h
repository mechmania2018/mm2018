#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "types.h"

#define INIT_PLAYER_HEALTH 7

class Player : public Unit {
public:
  Player();

  int get_num_victory_points();

  bool is_player();
  bool is_monster();

  /*
   * makes the appropriate changes to the Player based on the death effects
   */
  void activate_death_effects(DeathEffects effects);

private:
  int _exp_points;
  int _victory_points;
};

#endif
