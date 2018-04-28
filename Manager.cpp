#include "Manager.h"

using namespace std;

void init_pdata(pdata_t* obj, int player_num){
	obj->id = player_num;
	obj->m = PTHREAD_MUTEX_INITIALIZER;
	obj->cv = PTHREAD_COND_INITIALIZER;
	obj->state = Idle;
	obj->buffer = NULL;
}

void* manage_player(void* data){
	pdata_t *self = (pdata_t*) data;

	while(1){
		pthread_mutex_lock(&self->m);
		while(self->state == Idle){
			pthread_cond_wait(&self->cv, &self->m);
		}

		if(self->state == Reading){
			string temp = read_from_player(self->id);
			self->buffer = new string(temp);
			self->state = Idle;
		}

		if(self->state == Writing){
			write_to_player(self->id, *(self->buffer));
			self->state = Idle;
		}

		pthread_mutex_unlock(&self->m);
	}

	return NULL;
}