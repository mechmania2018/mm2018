#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "types.h"

using namespace std;

#define INIT_PLAYER_HEALTH 5

#define BUFF_NOTHING 0
#define BOOST_KUNG_FU 1
#define BOOST_HEALTH 2
#define BOOST_SPEED 3

#define INVALID_DESTINATION -1

class Player : public Unit {
public:
  // constructor
  Player(string name);

  /*
   * get the number of victory points the player has
   */
  int get_num_victory_points();

  /*
   * overridden methods from the Unit class
   */
  bool is_player();
  bool is_monster();
  string get_string();
  json to_json();

  /*
   * makes the appropriate changes to the Player based on the death effects from another Unit
   */
  void activate_death_effects(DeathEffects effects);

  struct Decision{
    Decision(string json_str) {
      try {
        json::basic_json j = json::parse(json_str);

        dest = j["Dest"];
        buff = j["Buff"];
      } catch (exception e) {
        // something was wrong with the decision string -- use the default decision
        cerr << "Received invalid decision: " << json_str << endl;
        dest = INVALID_DESTINATION;
        buff = BUFF_NOTHING;
      }
    }

    int dest;
    int buff;
  };

  /*
   * makes the player do one turn's decision: choose a new destination and a stat to potentially buff
   */
  void do_decision(Decision dec);

private:
  int _exp_points;
  int _victory_points;
};

#endif
