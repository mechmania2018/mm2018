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

  void add_connection(node_id_t node1, node_id_t node2);
  void add_unit(Unit* u, node_id_t location);

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

private:
  std::vector<Node> nodes;
  std::map<node_id_t, Node*> node_id_map;
  //Player* player1;
  //Player* player2;
};

# endif
