#ifndef SHELL_H_
#define SHELL_H_

char* find_shell(void); // find a shell we can use to run command, return the shell's path
int run_cmd(char* shell_path, char* cmd, char* output); // run a command through the shell we found and return the output
int create_shell_process(char* shell_path); // create a shell process and return the socketfd
int communicate_shell(int pid, char* cmd, char* output); // send a command to a shell process

#endif
