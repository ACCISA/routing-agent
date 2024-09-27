#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tokenise_route_sequence(char* sequence, char** tokens, int* token_count);
int populate_next_agent_hops(char** tokens, char*** agent_hops, int agent_hop_count);
int find_next_hop(char* next_agent);
int  process_route_sequence(char* sequence);
char* update_route_sequence(char* sequence);
void forward_next_hop(char *sequence);
void forward_instruction(char* instruction);
int is_target(char* agent_name);


