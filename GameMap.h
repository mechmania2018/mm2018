# ifndef GAME_MAP_H
# define GAME_MAP_H

#include <vector>

typedef int node_t;

class GameMap{
public:
  GameMap(int num_nodes);

  //void set_connected(node_t node1, node_t node2);
  std::vector<node_t> get_adjacent_nodes(node_t node);

private:
  int size;
  std::vector<std::vector<node_t>> adjacency_list;
};

# endif
