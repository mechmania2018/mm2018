#ifndef UNIT_H
#define UNIT_H

#include "types.h"

#define NO_MOVEMENT_DEST -1
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

  void decrement_movement_counter();
  bool time_to_move();
  void reset_movement_counter();

  /*
   * subtracts ATTACK_DAMAGE from health
   */
  void take_damage();

  virtual void die(node_id_t hell_node_id);

protected:
  void set_health(int new_health);

private:
  int health;
  int kung_fu;
  int speed;
  int movement_counter;
  node_id_t location;
  node_id_t destination;
};

#endif
