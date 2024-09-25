#include "../Routing/entry.h"
#include "../Utils/utils.h"

void
add_route_entry(entry_t** entry_head, entry_t* new_entry)
{
	new_entry->next_entry = *entry_head;
	*entry_head = new_entry;
	print_info("Added new routing entry");
}

void
remove_tail_entry(entry_t* entry_head)
{
	if (entry_head == NULL) return;

	entry_t* entry_temp = entry_head;

	while (entry_temp != NULL) {
		if (entry_temp->next_entry->next_entry == NULL) {
			entry_temp->next_entry = NULL;
			print_info("Removed list tail");
			return;
		}
		entry_temp = entry_temp->next_entry;
	}
}

entry_t*
create_route_entry(int destination, int next_hop, char* ip_addr, int port)
{
	entry_t* new_entry = (entry_t*)malloc(sizeof(entry_t));
	
	new_entry->destination = destination;
	new_entry->next_hop = next_hop;
	new_entry->ip_addr = ip_addr;
	new_entry->port = port;
	new_entry->next_entry = NULL;

	return new_entry;
}
