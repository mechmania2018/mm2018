#include <iostream>

#include "Game.h"
#include "Monster.h"

void setup_game(Game& game) {
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
}

int main() {
  Game game = Game(10);
  setup_game(game);

  Monster m(5, 0, 0, 0);
  game.add_unit(&m);

  while (game.get_winner() == 0) {
    // TODO: get and do player decisions
    game.do_movement_tick();
    game.do_damage_tick();
    game.do_monster_deaths();
  }

  return 0;
}
