#include <iostream>

#include "Game.h"

Game::Game(int size) {
  for (node_id_t i = 0; i < size + 1; i ++) {
    nodes.push_back(Node());
  }

  player1.set_destination(1);
  player2.set_destination(1);

  add_unit(nodes[0], &player1);
  add_unit(nodes[0], &player2);
}

void Game::add_connection(node_id_t node1, node_id_t node2){
  nodes[node1].adjacent.push_back(node2);
  nodes[node2].adjacent.push_back(node1);
}

void Game::add_unit(Unit* u){
  add_unit(nodes[u->get_location()], u);
}

std::vector<node_id_t> Game::get_adjacent_nodes(node_id_t node){
  return nodes[node].adjacent;
}

std::vector<Unit*> Game::get_units_at(node_id_t node){
  return nodes[node].units;
}

void Game::do_movement_tick(){
  for (Node &n : nodes) {
    for (int i = n.units.size() - 1; i >= 0; i --){
      Unit* u = n.units[i];

      if (u->do_movement_tick()) {
        remove_unit(n, u);
        add_unit(nodes[u->get_location()], u);
      }
    }
  }
}

void Game::do_damage_tick(){
  if (player1.get_location() != get_hell_node_id()) {
    do_damage_tick(nodes[player1.get_location()]);
  }

  if (player1.get_location() != player2.get_location() && player2.get_location() != get_hell_node_id()) {
    do_damage_tick(nodes[player2.get_location()]);
  }
}

void Game::do_monster_deaths(){
  do_monster_deaths(player1);
  do_monster_deaths(player2);
}

void Game::do_monster_deaths(Player& p) {
  if (p.get_location() == get_hell_node_id()) return;

  for (Unit* u : nodes[p.get_location()].units) {
    if (u->is_monster() && u->get_health() <= p.get_kung_fu()) {
      u->die(get_hell_node_id());
      remove_unit(nodes[p.get_location()], u);
      add_unit(nodes[get_hell_node_id()], u);
    }
  }
}

void Game::do_player_deaths(){
  do_player_death(player1);
  do_player_death(player2);
}

void Game::do_player_death(Player& p){
  if (p.get_location() == get_hell_node_id()) return;

  for (Unit* u : nodes[p.get_location()].units) {
    if (u->get_kung_fu() > p.get_health()) {
      p.die(get_hell_node_id());
      remove_unit(nodes[p.get_location()], &p);
      add_unit(nodes[get_hell_node_id()], &p);
      break;
    }
  }
}

int Game::get_winner() {
  if (player1.get_num_victory_points() > player2.get_num_victory_points()) {
    return 1;
  } else if (player2.get_num_victory_points() > player1.get_num_victory_points()) {
    return 2;
  } else if (player1.get_location() == get_hell_node_id() && player2.get_location() == get_hell_node_id()) {
    return 3;
  }
  return 0;
}

void Game::print_player_healths() {
  std::cout << "Player 1 health: " << player1.get_health() << std::endl;
  std::cout << "Player 1 location: " << player1.get_location() << std::endl;
  std::cout << "Player 2 health: " << player2.get_health() << std::endl;
  std::cout << "Player 2 location: " << player2.get_location() << std::endl;
}

int Game::get_hell_node_id() {
  return nodes.size() - 1;
}

void Game::do_damage_tick(Node& n) {
  if (n.units.size() > 1) {
    for (Unit* u : n.units) {
      u->take_damage();
    }
  }
}

void Game::remove_unit(Node& n, Unit* unit) {
  for (unsigned i = 0; i < n.units.size(); i ++) {
    if (n.units[i] == unit) {
      n.units.erase(n.units.begin() + i);
      return;
    }
  }
}

void Game::add_unit(Node& n, Unit* unit) {
  n.units.push_back(unit);
}
