//
// Created by alvar on 9/1/2018.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "Game_Api.h"
using std::cout;

Game_Api::Unit::Unit(string name, int h, int k, int s, node_id_t loc, Game_Api* api) {
    this->_api = api;
    this->_name = name;
    this->_health = h;
    this->_kung_fu = k;
    this->_speed = s;
    this->_location = loc;
    this->_destination = loc;
    this->_movement_counter = BASE_MOVEMENT_COUNTER;
    this->_exp = 0; //only player exp changes. monster stay at 0
    this->_victory_points = 0; //same as above
}

void Game_Api::Unit::update(json unit_json) {
    //remove unit from previous location in case it has moved
    if (unit_json["Location"] != this->_location) {
      std::cerr << "location changed" << "\n";
        Node& prev_location = _api->nodes[_location];
        for (unsigned i = 0; i < prev_location.units.size(); i++) {
            if (prev_location.units[i] == this) {
                prev_location.units.erase(prev_location.units.begin() + i);
            }
        }
        _location = unit_json["Location"];
        _api->nodes[_location].units.push_back(this);
    }
    _name = unit_json["Name"];
    _health = unit_json["Health"];
    _kung_fu = unit_json["Kung_fu"];
    _speed = unit_json["Speed"];
    _destination = unit_json["Destination"];
    _movement_counter = unit_json["Movement_counter"];

    //missing exp and victory points
}

Game_Api::Game_Api(int i, string json_string) {
    i = 0;
    json::basic_json map = json::parse(json_string);
    json::basic_json nodes_json = map["Nodes"];
    json::basic_json edges_json = map["Edges"];
    json::basic_json monsters_json = map["Monsters"];

    for (node_id_t i = 0; i < (int)nodes_json.size(); i++) {
        nodes.push_back(Node());
    }
    nodes.push_back(Node());// add hell

    Unit player1("player1", INIT_PLAYER_HEALTH, 0, 0, 0, this);
    Unit player2("player2", INIT_PLAYER_HEALTH, 0, 0, 0, this);
    all_units.push_back(player1);
    all_units.push_back(player2);
    _player1 = &(all_units[0]);
    _player2 = &(all_units[1]);

    nodes[0].units.push_back(&player1);
    nodes[0].units.push_back(&player2);

    for (json::basic_json edge : edges_json) {
        json::basic_json adj = edge["Adjacents"];
        nodes[adj[0]].adjacent.push_back(adj[1]);
        nodes[adj[1]].adjacent.push_back(adj[0]);
    }

    for (json::basic_json mon : monsters_json) {
        Unit monster(mon["Name"], mon["Health"], mon["Kung_fu"], mon["Speed"], mon["Location"], this);
        all_units.push_back(monster);
    }

    for (unsigned i = 0; i < all_units.size(); i ++) {
        Unit* m = &(all_units[i]);
        nodes[m->_location].units.push_back(m);
    }
    //print();
}

void Game_Api::print() {
    for (Unit unit : all_units) {
        std::cerr << unit._name << "\n";
        std::cerr << unit._location << "\n";
        std::cerr << unit._destination << "\n";
    }
    int idx = 0;
    for (Node node : nodes) {
        for (node_id_t i : node.adjacent) {
            std::cerr << "Node " << idx << " adjacent: " << i << "\n";
        }
        for (Unit* unit : node.units) {
            std::cerr << "This node contains: " << unit->_name << "\n";
        }
        idx++;
    }
}

void Game_Api::update(json json_string) {
    for (unsigned i = 0; i < all_units.size(); i++) {
          all_units[i].update(json_string[i]);
    }
}

string Game_Api::get_adjacent_nodes(int player_number) {
  string response = "";
  node_id_t player_location = all_units[(player_number-1)]._location;
  for (node_id_t node_id : nodes[player_location].adjacent) {
    response += std::to_string(node_id);
  }
  return response;
}

// string Game_Api::get_path_nearest_powerup(string powerup_name) {
//
// }
//
// string Game_Api::get_path_nearest_monster(string monster_name) {
//
// }
//
// string Game_Api::get_path_other_player() {
//
// }
//
// string Game_Api::get_path_node(node_id_t node) {
//
// }
