#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include<sys/types.h>

#include <iostream>
#include <string.h>
#include <string>

#include "ScriptIO.h"

#define READ_BUF_SIZE 64

static pid_t p1_pid;
static int to_p1_fd;
static int from_p1_fd;

static pid_t p2_pid;
static int to_p2_fd;
static int from_p2_fd;

// helper fucntion -- gets the number of arguments contained in a string
int get_arg_count(char* str) {
  int args = 1;
  int idx = 0;

  while (*(str + idx)) {
    if (*(str + idx) == ' ') {
      args ++;
    }
    idx ++;
  }

  return args;
}

// helper function to start one script, setting stream_to and stream_from
// to be file descriptors for a pipe to and from the script, respectively
pid_t start_script(char* name, int& stream_to, int& stream_from) {
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

    int num_args = get_arg_count(name);
    char* args[num_args + 1];
    args[num_args] = NULL;
    args[0] = name;

    int idx = 0;
    int arg = 1;
    while (arg < num_args) {
      if (*(name + idx) == ' ') {
        *(name + idx) = '\0';
        args[arg] = name + idx + 1;
        arg ++;
      }
      idx ++;
    }

    //execute the script
    execvp(args[0], args);
    perror("execvp()");
    exit(1);
  }
  // Parent Process
  if (close(pipe_to[0]) ||
      close(pipe_from[1])) {
        perror("close() (parent)");
        exit(1);
  }

  //set up the pipe between you and the newly started script
  stream_to = pipe_to[1];
  stream_from = pipe_from[0];

  // Modify reading stream to not block on reads
  int flags = 0;
  if ((flags = fcntl(stream_from, F_GETFL, 0)) == -1){
    perror("fcntl() (get flags)");
    exit(1);
  }
  if(fcntl(stream_from, F_SETFL, flags | O_NONBLOCK)){
    perror("fcntl() (set flags)");
    exit(1);
  }

  return child_id;
}

// public function to start each of the player scripts
void start_scripts(char* script1, char* script2) {
  p1_pid = start_script(script1, to_p1_fd, from_p1_fd);
  p2_pid = start_script(script2, to_p2_fd, from_p2_fd);
}

void terminate_scripts() {
  kill(p1_pid, 9);
  kill(p2_pid, 9);
}

// Read all input from player, and return only the first line, throwing the rest away
string read_from(int fd) {
  char buf[READ_BUF_SIZE];
  char trash[READ_BUF_SIZE];

  // I assume one usable line contains less than READ_BUF_SIZE bytes
  // since it's only really supposed to be a small json
  ssize_t len = read(fd, &buf, READ_BUF_SIZE);
  string return_string;

  if (len == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
    // Player sent nothing
    return "";
  } else if (len == -1){
    perror("read()");
    exit(1);
  } else {
    // Find the first newline character and set it to NULL
    char* eol = strchr(buf, '\n');
    if(!eol){
      // No newline == invalid input
      return_string = "";
    } else {
      *eol = '\0';
      return_string = string(buf);
    }
  }

  // discard the rest of the contents of the file descriptor
  while(read(fd, &trash, READ_BUF_SIZE) > 0){
    // Nothing to do here
  }

  return return_string;
}

// public method that gets the player's output
string read_from_player(int player_num) {
  if (player_num == 1) {
    return read_from(from_p1_fd);
  } else if (player_num == 2) {
    return read_from(from_p2_fd);
  } else {
    cout << "Invalid player number passed to read_from_player" << endl;
    return NULL;
  }
}

// helper function to write an entire string to a file descriptor
void write_to(int fd, string str) {
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

// public method that writes str into the respective player's stdin
void write_to_player(int player_num, string str) {
  if (player_num == 1) {
    write_to(to_p1_fd, str);
  } else if (player_num == 2) {
    write_to(to_p2_fd, str);
  } else {
    cout << "Invalid player number passed to write_to_player" << endl;
  }
}

void write_to_player(int player_num, json obj) {
  write_to_player(player_num, obj.dump() + "\n");
}
