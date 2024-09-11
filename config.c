#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "router.h"

entry_t*
parse_line(char* line)
{
	char line_copy[50];

	strncpy(line_copy, line, 50);

	char *token = strtok(line_copy, ",");
	int idx = 0;

	entry_t* entry = (entry_t*)malloc(sizeof(entry_t));
	

	while (token != NULL) {
		printf("idx: %d, tok: %s\n", idx, token);
		if (idx == 0) entry->destination = atoi(token);
		else if (idx == 1) entry->next_hop = atoi(token);
		else if (idx == 2) {
			entry->ip_addr = (char*)malloc(strlen(token)+1);
			entry->ip_addr = token;
		}
		else if (idx == 3) entry->port = atoi(token);
		else {
			printf("invalid config file\n");
			return NULL;
		}
		token = strtok(NULL, ",");
		idx++;
	}

	printf("config entryy; dst: %d, hop: %d, addr: %s, port: %d\n",
			entry->destination,
			entry->next_hop,
			entry->ip_addr,
	      		entry->port);

	return entry;
}

entry_t*
read_config(const char* config_path)
{
	FILE* file = fopen(config_path, "r");
	if (file == NULL) {
		printf("Failed to read config file\n");
		return NULL;
	}

	printf("Reading config file\n");

	char line[256];
	entry_t* temp_head = (entry_t*)malloc(sizeof(entry_t));
	entry_t* new_entry;

	while (fgets(line, sizeof(line), file)) {
		new_entry = parse_line(line);
		printf("new entry: %s\n",new_entry->ip_addr);
		if (new_entry != NULL) {
			printf("temp addr: %s\n",temp_head->ip_addr);
			add_route_entry(&temp_head, new_entry);
			printf("new antry: %s\n",new_entry->ip_addr);
			printf("new entry2: %s\n",temp_head->ip_addr);
			display_route_table(temp_head);
		}
	}
	printf("Displaying routing table\n");
	printf("addr: %s\n",temp_head->next_entry->next_entry->ip_addr);
	display_route_table(temp_head->next_entry);
	
	fclose(file);
	
	return temp_head->next_entry;
}
