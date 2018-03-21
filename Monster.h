#ifndef MONSTER_H
#define MONSTER_H

#include "types.h"
#include "Unit.h"

class Monster : public Unit {
public:
  Monster(int health, int kung_fu, int speed, node_id_t location, DeathEffects effects);

  bool is_player();
  bool is_monster();

  void die(node_id_t hell_node_id);

private:
  int _base_health;
};

#endif
