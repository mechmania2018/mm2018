#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>
int main() {
    std::string json;
    std::string engine_data;
    std::string decision;

    while (true) {
        char *buf = NULL;
        size_t size = 0;
        getline(&buf, &size, stdin);
        fflush(stdin);

        //parse json

        //requesting adjacent nodes and player health
        printf("nh\n"); //n = nodes, h = health
        fflush(stdout);

        //receive data
        getline(&buf, &size, stdin);
        if (engine_data == "15720") {
            decision = "52\n";
            } else decision = "11\n";

        //sending decision
        std::cout << decision;
        fflush(stdout);
        free(buf);

    }
}

