#include <iostream>
#include <string>

#include "Game.h"

using namespace std;

Game::Game(int size, string p1_name, string p2_name) : _player1(p1_name), _player2(p2_name){
  for (node_id_t i = 0; i < size + 1; i ++) {
    _nodes.push_back(Node());
  }

  add_unit(_nodes[0], &_player1);
  add_unit(_nodes[0], &_player2);
}

void Game::add_connection(node_id_t node1, node_id_t node2){
  _nodes[node1].adjacent.push_back(node2);
  _nodes[node2].adjacent.push_back(node1);
}

void Game::add_unit(Unit* u){
  add_unit(_nodes[u->get_location()], u);
  all_units.push_back(u);
}

vector<node_id_t> Game::get_adjacent_nodes(node_id_t node){
  return _nodes[node].adjacent;
}

vector<Unit*> Game::get_units_at(node_id_t node){
  return _nodes[node].units;
}

void Game::do_player_decisions(string player1_decision, string player2_decision) {
  _player1.do_decision(_nodes[_player1.get_location()].adjacent, player1_decision);
  _player2.do_decision(_nodes[_player2.get_location()].adjacent, player2_decision);
}

string Game::process_player_requests(string player_requests, int player_num) {
  string response = "";
  for (char c : player_requests) {
    if (c == 'n') {
      response += "157";
    }
    else if (c == 'h') {
      response += "20";
    }
    else if (c == 'z') {
      response += "";
    }
  }
  return response;
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
      if (_player1.get_location() == u->get_location())
      {
        _player1.activate_death_effects(u->get_death_effects());
      }

      if (_player2.get_location() == u->get_location())
      {
        _player2.activate_death_effects(u->get_death_effects());
      }

      // Monster u is dead
      u->die(get_hell_node_id());
      remove_unit(_nodes[p.get_location()], u);
      add_unit(_nodes[get_hell_node_id()], u);
    }
  }
}

void Game::do_player_deaths(){
  bool p1_dies = will_player_die(_player1);
  bool p2_dies = will_player_die(_player2);

  if (p1_dies) {
    _player1.die(get_hell_node_id());
    remove_unit(_nodes[_player1.get_location()], &_player1);
    add_unit(_nodes[get_hell_node_id()], &_player1);
  }

  if (p2_dies) {
    _player2.die(get_hell_node_id());
    remove_unit(_nodes[_player2.get_location()], &_player2);
    add_unit(_nodes[get_hell_node_id()], &_player2);
  }
}

bool Game::will_player_die(Player& p){
  if (p.get_location() == get_hell_node_id()) return false;

  for (Unit* u : _nodes[p.get_location()].units) {
    if (u != &p && u->get_kung_fu() > p.get_health()) {
      return true;
    }
  }

  return false;
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

void Game::print_game() {
  for (unsigned i = 0; i < _nodes.size() - 1; i ++) {
    cout << "Node " << i << endl;

    for (Unit* u : _nodes[i].units) {
      cout << u->get_string() << endl;
    }

    cout << endl;
  }
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

std::string Game::to_json() {

  json state;

  state += _player1.to_json();
  state += _player2.to_json();

  for (size_t i = 0; i < all_units.size(); i++) {
    state += all_units[i]->to_json();

  }
  string ret = state.dump();
  return ret;
}
