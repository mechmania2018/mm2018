#ifndef UNIT_H
#define UNIT_H

#include "types.h"
#include "includes/json.hpp"

#include <string>
#include "includes/json.hpp"

using json = nlohmann::json;
using namespace std;

#define BASE_MOVEMENT_COUNTER 7
#define MAX_SPEED 5

#define INVALID_STANCE 0
#define STANCE_ROCK 1
#define STANCE_PAPER 2
#define STANCE_SCISSORS 3

class Unit {
public:
  /*
   * struct that represents the effects on the players of a Unit dying in the same node as the player
   */
  class DeathEffects {
  public:
    DeathEffects(int r, int p, int sc, int sp, int h) {
      rock = r;
      paper = p;
      scissors = sc;
      speed = sp;
      health = h;
    }

    // alternate constructor using JSON
    DeathEffects(json j) {
      rock = j["Rock"];
      paper = j["Paper"];
      scissors = j["Scissors"];
      speed = j["Speed"];
      health = j["Health"];
    }

    json to_json() {
      json j;

      j["Rock"] = rock;
      j["Paper"] = paper;
      j["Scissors"] = scissors;
      j["Speed"] = speed;
      j["Health"] = health;

      return j;
    }

    int rock;
    int paper;
    int scissors;
    int speed; // speed gained by the player
    int health; // health gained by the player
  };

  Unit(string name, int init_health, int init_stance, int speed, node_id_t location, DeathEffects effects);

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
   * getters for health, stance, name, and death status
   */
  int get_health();
  int get_stance();
  string get_name();
  bool dead();

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
  virtual json to_json();
  virtual string get_string() = 0;

  /*
   * decrements the Unit's movement counter by 1
   */
  virtual void decrement_movement_counter();

  /*
   * returns true iff it is time for the unit to move (when the movement counter is <= the unit's speed)
   */
  bool time_to_move();

  /*
   * resets the Unit's movement counter to BASE_MOVEMENT_COUNTER
   */
  void reset_movement_counter();

  /*
   * method for this unit to (potentially) deal damage to another -- overridden in child classes
   */
  virtual void attack(Unit* other) = 0;

  /*
   * sets the unit to be dead
   */
  virtual void die();

  /*
   * set the unit's health to a specific value
   */
  void set_health(int new_health);

  static int get_stance_val(string stance_str);
  static string get_stance_str(int stance_val);

  /*
   * returns 1 if first stance wins, 0 if tie, -1 if second stance wins
   */
  static int stance_result(int stance_id_1, int stance_id_2);

protected:
  int get_speed();
  int get_movement_counter();

  void set_stance(int new_stance);

  /*
   * adds speed_added to unit's speed (without going over MAX_SPEED)
   */
  void add_speed(int speed_added);

  /*
   * brings a unit back to life, with a specified amount of health
   */
  void revive(int health);

private:
  string _name;
  int _stance;
  int _health;
  int _speed;
  int _movement_counter;
  node_id_t _location;
  node_id_t _destination;
  DeathEffects _effects;
  bool _dead;
};

#endif
