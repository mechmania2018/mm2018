# ifndef GAME_MAP_H
# define GAME_MAP_H

#include <map>
#include <vector>

#include "Unit.h"
#include "Player.h"
#include "types.h"

using namespace std;

class Game{
public:
  Game(int num_nodes, string p1_name, string p2_name);

  /*
   * adds a connection between node1 and node2
   * (assumes that node1 and node2 are not already connected)
   */
  void add_connection(node_id_t node1, node_id_t node2);

  /*
   * adds a unit to the Game (at the location specified by the unit)
   * (Note: u is passed as a pointer, so make sure you don't free the unit's memory)
   */
  void add_unit(Unit* u);

  /*
   * gets the list of nodes that are adjacent to 'node'
   */
  vector<node_id_t> get_adjacent_nodes(node_id_t node);

  /*
   * gets the list of units present at 'node'
   */
  vector<Unit*> get_units_at(node_id_t node);

  void do_player_decisions();

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
   * returns 0 if no winner yet, 1 if player 1 wins, 2 if player 2 wins, or 3 if it's a tie (both players are dead and have the same number of victory points)
   */
  int get_winner();

  void print_game();

  std::string to_json();

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
  std::vector<Unit*> all_units;
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
  void remove_unit(Node& n, Unit* unit);

  /*
   * helper function - adds a unit to a Node
   */
  void add_unit(Node& n, Unit* unit);
};

# endif
