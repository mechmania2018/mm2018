#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"

#define INIT_PLAYER_HEALTH 10

class Player : public Unit {
public:
  Player();

  int get_num_victory_points();

private:
  int experience_points;
  int victory_points;
};

#endif
