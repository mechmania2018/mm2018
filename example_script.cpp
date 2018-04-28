#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
	printf("Hello world!\n");
	fflush(stdout);

	char* buf = NULL;
	size_t size = 0;

	getline(&buf, &size, stdin);

	printf("%s\n", buf);
	fflush(stdout);

	free(buf);

	while(1){
		printf("0 0\n");
		fflush(stdout);
		sleep(0.5);
	}
}
