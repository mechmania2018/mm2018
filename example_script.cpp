#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define RESPONSE_SECS 1
#define RESPONSE_NSECS 0

int main() {
	while(1){
		char* buf = NULL;
		size_t size = 0;

		getline(&buf, &size, stdin);

		fprintf(stderr, "Player received %s\n", buf);

		sleep(0.5);

		printf("0 4\n");
		//printf("trashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrashtrash\n");
		fflush(stdout);

		sleep(0.5);

		free(buf);
	}
}
