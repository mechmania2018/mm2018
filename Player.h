#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "types.h"

using namespace std;

#define INIT_PLAYER_HEALTH 20

#define INVALID_DESTINATION -1

#define BAD_DECISIONS_ALLOWED 0

class Player : public Unit {
public:
  // constructor
  Player(string name);

  /*
   * overridden methods from the Unit class
   */
  bool is_player();
  bool is_monster();
  string get_string();
  json to_json();
  void attack(Unit* other);

  /*
   * makes the appropriate changes to the Player based on the death effects from another Unit
   */
  void activate_death_effects(DeathEffects effects);

  struct Decision{
    Decision(string json_str) {
      try {
        json j = json::parse(json_str);

        dest = j["Dest"];

        stance = get_stance_val(j["Stance"]);

      } catch (exception e) {
        // something was wrong with the decision string -- use the default decision
        cerr << "Received invalid decision: " << json_str << endl;
        dest = INVALID_DESTINATION;
        stance = INVALID_STANCE;
      }
    }

    int dest;
    int stance;
  };

  /*
   * makes the player do one turn's decision: choose a new destination and a stat to potentially buff
   */
  void do_decision(Decision dec);

private:
  /*
   * returns the stat value of the stance indicated by stance_id
   */
  int stance_stat(int stance_id);

  // count of the number of times the player has sent an invalid or empty response in a turn
  int _bad_decisions;

  int _rock;
  int _paper;
  int _scissors;
};

#endif
