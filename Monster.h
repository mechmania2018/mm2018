#ifndef MONSTER_H
#define MONSTER_H

#include "./includes/json.hpp"

#include "types.h"
#include "Unit.h"

using json = nlohmann::json;
using namespace std;

class Monster : public Unit {
public:
  Monster();

  /*
   * constructor for creating monsters from map JSONs
   */
  Monster(json::basic_json j);

  /*
   * manual constructor
   */
  Monster(string name, int health, int kung_fu, int speed, node_id_t location, DeathEffects effects);

  /*
   * Overridden methods from Unit
   */
  bool is_player();
  bool is_monster();
  string get_string();
  json to_json();

  /*
   * overridden from Unit class -- brings the monster back to life if it is time for it to respawn
   */
  void decrement_movement_counter();

private:
  // health the monster regenerates to whenever it respawns
  int _base_health;
};

#endif
