#include <string>

void start_scripts(char* script1, char* script2);

/*
 * reads one line from the player indicated by player_num
 */
std::string read_from_player(int player_num);

void write_to_player(int player_num, std::string str);
