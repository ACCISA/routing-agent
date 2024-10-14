#include "../Utils/error.h"
#include "../Utils/utils.h"
#include "../Config/config.h"

#include <stdio.h>
#include <string.h>

void
set_agent_from_config(char* filename)
{
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        print_error("CONFIG - Failed to read config file");
        return;
    }

    char buffer[250];
    int idx = 0;
    char agent_name[50] = {0};
    char ip_addr[50] = {0};
    char port[10] = {0};
    char key[33] = {0}; 
    char iv[17] = {0};

    while (fgets(buffer, sizeof(buffer), file) != NULL && idx < 5) {
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
            print_error("CONFIG - Invalid config file provided");
            fclose(file);
            return;
        }
        idx++;
    }

    if (idx != 5) {
        print_error("CONFIG - Incomplete config file");
        fclose(file);
        return;
    }

    set_agent_name((char*)agent_name);
    set_agent_ip_addr((char*)ip_addr);
    set_agent_port(atoi(port));
    set_agent_key((unsigned char*)key);
    set_agent_iv((unsigned char*)iv);

    fclose(file);
}

