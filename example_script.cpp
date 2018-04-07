#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	printf("Hello world!\n");
	fflush(stdout);

	char* buf = NULL;
	size_t size = 0;

	getline(&buf, &size, stdin);

	printf("%s\n", buf);
	fflush(stdout);

	free(buf);
}
