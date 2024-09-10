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
		if (idx == 0) entry->destination = atoi(token);
		else if (idx == 1) entry->next_hop = atoi(token);
		else if (idx == 2) entry->ip_addr = token;
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
		return;
	}

	printf("Reading config file\n");

	char line[256];
	entry_t* temp_head = (entry_t*)malloc(sizeof(entry_t));
	entry_t* new_entry;

	while (fgets(line, sizeof(line), file)) {
		new_entry = parse_line(line);
		if (new_entry != NULL) {
			add_route_entry(temp_head, new_entry);
		}
	}
	printf("Displaying routing table\n");
	
	display_route_table(temp_head->next_entry);
	
	fclose(file);

	return temp_head->next_entry;
}
