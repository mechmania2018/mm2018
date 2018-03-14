# ifndef GAME_MAP_H
# define GAME_MAP_H

#include <map>
#include <vector>

#include "Node.h"
#include "Unit.h"
#include "Player.h"
#include "types.h"

class Game{
public:
  Game(int num_nodes);

  /*
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

  void do_monster_deaths();

  /*
   * returns 0 if no winner yet, 1 if player 1 wins, 2 if player 2 wins, or 3 if it's a tie (both players are dead)
   */
  int get_winner();

private:
  std::vector<Node> nodes;
  Node hell;
  std::map<node_id_t, Node*> node_id_map;
  Player player1;
  Player player2;

  void do_monster_deaths(Player& p);
};

# endif