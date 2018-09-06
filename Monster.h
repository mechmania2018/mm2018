#ifndef MONSTER_H
#define MONSTER_H

#include "./includes/json.hpp"

#include "types.h"
#include "Unit.h"

using json = nlohmann::json;
using namespace std;

class Monster : public Unit {
public:
  Monster(json::basic_json j);

  Monster(string name, int health, int kung_fu, int speed, node_id_t location, DeathEffects effects);
  bool is_player();
  bool is_monster();

  string get_string();

  json to_json();

  void die(node_id_t hell_node_id);

private:
  int _base_health;
};

#endif
