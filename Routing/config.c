#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../Routing/entry.h"
#include "../Routing/config.h"

int
build_entry(char* token, entry_t* entry)
{
	int idx = 0;
	while (token != NULL) {
		if (idx == 0) entry->destination = atoi(token);
		else if (idx == 1) entry->next_hop = atoi(token);
		else if (idx == 2) {
			entry->ip_addr = (char*)malloc(strlen(token)+1);
			strncpy(entry->ip_addr, token, strlen(token));
		}
		else if (idx == 3) entry->port = atoi(token);
		else {
			print_error("Invalid config file");
			return 1;
		}
		token = strtok(NULL, ",");
		idx++;
	}

	print_entry(entry);
	return 0;


}

entry_t*
parse_line(char *line)
{
	char line_copy[50];
	int status;

	strncpy(line_copy, line, 50);

	char *token = strtok(line_copy, ",");

	entry_t* entry = (entry_t*)malloc(sizeof(entry_t));
	
	status = build_entry(token, entry);

	if (status != 0) {
		print_error("Failed to load config file");
		return NULL;
	}
	
	return entry;
}

entry_t*
read_config_file(FILE* file)
{
	char line[256];

	entry_t* temp_head = (entry_t*)malloc(sizeof(entry_t));
	entry_t* new_entry;
	
	while (fgets(line, sizeof(line), file)) {
		new_entry = parse_line(line);
		if (new_entry != NULL) {
			add_route_entry(&temp_head, new_entry);
		}
	}

	remove_tail_entry(temp_head);
	display_route_table(temp_head);

	return temp_head;
}

int
open_config_file(const char* config_path)
{
	FILE* file = fopen(config_path, "r");
	
	if (file == NULL) {
		print_error("Failed to open config file");
		return 1;
	}

	print_info("Reading config file");


	entry_t* entry_table = read_config_file(file);

	if (entry_table == NULL) {
		print_error("Open config file routine failed");
		return 1;
	}

	print_info("Loaded config data");
	return 0;
}
