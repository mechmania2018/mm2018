#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "Game.h"
#include "Unit.h"
#include "Monster.h"
#include "Manager.h"
#include "ScriptIO.h"

using namespace std;

#define RESPONSE_SECS 1
#define RESPONSE_NSECS 0

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "not enough args" << endl;
    return 1;
  }

  start_scripts(argv[1], argv[2]);

  // just some stuff for debugging player IO
  /*string s = read_from_player(1);
  cout << "Player 1 returned " << s << endl;
  write_to_player(1, "Test\n");
  cout << "Now player 1 returned " << read_from_player(1) << endl;*/

  // TODO: tell each player which player they are

  Game game = Game(10, "Player1", "Player2");

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
  game.add_unit(&victory);

  cout << game.to_json() << endl;



  // Set up manager threads
  pdata_t p1;
  init_pdata(&p1, 1);

  pdata_t p2;
  init_pdata(&p2, 2);

  pthread_create(&p1.thread, NULL, manage_player, &p1);
  pthread_create(&p2.thread, NULL, manage_player, &p2);

  struct timespec sleepFor;
  sleepFor.tv_sec = RESPONSE_SECS;
  sleepFor.tv_nsec = RESPONSE_NSECS;

  string default_action = "0 0";

  while (game.get_winner() == 0) {
    // game.print_game();
    // get decisions from players
    string json = game.to_json() + "\n";

    pthread_mutex_lock(&p1.m);
    p1.state = Writing;
    p1.buffer = new string(json);
    pthread_cond_signal(&p1.cv);
    pthread_mutex_unlock(&p1.m);

    pthread_mutex_lock(&p2.m);
    p2.state = Writing;
    p2.buffer = new string(json);
    pthread_cond_signal(&p2.cv);
    pthread_mutex_unlock(&p2.m);


    pthread_mutex_lock(&p1.m);
    // We don't need the JSON data anymore
    delete p1.buffer;
    p1.buffer = NULL;
    p1.state = Reading;
    pthread_cond_signal(&p1.cv);
    pthread_mutex_unlock(&p1.m);

    pthread_mutex_lock(&p2.m);
    delete p2.buffer;
    p2.buffer = NULL;
    p2.state = Reading;
    pthread_cond_signal(&p2.cv);
    pthread_mutex_unlock(&p2.m);

    // Wait for player threads to send responses, then have both threads idle again
    nanosleep(&sleepFor, NULL);
    pthread_mutex_lock(&p1.m);
    pthread_mutex_lock(&p2.m);
    p1.state = Idle;
    p2.state = Idle;
    printf("Player1 sent %s, Player2 sent %s\n", p1.buffer ? p1.buffer->c_str() : "no response", p2.buffer ? p2.buffer->c_str() : "no response");
    game.do_player_decisions(p1.buffer ? *p1.buffer : default_action, p2.buffer ? *p2.buffer : default_action);
	pthread_mutex_unlock(&p2.m);
	pthread_mutex_unlock(&p1.m);

    game.do_movement_tick();
    game.do_damage_tick();
    game.do_monster_deaths();
    game.do_player_deaths();
  }

  cout << "Winner: " << game.get_winner() << endl;

  return 0;
}
