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

  // Send initial map data to player scripts

  json message_map1 = {
    {"type", "map"},
    {"player_id", 1},
    {"map", map_str}
  };

  json message_map2 = {
    {"type", "map"},
    {"player_id", 2},
    {"map", map_str}
  };

  write_to_player(1, message_map1);
  write_to_player(2, message_map2);

  struct timespec sleepFor;
  sleepFor.tv_sec = RESPONSE_SECS;
  sleepFor.tv_nsec = RESPONSE_NSECS;

  string default_action = string("00");
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

    // run the game's turn based on the players' actions
    game.do_player_decisions(p1_buffer->c_str(), p2_buffer->c_str());

    game.do_movement_tick();
    game.do_damage_tick();
    game.do_monster_deaths();
    game.do_player_deaths();

    if(p1_buffer) delete p1_buffer;
    if(p2_buffer) delete p2_buffer;
  }

  cout << "Winner: " << game.get_winner() << endl;

  terminate_scripts();

  return 0;
}
