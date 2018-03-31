#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "Game.h"
#include "Unit.h"
#include "Monster.h"

void start_script(char* name, int pipe_to[2], int pipe_from[2]) {
  pid_t child_id = fork();

  if (!child_id) {
    // Child Process

    /* dup pipe read/write to stdin/stdout */
    dup2( pipe_to[0], STDIN_FILENO );
    dup2( pipe_from[1], STDOUT_FILENO  );
    /* close unnecessary pipe descriptors for a clean environment */
    close( pipe_to[0] );
    close( pipe_to[1] );
    close( pipe_from[0] );
    close( pipe_from[1] );

    execlp(name, name, NULL);
    exit(1);
  }

  // Parent Process
  close(pipe_to[0]);
  close(pipe_from[1]);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "not enough args" << std::endl;
  }

  int pipe_to_p1[2];
  if (pipe(pipe_to_p1)) {
    perror("pipe_to_p1");
    exit(1);
  }

  int pipe_from_p1[2];
  if (pipe(pipe_from_p1)) {
    perror("pipe_from_p1");
    exit(1);
  }

  start_script(argv[1], pipe_to_p1, pipe_from_p1);

  int pipe_to_p2[2];
  if (pipe(pipe_to_p2)) {
    perror("pipe_to_p2");
    exit(1);
  }

  int pipe_from_p2[2];
  if (pipe(pipe_from_p2)) {
    perror("pipe_from_p2");
    exit(1);
  }

  start_script(argv[2], pipe_to_p2, pipe_from_p2);

  FILE* stream = fdopen(pipe_from_p1[0], "r");
  char* buff = NULL;
  size_t size = 0;
  getline(&buff, &size, stream);

  std::cout << buff << std::endl;

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
  Monster m3("sped monster", 0, 0, 0, 3, Unit::DeathEffects(0, 1, 0, 0, 0));
  game.add_unit(&m3);

  // add victory point monster
  Monster victory("victory point monster", 0, 0, -23, game.get_hell_node_id(), Unit::DeathEffects(0, 0, 0, 0, 1));
  victory.change_destination(0);
  game.add_unit(&victory);

  while (game.get_winner() == 0) {
    game.print_game();
    game.do_player_decisions();
    game.do_movement_tick();
    game.do_damage_tick();
    game.do_monster_deaths();
    game.do_player_deaths();
  }

  std::cout << "Winner: " << game.get_winner() << std::endl;

  return 0;
}
