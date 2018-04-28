# ifndef MANAGER_H
# define MANAGER_H

#include <iostream>
#include <pthread.h>
#include "ScriptIO.h"
// Set up a "manager thread" for each player
// An instance of this thread will handle reading/writing to the child program.

typedef enum pstate_t{Idle, Reading, Writing} pstate_t;

typedef struct pdata_t {
	pthread_t thread;
	int id; // 1 or 2
	pthread_mutex_t m;
	pthread_cond_t cv;
	pstate_t state;
	string* buffer; // A pointer to the string read from/written to player
} pdata_t;

void init_pdata(pdata_t* obj, int player_num);

// Data will be cast to type (pdata_t*)
void *manage_player(void* data);

# endif