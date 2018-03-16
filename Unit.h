#ifndef UNIT_H
#define UNIT_H

#include "types.h"

#define BASE_MOVEMENT_COUNTER 7
#define ATTACK_DAMAGE 1

class Unit {
public:
  Unit(int init_health, int kung_fu, int speed, node_id_t location);

  node_id_t get_destination();
  void set_destination(node_id_t node);
  node_id_t get_location();
  void set_location(node_id_t node);

  int get_health();
  int get_kung_fu();

   virtual bool is_monster() = 0;
   virtual bool is_player() = 0;

  /*
   * decrements the movement_counter by 1
   * if movement_counter <= speed, returns true, changes the monster's location, and resets the movement counter.
   * otherwise, returns false
   */
  bool do_movement_tick();

  /*
   * subtracts ATTACK_DAMAGE from health
   */
  void take_damage();

  void die(node_id_t hell_node_id);

private:
  int health;
  int kung_fu;
  int speed;
  int movement_counter;
  node_id_t location;
  node_id_t destination;
};

#endif
