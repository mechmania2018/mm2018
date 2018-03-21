# ifndef GAME_MAP_H
# define GAME_MAP_H

#include <map>
#include <vector>

#include "Unit.h"
#include "Player.h"
#include "types.h"

class Game{
public:
  Game(int num_nodes);

  // TODO: use this
  struct Decision {
    node_id_t destination;
    int level_up_choice;
  };

  /*
   * adds a connection between node1 and node2
   * assumes that node1 and node2 are not already connected
   */
  void add_connection(node_id_t node1, node_id_t node2);
  void add_unit(Unit* u);

  std::vector<node_id_t> get_adjacent_nodes(node_id_t node);
  std::vector<Unit*> get_units_at(node_id_t node);

  /*
   * handles movement counters, then movement for all units
   */
  void do_movement_tick();

  /*
   * all units with the same location as another unit lose 1 health
   */
  void do_damage_tick();

  /*
   * Checks if monster healths are lower than player's kung-fu, and kills them if so
   */
  void do_monster_deaths();

  /*
   * Checks if player healths are lower than another unit's kung-fu, and kills them if so
   */
  void do_player_deaths();

  /*
   * returns 0 if no winner yet, 1 if player 1 wins, 2 if player 2 wins, or 3 if it's a tie (both players are dead)
   */
  int get_winner();

  // just for debugging
  void print_player_healths();

  void print_game();

  node_id_t get_hell_node_id();

private:
  struct Node {
    std::vector<node_id_t> adjacent;
    std::vector<Unit*> units;
  };

  std::vector<Node> _nodes;
  Player _player1;
  Player _player2;

  void do_monster_deaths(Player& p);
  void do_player_death(Player& p);
  void do_damage_tick(Node& n);
  void remove_unit(Node& n, Unit* unit);
  void add_unit(Node& n, Unit* unit);
};

# endif
