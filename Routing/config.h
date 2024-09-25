#ifndef CONFIG_H
#define CONFIG_H

#include "../Routing/entry.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"

int build_entry(char* token, entry_t* entry);
entry_t* parse_line(char* line);
entry_t* read_config_file(FILE* file);
int open_config_file(const char* config_path);

#endif
