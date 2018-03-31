#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "types.h"

#define INIT_PLAYER_HEALTH 20

class Player : public Unit {
public:
  Player(std::string name);

  int get_num_victory_points();

  bool is_player();
  bool is_monster();

  std::string to_string();

  /*
   * makes the appropriate changes to the Player based on the death effects from another Unit
   */
  void activate_death_effects(DeathEffects effects);

  void do_decision(const std::vector<node_id_t>& adjacent);

private:
  int _exp_points;
  int _victory_points;
};

#endif
