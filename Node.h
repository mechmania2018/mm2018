#ifndef _NODE_H
#define _NODE_H

#include <vector>
#include <map>

#include "Unit.h"

class Node {
public:
  Node(node_id_t id, std::map<node_id_t, Node*>* map);

  std::vector<node_id_t> get_adjacent();
  void add_adjacent(node_id_t other);

  std::vector<Unit*> get_units();
  void add_unit(Unit* unit);
  void remove_unit(Unit* unit);

  void do_movement_tick();
  void do_damage_tick();

private:
  node_id_t id;
  std::map<node_id_t, Node*>* id_map;
  std::vector<node_id_t> adjacent;
  std::vector<Unit*> units;
};

#endif
