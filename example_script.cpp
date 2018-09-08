#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
//#include "Game_Api.h"
#include "includes/json.hpp"
using json = nlohmann::json;

#define RESPONSE_SECS 1
#define RESPONSE_NSECS 0

#include <iostream>
using namespace std;

int main() {
	//Game_Api * api;
	int my_player_num = 0;
	while(1){
		char* buf = NULL;
		size_t size = 0;

		getline(&buf, &size, stdin);
		json data = json::parse(buf);

		if(data["type"] == "map"){
			string map = data["map"];
			//api = new Game_Api(map);
			my_player_num = data["player_id"];
			cerr << "Player " << my_player_num << " received map data" << endl;
		} else {
			cerr << "Player " << my_player_num << " received turn " << data["turn_number"] << " data" << endl;
			printf("0 %d\n", my_player_num);
			fflush(stdout);
		}

		free(buf);
	}
}
