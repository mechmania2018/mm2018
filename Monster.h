#ifndef MONSTER_H
#define MONSTER_H

#include "json.hpp"

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
   * Sets the monster's location to hell and sets it to respawn after some time (based off its speed)
   */
  void die(node_id_t hell_node_id);

private:
  // health the monster regenerates to whenever it respawns
  int _base_health;
};

#endif
