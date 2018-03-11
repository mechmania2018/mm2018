#include "Game.h"

Game::Game(int size) {
  for (node_id_t i = 0; i < size; i ++) {
    nodes.push_back(Node(i, &node_id_map));
    node_id_map[i] = &nodes[i];
  }
}

void Game::add_connection(node_id_t node1, node_id_t node2){
  nodes[node1].add_adjacent(node2);
  nodes[node2].add_adjacent(node1);
}

void Game::add_unit(Unit* u, node_id_t location){
  nodes[location].add_unit(u);
}

std::vector<node_id_t> Game::get_adjacent_nodes(node_id_t node){
  return nodes[node].get_adjacent();
}

std::vector<Unit*> Game::get_units_at(node_id_t node){
  return nodes[node].get_units();
}

void Game::do_movement_tick(){
  for (Node n : nodes) {
    n.do_movement_tick();
  }
}

void Game::do_damage_tick(){
  for (Node n : nodes) {
    n.do_damage_tick();
  }
}
