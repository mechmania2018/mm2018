#include <iostream>

#include "Game.h"

Game::Game(int size) {
  for (node_id_t i = 0; i < size + 1; i ++) {
    _nodes.push_back(Node());
  }

  _player1.change_destination(1); // just for debugging
  _player2.change_destination(1); // just for debugging

  add_unit(_nodes[0], &_player1);
  add_unit(_nodes[0], &_player2);
}

void Game::add_connection(node_id_t node1, node_id_t node2){
  _nodes[node1].adjacent.push_back(node2);
  _nodes[node2].adjacent.push_back(node1);
}

void Game::add_unit(Unit* u){
  add_unit(_nodes[u->get_location()], u);
}

std::vector<node_id_t> Game::get_adjacent_nodes(node_id_t node){
  return _nodes[node].adjacent;
}

std::vector<Unit*> Game::get_units_at(node_id_t node){
  return _nodes[node].units;
}

void Game::do_movement_tick(){
  for (Node &n : _nodes) {
    for (int i = n.units.size() - 1; i >= 0; i --){
      Unit* u = n.units[i];

      u->decrement_movement_counter();
      if (u->time_to_move()) {
        u->reset_movement_counter();
        remove_unit(n, u);
        add_unit(_nodes[u->get_destination()], u);
        u->set_location(u->get_destination());
      }
    }
  }
}

void Game::do_damage_tick(){
  if (_player1.get_location() != get_hell_node_id()) {
    do_damage_tick(_nodes[_player1.get_location()]);
  }

  if (_player1.get_location() != _player2.get_location() && _player2.get_location() != get_hell_node_id()) {
    do_damage_tick(_nodes[_player2.get_location()]);
  }
}

void Game::do_monster_deaths(){
  do_monster_deaths(_player1);
  do_monster_deaths(_player2);
}

void Game::do_monster_deaths(Player& p) {
  if (p.get_location() == get_hell_node_id()) return;

  for (Unit* u : _nodes[p.get_location()].units) {
    if (u->is_monster() && u->get_health() <= p.get_kung_fu()) {
      u->die(get_hell_node_id());
      remove_unit(_nodes[p.get_location()], u);
      add_unit(_nodes[get_hell_node_id()], u);
    }
  }
}

void Game::do_player_deaths(){
  do_player_death(_player1);
  do_player_death(_player2);
}

void Game::do_player_death(Player& p){
  if (p.get_location() == get_hell_node_id()) return;

  for (Unit* u : _nodes[p.get_location()].units) {
    if (u->get_kung_fu() > p.get_health()) {
      p.die(get_hell_node_id());
      remove_unit(_nodes[p.get_location()], &p);
      add_unit(_nodes[get_hell_node_id()], &p);
      break;
    }
  }
}

int Game::get_winner() {
  if (_player1.get_num_victory_points() > _player2.get_num_victory_points()) {
    return 1;
  } else if (_player2.get_num_victory_points() > _player1.get_num_victory_points()) {
    return 2;
  } else if (_player1.get_location() == get_hell_node_id() && _player2.get_location() == get_hell_node_id()) {
    return 3;
  }
  return 0;
}

void Game::print_player_healths() {
  std::cout << "Player 1 health: " << _player1.get_health() << std::endl;
  std::cout << "Player 1 location: " << _player1.get_location() << std::endl;
  std::cout << "Player 2 health: " << _player2.get_health() << std::endl;
  std::cout << "Player 2 location: " << _player2.get_location() << std::endl;
}

void print_game() {
  //TODO
}

int Game::get_hell_node_id() {
  return _nodes.size() - 1;
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
