# ifndef GAME_MAP_H
# define GAME_MAP_H

#include <map>
#include <vector>

#include "Monster.h"
#include "Unit.h"
#include "Player.h"
#include "types.h"
#include "includes/json.hpp"

#define NO_WINNER 0
#define P1_WINS 1
#define P2_WINS 2
#define TIED_GAME 3

// TODO: add something to force the game to end after a certain amount of time

using namespace std;
using json = nlohmann::json;

class Game{
public:
  /*
   * create a map from a json string
   */
  Game(string json_map, string p1_name, string p2_name);

  /*
   * gets the list of nodes that are adjacent to 'node'
   */
  vector<node_id_t> get_adjacent_nodes(node_id_t node);

  /*
   * gets the list of units present at 'node'
   */
  vector<Unit*> get_units_at(node_id_t node);

  /*
   * does one turn's worth of player decisions for each player
   */
  void do_player_decisions(string dec1, string dec2);

  /*
   * handles movement counters, then movement for all units
   */
  void do_movement_tick();

  /*
   * all units with the same location as a player lose 1 health
   * (note: currently, two monsters on the same node will not deal damage to each other unless a player is also at that node)
   */
  void do_damage_tick();

  /*
   * Checks if monster healths are lower than player's kung-fu, and kills the monster(s) if so
   */
  void do_monster_deaths();

  /*
   * Checks if player healths are lower than another unit's kung-fu, and kills the player(s) if so
   */
  void do_player_deaths();

  /*
   * returns NO_WINNER, P1_WINS, P2_WINS, or TIED_GAME, respectively
   */
  int get_winner();

  /*
   * prints a representation of the game to stdout
   */
  void print_game();

<<<<<<< f94eb2e9441b000bd5541ba18c8a42fabc3636f7
  json to_json();
=======
  /*
   * returns a json string representation of the current state of the game
   */
  std::string to_json();
>>>>>>> added comments and other clarifying stuff

  /*
   * gets the node_id for hell
   */
  node_id_t get_hell_node_id();

private:
  /*
   * internal representation of a Node
   */
  struct Node {
    vector<node_id_t> adjacent;
    vector<Unit*> units;
  };
  std::vector<Monster> _monsters; // TODO: change to an array

  /*
   * list of the nodes in the game
   * when a Node is referred to using a node_id, it is just the index of the node in this vector
   */
  vector<Node> _nodes;

  /*
   * stores each of the two players
   */
  Player _player1;
  Player _player2;

  /*
   * adds a connection between node1 and node2
   * (assumes that node1 and node2 are not already connected)
   */
  void add_connection(node_id_t node1, node_id_t node2);

  /*
   * helper function - does the monster deaths associated with just one of the players
   */
  void do_monster_deaths(Player& p);

  /*
   * helper function - checks weather a specific player should die right now
   */
  bool will_player_die(Player& p);

  /*
   * helper function - does the damage tick stuff for a single Node
   */
  void do_damage_tick(Node& n);

  /*
   * helper function - removes a unit from a Node
   */
  void remove_unit_from_node(Node& n, Unit* unit);

  /*
   * helper function - adds a unit to a Node
   */
  void add_unit_to_node(Node& n, Unit* unit);
};

# endif
