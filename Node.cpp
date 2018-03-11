#include "Node.h"

Node::Node(node_id_t id, std::map<node_id_t, Node*>* map) {
  this->id = id;
  this->id_map = map;
}

std::vector<node_id_t> Node::get_adjacent() {
  return adjacent;
}

void Node::add_adjacent(node_id_t other){
  adjacent.push_back(other);
}

std::vector<Unit*> Node::get_units() {
  return units;
}

void Node::add_unit(Unit* unit) {
  units.push_back(unit);
}

void Node::remove_unit(Unit* unit) {
  for (unsigned i = 0; i < units.size(); i ++){
    if (units[i] == unit) {
      units.erase(units.begin() + i);
      return;
    }
  }
}

void Node::do_movement_tick() {
  for (unsigned i = 0; i < units.size(); i ++){
    Unit* u = units[i];

    if (u->do_movement_tick()) {
      units.erase(units.begin() + i);
      (*id_map)[u->get_destination()]->add_unit(u);
    }
  }
}

void Node::do_damage_tick() {
  if (units.size() > 1) {
    for (Unit* u : units) {
      u->take_damage();
    }
  }
}
