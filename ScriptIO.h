#include <string>
#include "includes/json.hpp"
using json = nlohmann::json;
using namespace std;

/*
 * initializes each of the player scripts and sets up communication between this program and the player scripts
 */
void start_scripts(char* script1, char* script2);

/*
 * kills each of the player scripts
 */
void terminate_scripts();

#define READ_BUF_SIZE 64
/*
 * reads up to READ_BUF_SIZE bytes of input from player_num's process
 */
string read_from_player(int player_num);

/*
 * writes the string str into the respective player's stdin
 */
void write_to_player(int player_num, string str);
void write_to_player(int player_num, json obj);
