#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include <iostream>
#include <string>

#include "ScriptIO.h"

static int to_p1_fd;
static int from_p1_fd;

static int to_p2_fd;
static int from_p2_fd;

void start_script(char* name, int& stream_to, int& stream_from) {
  int pipe_to[2];
  if (pipe(pipe_to)) {
    perror("pipe()");
    exit(1);
  }

  int pipe_from[2];
  if (pipe(pipe_from)) {
    perror("pipe()");
    exit(1);
  }

  pid_t child_id = fork();

  if (child_id == -1) {
    perror("fork()");
    exit(1);
  } else if (!child_id) {
    // Child Process

    /* dup pipe read/write to stdin/stdout */
    if ( (dup2( pipe_to[0], STDIN_FILENO ) == -1) ||
        (dup2( pipe_from[1], STDOUT_FILENO  ) == -1)) {
      perror("dup2()");
      exit(1);
    }
    /* close unnecessary pipe descriptors for a clean environment */
    if (close( pipe_to[0] ) ||
        close( pipe_to[1] ) ||
        close( pipe_from[0] ) ||
        close( pipe_from[1] )) {
      perror("close() (child)");
      exit(1);
    }

    execlp(name, name, NULL);
    perror("execlp()");
    exit(1);
  }
  // Parent Process
  if (close(pipe_to[0]) ||
      close(pipe_from[1])) {
        perror("close() (parent)");
        exit(1);
  }

  stream_to = pipe_to[1];
  stream_from = pipe_from[0];
}

void start_scripts(char* script1, char* script2) {
  start_script(script1, to_p1_fd, from_p1_fd);
  start_script(script2, to_p2_fd, from_p2_fd);
}

std::string read_from(int fd) {
  FILE* stream = fdopen(dup(fd), "r");

  char* buf = NULL;
  size_t size = 0;

  ssize_t len = getline(&buf, &size, stream);

  if (len == -1 && errno == EINVAL) {
    perror("getline()");
    exit(1);
  } else if (len > 0 && buf[len - 1] == '\n') {
    buf[len-1] = '\0';
  }

  fclose(stream);

  return std::string(buf);
}

std::string read_from_player(int player_num) {
  if (player_num == 1) {
    return read_from(from_p1_fd);
  } else if (player_num == 2) {
    return read_from(from_p2_fd);
  } else {
    std::cout << "Invalid player number passed to read_from_player" << std::endl;
    return "";
  }
}

void write_to(int fd, std::string str) {
  const char* cstr = str.c_str();
  size_t bytes_read = 0;
  size_t len = str.length();

  while (bytes_read < len) {
    ssize_t ret = write(fd, cstr + bytes_read, len - bytes_read);

    if (ret == -1 && errno != EINTR) {
      perror("write()");
      exit(1);
    } else if (ret > 0) {
      bytes_read += ret;
    }
  }
}

void write_to_player(int player_num, std::string str) {
  if (player_num == 1) {
    write_to(to_p1_fd, str);
  } else if (player_num == 2) {
    write_to(to_p2_fd, str);
  } else {
    std::cout << "Invalid player number passed to write_to_player" << std::endl;
  }
}
