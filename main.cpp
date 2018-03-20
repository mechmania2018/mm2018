#include <iostream>

#include "Game.h"
#include "Unit.h"
#include "Monster.h"

//TODO: add death effects

int main() {
  Game game = Game(10);

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
  Monster m8(5, 0, 0, 8, Unit::DeathEffects(2, 0, 0, 2, 0));
  game.add_unit(&m8);

  Monster m9(5, 0, 0, 9, Unit::DeathEffects(2, 0, 0, 2, 0));
  game.add_unit(&m9);

  Monster m1(5, 0, 0, 1, Unit::DeathEffects(2, 0, 0, 2, 0));
  game.add_unit(&m1);

  Monster m2(5, 0, 0, 2, Unit::DeathEffects(2, 0, 0, 2, 0));
  game.add_unit(&m2);

  Monster m6(5, 0, 0, 6, Unit::DeathEffects(2, 0, 0, 2, 0));
  game.add_unit(&m6);

  // add one-horned monsters
  Monster m5(3, 0, 0, 5, Unit::DeathEffects(1, 0, 0, 3, 0));
  game.add_unit(&m5);

  Monster m7(3, 0, 0, 7, Unit::DeathEffects(1, 0, 0, 3, 0));
  game.add_unit(&m7);

  Monster m4(3, 0, 0, 4, Unit::DeathEffects(1, 0, 0, 3, 0));
  game.add_unit(&m4);

  // add speed monster
  Monster m3(0, 0, 0, 3, Unit::DeathEffects(0, 1, 0, 0, 0));
  game.add_unit(&m3);

  // add victory point monster
  Monster victory(0, 0, -23, game.get_hell_node_id(), Unit::DeathEffects(0, 0, 0, 0, 1));
  victory.change_destination(0);
  game.add_unit(&victory);

  while (game.get_winner() == 0) {
    //TODO: get and do player decisions
    //std::cout << "Monster health: " << m.get_health() << std::endl;
    //std::cout << "Monster location: " << m.get_location() << std::endl;
    //std::cout << "Monster destination: " << m.get_destination() << std::endl;
    //game.print_player_healths();
    //std::cout << std::endl;

    game.do_movement_tick();
    game.do_damage_tick();
    game.do_monster_deaths();
    game.do_player_deaths();
  }

  std::cout << "Winner: " << game.get_winner() << std::endl;

  return 0;
}
