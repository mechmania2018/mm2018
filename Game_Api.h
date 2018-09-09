//
// Created by alvar on 9/1/2018.
//

#ifndef GAME_API_GAME_API_H
#define GAME_API_GAME_API_H
#include "includes/json.hpp"

#define BASE_MOVEMENT_COUNTER 7
#define INIT_PLAYER_HEALTH 10

using std::string;
using std::vector;
using json = nlohmann::json;

typedef int node_id_t;
class Game_Api {

private:
    struct Unit { //make everything const
        Unit(string name, int h, int k, int s, node_id_t loc, Game_Api* api);
        void update(json unit_json);
        string _name;
        int _health;
        int _kung_fu;
        int _speed;
        int _movement_counter;
        node_id_t _location;
        node_id_t _destination;
        int _exp;
        int _victory_points;
        Game_Api* _api;
    };

    struct Node {
        vector<node_id_t> adjacent;
        vector<Unit*> units;
    };

public:
    Unit * _player1; //0th unit in all_units
    Unit * _player2; //1st unit in all_units
    vector<Unit> all_units; //doesnt include players
    vector<Node> nodes;
    explicit Game_Api(int i, string json_str);
    void update(json json_str);
    void print();
    string get_adjacent_nodes(int player_number);
    string get_path_nearest_powerup(string powerup_name); //powerup_name refers to 'type' of powerup
    string get_path_nearest_monster(string monster_name); //'type' of monster
    string get_path_other_player(); //shortest path
    string get_path_node(node_id_t node); //shortest path

};


#endif //MM2018_GAME_LOGIC_GAME_API_H
