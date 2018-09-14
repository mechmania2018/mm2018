#include <iostream>
#include <string>

#include "json.hpp"
#include "Unit.h"
#include "Monster.h"
#include "Game.h"

using json = nlohmann::json;
using namespace std;

Game::Game(string json_str, string p1_name, string p2_name): _player1(p1_name), _player2(p2_name) {
  json::basic_json map = json::parse(json_str);

  json::basic_json nodes_json = map["Nodes"];
  json::basic_json edges = map["Edges"];
  json::basic_json monsters_json = map["Monsters"];

  // create each of the nodes in the map
  while (_nodes.size() < nodes_json.size()) {
    _nodes.push_back(Node());
  }

  // add each player to node 0
  add_unit_to_node(_nodes[0], &_player1);
  add_unit_to_node(_nodes[0], &_player2);

  // add adjacent edges to each node
  for (json::basic_json edge : edges) {
    json::basic_json adj = edge["Adjacents"];
    add_connection(adj[0], adj[1]);
  }

  // create each of the monsters
  num_monsters = monsters_json.size();

  _monsters = new Monster[num_monsters];
  for (size_t i = 0; i < num_monsters; i ++){
    Monster mon(monsters_json[i]);
    _monsters[i] = mon;

    // add each monster to its respective node
    Monster* m = &(_monsters[i]);
    add_unit_to_node(_nodes[m->get_location()], m);
  }
}

Game::~Game(){
  delete[] _monsters;
}

void Game::add_connection(node_id_t node1, node_id_t node2){
  _nodes[node1].adjacent.push_back(node2);
  _nodes[node2].adjacent.push_back(node1);
}

vector<node_id_t> Game::get_adjacent_nodes(node_id_t node){
  return _nodes[node].adjacent;
}

vector<Unit*> Game::get_units_at(node_id_t node){
  return _nodes[node].units;
}

void Game::do_player_decisions(string dec1_str, string dec2_str) {
  do_player_decision(_player1, dec1_str);
  do_player_decision(_player2, dec2_str);
}

void Game::do_player_decision(Player& player, string decision) {
  Player::Decision dec(decision);

  Node location = _nodes[player.get_location()];

  bool valid_dest = (dec.dest == player.get_location());

  for (int i : get_adjacent_nodes(player.get_location())) {
    if (i == dec.dest) valid_dest = true;
  }

  if (!valid_dest) {
    cerr << "Player " << player.get_name() << " attempted to set destination to invalid node:" << dec.dest << endl;
    dec.dest = player.get_location();
  }

  player.do_decision(dec);
}

void Game::do_movement_tick(){
  for (Node &n : _nodes) {
    for (int i = n.units.size() - 1; i >= 0; i --){
      Unit* u = n.units[i];

      u->decrement_movement_counter();
      if (u->time_to_move()) {
        u->reset_movement_counter();
        remove_unit_from_node(n, u);
        add_unit_to_node(_nodes[u->get_destination()], u);
        u->set_location(u->get_destination());
      }
    }
  }
}

void Game::do_damage_tick(){
  for (Node& n : _nodes) {
    if (n.units.size() > 1) {
      for (Unit* u1 : n.units) {
        if (!u1->dead()) {
          for (Unit* u2 : n.units) {
            if (u1 != u2 && !u2->dead()) {
              u1->attack(u2);
            }
          }
        }
      }
    }
  }
}

void Game::do_monster_deaths(){
  for (node_id_t node_id = 0; node_id < (node_id_t)_nodes.size(); node_id ++) {
    for (Unit* u : _nodes[node_id].units) {
      if (u->is_monster() && !u->dead() && u->get_health() <= 0) {
        if (_player1.get_location() == node_id) {
          _player1.activate_death_effects(u->get_death_effects());
        }

        if (_player2.get_location() == node_id) {
          _player2.activate_death_effects(u->get_death_effects());
        }

        u->die();
      }
    }
  }
}

void Game::do_player_deaths(){
  // do checks before taking any action so that the turn order doesn't matter
  bool p1_dies = will_player_die(_player1);
  bool p2_dies = will_player_die(_player2);

  if (p1_dies) {
    _player1.die();
  }

  if (p2_dies) {
    _player2.die();
  }
}

bool Game::will_player_die(Player& p){
  if (p.dead()) return false;
  return (p.get_health() <= 0);
}

int Game::get_winner() {
  if (_player1.dead() && _player2.dead()) {
    return TIED_GAME;
  } else if (_player1.dead()) {
    return P2_WINS;
  } else if (_player2.dead()) {
    return P1_WINS;
  }
  return NO_WINNER;
}

void Game::print_game() {
  for (unsigned i = 0; i < _nodes.size(); i ++) {
    if (_nodes[i].units.size() > 0){
      cout << "Node " << i << endl;

      for (Unit* u : _nodes[i].units) {
        cout << u->get_string() << endl;
      }

      cout << endl;
    }
  }
  cout << endl;
}

void Game::remove_unit_from_node(Node& n, Unit* unit) {
  for (unsigned i = 0; i < n.units.size(); i ++) {
    if (n.units[i] == unit) {
      n.units.erase(n.units.begin() + i);
      return;
    }
  }
}

void Game::add_unit_to_node(Node& n, Unit* unit) {
  n.units.push_back(unit);
}

json Game::to_json() {
  json state;

  state += _player1.to_json();
  state += _player2.to_json();

  for (size_t i = 0; i < num_monsters; i++) {
    state += _monsters[i].to_json();
  }

  return state;
}

void Game::move_players_to_start() {
  if (_player1.get_location() != 0) {
    _player1.set_location(0);
    remove_unit_from_node(_nodes[_player1.get_location()], &_player1);
    add_unit_to_node(_nodes[0], &_player1);
  }

  if (_player2.get_location() != 0) {
    _player2.set_location(0);
    remove_unit_from_node(_nodes[_player2.get_location()], &_player2);
    add_unit_to_node(_nodes[0], &_player2);
  }
}
