#include "GameMap.h"

GameMap::GameMap(int num_nodes) {
  this->size = num_nodes;

  this->adjacency_list = std::vector<std::vector<node_t>>();

  for (int i = 0; i < num_nodes; i ++){
    this->adjacency_list.push_back(std::vector<node_t>());
  }
}

//void GameMap::set_connected(node_t node1, node_t node2){

//}
