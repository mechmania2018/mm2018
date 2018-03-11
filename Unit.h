#ifndef UNIT_H
#define UNIT_H

#include "types.h"

#define BASE_MOVEMENT_COUNTER 7
#define ATTACK_DAMAGE 1

class Unit {
public:
  Unit(int init_health, int kung_fu, int speed);

  node_id_t get_destination();
  void set_destination(node_id_t node);

  /*
   * decrements the movement_counter by 1
   * if movement_counter <= speed, returns true and resets the movement counter.
   * otherwise, returns false
   */
  bool do_movement_tick();

  /*
   * subtracts ATTACK_DAMAGE from health
   */
  void take_damage();

  struct Death_Effects {
    int exp_to_players;
    int health_to_players;
    int victory_pts_to_players;
  };

private:
  int health;
  int kung_fu;
  int speed;
  int movement_counter;
  node_id_t destination;
  //Death_Effects effects;
};

#endif
