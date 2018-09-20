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

#define SLEEP_SECS 0
#define SLEEP_NSECS 100000000
#define SLEEPS_PER_TURN 10

#define CONFINE_TURN_NUMBER 30

static int startup_sleep = 3;

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 4) {
    cerr << "not enough args. expected player1script, player2script, mapfile" << endl;
    return 1;
  } else if (argc == 5) {
    startup_sleep = atoi(argv[4]);
  }

  // initialize the player scripts
  start_scripts(argv[1], argv[2]);

  struct timespec startupSleep;
  startupSleep.tv_sec = startup_sleep;
  startupSleep.tv_nsec = 0;
  nanosleep(&startupSleep, NULL);

  // get the map json string from the file (argv[3])
  ifstream t(argv[3]);
  string map_str;
  t.seekg(0, ios::end);
  map_str.reserve(t.tellg());
  t.seekg(0, ios::beg);

  map_str.assign((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

  Game game = Game(map_str, "Player1", "Player2");

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

  int turn_number = 0;

  struct timespec sleepFor;
  sleepFor.tv_sec = SLEEP_SECS;
  sleepFor.tv_nsec = SLEEP_NSECS;

  while (game.get_winner() == NO_WINNER) {
    turn_number += 1;

    cout << game.to_json() << endl;
    //cout << "-----Turn " << turn_number << "-----" << endl;
    //game.print_game();

    json message_turn = {
      {"type", "turn"},
      {"turn_number", turn_number},
      {"game_data", game.to_json()},
    };

    write_to_player(1, message_turn);
    write_to_player(2, message_turn);

    // get responses from players
    Player::Decision p1_dec("");
    Player::Decision p2_dec("");
    string p1_reply = "";
    string p2_reply = "";

    int sleeps_done = 0;
    bool got_valid_p1_decision = false;
    bool got_valid_p2_decision = false;
    while (sleeps_done < SLEEPS_PER_TURN && (!got_valid_p1_decision || !got_valid_p2_decision)) {
      nanosleep(&sleepFor, NULL);
      if (!got_valid_p1_decision) {
        p1_reply += read_from_player(1);
        p1_dec = Player::Decision(p1_reply);
        got_valid_p1_decision = p1_dec.is_valid();
      }

      if (!got_valid_p2_decision) {
        p2_reply += read_from_player(2);
        p2_dec = Player::Decision(p2_reply);
        got_valid_p2_decision = p2_dec.is_valid();
      }

      sleeps_done ++;
    }

    if (!got_valid_p1_decision) {
      cerr << "Invalid response from Player1: " << p1_reply << endl;
    }

    if (!got_valid_p2_decision) {
      cerr << "Invalid response from Player2: " << p2_reply << endl;
    }

    // run the game's turn based on the players' actions
    game.do_player_decisions(p1_dec, p2_dec);

    if (turn_number < CONFINE_TURN_NUMBER){
      game.do_movement_tick();
    } else if (turn_number == CONFINE_TURN_NUMBER){
      game.move_players_to_start();
    }

    game.do_damage_tick();
    game.do_monster_deaths();
    game.do_player_deaths();
  }

  json j;
  j["Winner"] = game.get_winner();
  cout << j.dump() << endl;

  terminate_scripts();

  return 0;
}
