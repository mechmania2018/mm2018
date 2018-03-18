#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "types.h"

#define INIT_PLAYER_HEALTH 15

class Player : public Unit {
public:
  Player();

  int get_num_victory_points();

  bool is_player();
  bool is_monster();

private:
  int experience_points;
  int victory_points;
};

#endif
