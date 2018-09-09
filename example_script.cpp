#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "Game_Api.h"
#include "includes/json.hpp"
using json = nlohmann::json;

#define RESPONSE_SECS 1
#define RESPONSE_NSECS 0

#include <iostream>
using namespace std;

int main() {
	Game_Api * api;
	int my_player_num = 0;
	while(1){
		char* buf = NULL;
		size_t size = 0;

		getline(&buf, &size, stdin);
		json data = json::parse(buf);

		if(data["type"] == "map"){
			api = new Game_Api(1, data["map"]);
			my_player_num = data["player_id"];
		} else {
			 api->update(data["game_data"]);
			 if (my_player_num == 1) {
				 cerr << "player 1 destination: " << api->all_units[0]._destination << "\n";
				 cerr << "player 1 location: " << api->all_units[0]._location << "\n";
			 }
			 string decision = "0";
			 string adjacent = api->get_adjacent_nodes(my_player_num);

			 if (api->all_units[0]._location == 1) {
				 decision += adjacent[1];
			 }else {
				 decision += adjacent[0];
			 }
			 printf("%s\n", decision.c_str());
		 	 fflush(stdout);
		}

		free(buf);
	}
}
