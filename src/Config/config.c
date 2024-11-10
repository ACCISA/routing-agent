#include "../Utils/error.h"
#include "../Utils/utils.h"
#include "../Config/config.h"
#include "../Message/message.h"
#include "../Reactor/reactor.h"
#include "../Router/router.h"
#include "../Queue/queue.h"
#include "../Instructor/task.h"
#include "../globals.h"

#include <stdio.h>
#include <string.h>

#define MAX_INFO_LEN 30

int
read_peer_config(char* line)
{
	char* ip = (char*)malloc(sizeof(char)*MAX_INFO_LEN);
	int port;
	char* name = (char*)malloc(sizeof(char)*MAX_INFO_LEN);

	char* token = strtok(line, ";");
	if (token == NULL) return -1;
	strncpy(ip, token, MAX_INFO_LEN);
	ip[MAX_INFO_LEN-1] = '\0';

	token = strtok(NULL, ";");
	if (token == NULL) return -1;
	port = atoi(token);

	token = strtok(NULL, ";");

	if (token == NULL) return -1;

	strncpy(name, token, MAX_INFO_LEN);
	name[MAX_INFO_LEN-1];
	peer_t* peer = create_peer_entry(ip, port, name);
	add_peer_entry(peer);	
    	display_peer_table();
}

void
set_agent_from_config(char* filename)
{
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        print_error("CONFIG - Failed to read config file");
        return;
    }

    char buffer[250];
    int idx 			= 0;
    char agent_name[50] 	= {0};
    char ip_addr[50] 		= {0};
    char port[10] 		= {0};
    char key[33] 		= {0}; 
    char iv[17] 		= {0};
    char peer_config[50] 	= {0};

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (idx == 0) {
            	strncpy(agent_name, buffer, sizeof(agent_name) - 1);
        } else if (idx == 1) {
            	strncpy(ip_addr, buffer, sizeof(ip_addr) - 1);
        } else if (idx == 2) {
            	strncpy(port, buffer, sizeof(port) - 1);
        } else if (idx == 3) {
        	strncpy(key, buffer, sizeof(key) - 1);
        } else if (idx == 4) {
        	strncpy(iv, buffer, sizeof(iv) - 1);
        } else {
		strncpy(peer_config, buffer, sizeof(peer_config)-1);
		if (read_peer_config(peer_config) == -1) {
			print_error("CONFIG - Invalid config file provided");
			return;
		}
        }
        idx++;
    }

    set_agent_name((char*)agent_name);
    set_agent_ip_addr((char*)ip_addr);
    set_agent_port(atoi(port));
    set_agent_key((unsigned char*)key);
    set_agent_iv((unsigned char*)iv);
    fclose(file);
}

