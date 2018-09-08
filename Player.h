#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "types.h"

using namespace std;

#define INIT_PLAYER_HEALTH 20

#define BOOST_KUNG_FU 1
#define BOOST_HEALTH 2
#define BOOST_SPEED 3

class Player : public Unit {
public:
  // constructor
  Player(string name);

  /*
   * get the number of victory points the player has
   */
  int get_num_victory_points();

  /*
   * overridden methods from the Unit class
   */
  bool is_player();
  bool is_monster();
  string get_string();
  json to_json();

  /*
   * makes the appropriate changes to the Player based on the death effects from another Unit
   */
  void activate_death_effects(DeathEffects effects);

  /*
   * makes the player do one turn's decision: choose a new destination and a stat to potentially buff
   */
  void do_decision(string decision); // TODO: change string to JSON

private:
  int _exp_points;
  int _victory_points;
};

#endif
