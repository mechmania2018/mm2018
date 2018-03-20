#ifndef UNIT_H
#define UNIT_H

#include "types.h"

#define BASE_MOVEMENT_COUNTER 7
#define MAX_SPEED 5

class Unit {
public:
  Unit(int init_health, int kung_fu, int speed, node_id_t location);

  /*
   * bonuses given to players on the same node when this unit dies
   * TODO: use this
   */
  struct DeathEffects {
    int exp;
    int speed;
    int kung_fu;
    int health;
    int victory_points;
  };

  /*
   * getter and setter for unit's destination
   */
  node_id_t get_destination();

  /*
   * changes the unit's destination. Also resets the movement counter
   */
  void change_destination(node_id_t node);

  /*
   * getter and setter for unit's location
   */
  node_id_t get_location();
  void set_location(node_id_t node);

  /*
   * getters for health and kung_fu
   */
  int get_health();
  int get_kung_fu();

  /*
   * abstract methods for checking if a unit is a monster or a player
   * (overridden in child classes)
   */
  virtual bool is_monster() = 0;
  virtual bool is_player() = 0;

  void decrement_movement_counter();
  bool time_to_move();
  void reset_movement_counter();

  /*
   * subtracts 1 from health
   */
  void take_damage();

  virtual void die(node_id_t hell_node_id);

protected:
  void set_health(int new_health);

  /*
   * adds speed_added to unit's speed (without going over MAX_SPEED)
   */
  void add_speed(int speed_added);

  /*
   * adds kung_fu_added to the unit's kung_fu
   */
  void add_kung_fu(int kung_fu_added);

private:
  int _health;
  int _kung_fu;
  int _speed;
  int _movement_counter;
  node_id_t _location;
  node_id_t _destination;
};

#endif
