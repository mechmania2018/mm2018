#include "Game.h"

Game::Game(int size) :
  hell(HELL_NODE_ID, &node_id_map) {
  node_id_map[HELL_NODE_ID] = &hell;

  for (node_id_t i = 0; i < size + 1; i ++) {
    nodes.push_back(Node(i, &node_id_map));
    node_id_map[i] = &nodes[i];
  }

  nodes[0].add_unit(&player1);
  nodes[0].add_unit(&player2);
}

void Game::add_connection(node_id_t node1, node_id_t node2){
  nodes[node1].add_adjacent(node2);
  nodes[node2].add_adjacent(node1);
}

void Game::add_unit(Unit* u){
  nodes[u->get_location()].add_unit(u);
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
  hell.do_movement_tick();
}

void Game::do_damage_tick(){
  nodes[player1.get_location()].do_damage_tick();

  if (player1.get_location() != player2.get_location()) {
    nodes[player2.get_location()].do_damage_tick();
  }
}

void Game::do_monster_deaths(){
  do_monster_deaths(player1);
  do_monster_deaths(player2);
}

void Game::do_monster_deaths(Player& p) {
  for (Unit* u : nodes[p.get_location()].get_units()) {
    if (u->is_monster() && u->get_health() <= p.get_kung_fu()) {
      u->die();
    }
  }
}

int Game::get_winner() {
  if (player1.get_num_victory_points() > player2.get_num_victory_points()) {
    return 1;
  } else if (player2.get_num_victory_points() > player1.get_num_victory_points()) {
    return 2;
  }

  return 0;
}
