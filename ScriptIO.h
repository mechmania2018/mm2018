#include <string>
#include "includes/json.hpp"
using json = nlohmann::json;
using namespace std;

/*
 * initializes each of the player scripts and sets up communication between this program and the player scripts
 */
void start_scripts(char* script1, char* script2);

/*
 * reads one line from the player indicated by player_num, discarding any further output from them
 */
string* read_from_player(int player_num);

/*
 * writes the string str into the respective player's stdin
 */
void write_to_player(int player_num, string str);
void write_to_player(int player_num, json obj);
