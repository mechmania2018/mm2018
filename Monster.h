#ifndef MONSTER_H
#define MONSTER_H

#include "types.h"
#include "Unit.h"

class Monster : public Unit {
public:
  Monster(int health, int kung_fu, int speed, node_id_t location);

  bool is_player();
  bool is_monster();

private:
  int base_health;
};

#endif
