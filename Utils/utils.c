#include <stdio.h>
#include <stdlib.h>

#include "../Utils/utils.h"

void 
print_info(char* str)
{
	printf("[+] %s\n", str);
}

void
print_entry(entry_t* entry)
{
	print_info("Printing entry:");
	printf("[+] Entry info: dst %d, hop: %d, addr: %s, port: %d\n",
			entry->destination,
			entry->next_hop,
			entry->ip_addr,
	      		entry->port);
}

void
display_route_table(entry_t* entry_head)
{
	print_info("Displaying route table:");
	
	if (entry_head == NULL) return;

	entry_t* entry_temp = entry_head;

	while (entry_temp != NULL) {
		print_entry(entry_temp);
		entry_temp = entry_temp->next_entry;
	}
}
