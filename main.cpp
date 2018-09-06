#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <streambuf>

#include "includes/json.hpp"
using json = nlohmann::json;

#include "Game.h"
#include "Unit.h"
#include "Monster.h"
#include "ScriptIO.h"

#define RESPONSE_SECS 1
#define RESPONSE_NSECS 0

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    cout << "not enough args. expected player1script, player2script, mapfile" << endl;
    return 1;
  }

  // initialize the player scripts
  start_scripts(argv[1], argv[2]);

  // get the map json string from the file (argv[3])
  ifstream t(argv[3]);
  string map_str;
  t.seekg(0, ios::end);
  map_str.reserve(t.tellg());
  t.seekg(0, ios::beg);

  map_str.assign((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

  // TODO: tell each player which player they are

  Game game = Game(map_str, "Player1", "Player2");

  /*Game game = Game(10, "Player1", "Player2");

  game.add_connection(0, 1);
  game.add_connection(1, 2);
  game.add_connection(2, 3);
  game.add_connection(3, 4);
  game.add_connection(4, 5);
  game.add_connection(5, 6);
  game.add_connection(0, 5);
  game.add_connection(0, 7);
  game.add_connection(7, 8);
  game.add_connection(7, 9);

  // add two-horned or eared or whatever monsters
  Monster m8("hard monster", 5, 0, 0, 8, Unit::DeathEffects(2, 0, 0, 2, 0));
  game.add_unit(&m8);

  Monster m9("hard monster", 5, 0, 0, 9, Unit::DeathEffects(2, 0, 0, 2, 0));
  game.add_unit(&m9);

  Monster m1("hard monster", 5, 0, 0, 1, Unit::DeathEffects(2, 0, 0, 2, 0));
  game.add_unit(&m1);

  Monster m2("hard monster", 5, 0, 0, 2, Unit::DeathEffects(2, 0, 0, 2, 0));
  game.add_unit(&m2);

  Monster m6("hard monster", 5, 0, 0, 6, Unit::DeathEffects(2, 0, 0, 2, 0));
  game.add_unit(&m6);

  // add one-horned monsters
  Monster m5("easy monster", 3, 0, 0, 5, Unit::DeathEffects(1, 0, 0, 3, 0));
  game.add_unit(&m5);

  Monster m7("easy monster", 3, 0, 0, 7, Unit::DeathEffects(1, 0, 0, 3, 0));
  game.add_unit(&m7);

  Monster m4("easy monster", 3, 0, 0, 4, Unit::DeathEffects(1, 0, 0, 3, 0));
  game.add_unit(&m4);

  // add speed monster
  Monster m3("speed monster", 0, 0, 0, 3, Unit::DeathEffects(0, 1, 0, 0, 0));
  game.add_unit(&m3);

  // add victory point monster
  Monster victory("victory point monster", 0, 0, -23, game.get_hell_node_id(), Unit::DeathEffects(0, 0, 0, 0, 1));
  victory.change_destination(0);
  game.add_unit(&victory);*/

  // Send initial map data to player scripts
  json map_data;
  ifstream mapStream(argv[3]);
  mapStream >> map_data;

  json message_map1 = {
    {"type", "map"},
    {"player_id", 1},
    {"map", map_data}
  };
  json message_map2 = {
    {"type", "map"},
    {"player_id", 2},
    {"map", map_data}
  };

  write_to_player(1, message_map1);
  write_to_player(2, message_map2);

  struct timespec sleepFor;
  sleepFor.tv_sec = RESPONSE_SECS;
  sleepFor.tv_nsec = RESPONSE_NSECS;

  string default_action = string("0 0");
  while (game.get_winner() == NO_WINNER) {
    int turn_number = 0;
    turn_number += 1;
    //game.print_game();

    json message_turn = {
      {"type", "turn"},
      {"turn_number", turn_number},
      {"game_data", game.to_json()},
    };

    write_to_player(1, message_turn);
    write_to_player(2, message_turn);
    nanosleep(&sleepFor, NULL);

    // get responses from players
    string* p1_buffer = read_from_player(1);
    string* p2_buffer = read_from_player(2);
    printf("Player1 sent %s, Player2 sent %s\n",
      p1_buffer ? p1_buffer->c_str() : "no response",
      p2_buffer ? p2_buffer->c_str() : "no response");

    Game::Decision p1_dec = Game::Decision(*p1_buffer);
    Game::Decision p2_dec = Game::Decision(*p2_buffer);
    cout << p1_dec.dest << p2_dec.dest;

    // run the game's turn based on the players' actions
    game.do_player_decisions(
      p1_buffer ? *p1_buffer : default_action,
      p2_buffer ? *p2_buffer : default_action);

    game.do_movement_tick();
    game.do_damage_tick();
    game.do_monster_deaths();
    game.do_player_deaths();

    if(p1_buffer) delete p1_buffer;
    if(p2_buffer) delete p2_buffer;
  }

  cout << "Winner: " << game.get_winner() << endl;

  return 0;
}
