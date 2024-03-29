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

using namespace std;
using json = nlohmann::json;

class Game{
public:
  /*
   * create a map from a json string
   */
  Game(string json_map, string p1_name, string p2_name);

  ~Game();

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
  void do_player_decisions(Player::Decision dec1, Player::Decision dec2);

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

  json to_json();

  void move_players_to_start();

private:
  /*
   * internal representation of a Node
   */
  struct Node {
    vector<node_id_t> adjacent;
    vector<Unit*> units;
  };

  // array on the heap holding all of the monsters' data
  Monster* _monsters;
  size_t num_monsters;

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
   * does the decision for just one player
   */
  void do_player_decision(Player& player, Player::Decision dec);

  /*
   * helper function - checks weather a specific player should die right now
   */
  bool will_player_die(Player& p);

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
