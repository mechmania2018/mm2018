#include <string>
#include "includes/json.hpp"
using json = nlohmann::json;
using namespace std;

void start_scripts(char* script1, char* script2);

/*
 * reads one line from the player indicated by player_num
 */
string* read_from_player(int player_num);

void write_to_player(int player_num, string str);
void write_to_player(int player_num, json obj);
