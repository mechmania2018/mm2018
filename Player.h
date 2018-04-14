#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "types.h"

using namespace std;

#define INIT_PLAYER_HEALTH 20

class Player : public Unit {
public:
  Player(string name);

  int get_num_victory_points();

  bool is_player();
  bool is_monster();

  string get_string();

  std::string to_json();

  /*
   * makes the appropriate changes to the Player based on the death effects from another Unit
   */
  void activate_death_effects(DeathEffects effects);

  void do_decision(const vector<node_id_t>& adjacent);

private:
  int _exp_points;
  int _victory_points;
};

#endif
