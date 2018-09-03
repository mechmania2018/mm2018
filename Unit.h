#ifndef UNIT_H
#define UNIT_H

#include "types.h"

#include "json.hpp"

#include <string>
#include "includes/json.hpp"

using json = nlohmann::json;
using namespace std;

#define BASE_MOVEMENT_COUNTER 7
#define MAX_SPEED 5

class Unit {
public:
  /*
   * struct that represents the effects on the players of a Unit dying in the same node as the player
   */
  struct DeathEffects {
    DeathEffects(int e, int s, int k, int h, int v) {
      exp = e;
      speed = s;
      kung_fu = k;
      health = h;
      victory_points = v;
    }

    // alternate constructor using JSON
    DeathEffects(json::basic_json j) {
      exp = j["Exp"];
      speed = j["Speed"];
      kung_fu = j["Kung_fu"];
      health = j["Health"];
      victory_points = j["Victory_points"];
    }

    int exp; // experience gained by the player
    int speed; // speed gained by the player
    int kung_fu; // kung-fu gained by the player
    int health; // health gained by the player
    int victory_points; // victory points gained by the player
  };

  Unit(string name, int init_health, int kung_fu, int speed, node_id_t location, DeathEffects effects);

  /*
   * get the DeathEffects from killing this Unit
   */
  DeathEffects get_death_effects();

  /*
   * get the unit's destination
   */
  node_id_t get_destination();

  /*
   * changes the unit's destination. Also resets the unit's movement counter
   */
  void change_destination(node_id_t node);

  /*
   * getter and setter for unit's location
   */
  node_id_t get_location();
  void set_location(node_id_t node);

  /*
   * getters for health, kung_fu, and name
   */
  int get_health();
  int get_kung_fu();
  string get_name();

  /*
   * abstract methods for checking if a unit is a monster or a player
   * (overridden in child classes)
   */
  virtual bool is_monster() = 0;
  virtual bool is_player() = 0;

  /*
   * abstract methods for getting the string or json representation of a unit
   * (overwritten in child classes)
   */
  virtual json to_json() = 0;
  virtual string get_string() = 0;

  /*
   * decrements the Unit's movement counter by 1
   */
  void decrement_movement_counter();

  /*
   * returns true iff it is time for the unit to move (when the movement counter is <= the unit's speed)
   */
  bool time_to_move();

  /*
   * resets the Unit's movement counter to BASE_MOVEMENT_COUNTER
   */
  void reset_movement_counter();

  /*
   * subtracts 1 from the unit's health
   */
  void take_damage();

  /*
   * changes the unit's location to 'hell_node_id' (since it's dead)
   * also changes its destination to its former location, and resets its movement counter
   * (used so non-player units will respawn after some time)
   */
  virtual void die(node_id_t hell_node_id);

protected:
  int get_speed();
  int get_movement_counter();

  /*
   * set the unit's health to a specific value
   */
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
  string _name;
  int _health;
  int _kung_fu;
  int _speed;
  int _movement_counter;
  node_id_t _location;
  node_id_t _destination;
  DeathEffects _effects;
};

#endif
