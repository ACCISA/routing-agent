#include <stdlib.h>
#include <stdio.h>

#include "router.h"

// the routing table is a linked list where each node has a destination and next hop

entry_t*
create_route_entry(int destination, int next_hop)
{
	entry_t* newEntry = (entry_t*)malloc(sizeof(entry_t));
	newEntry->destination = destination;
	newEntry->next_hop = next_hop;
	newEntry->next_entry = NULL;

	return newEntry;
}

void
display_route_table(entry_t* entry_head)
{
	printf("Route Table: \n");
	if (entry_head == NULL) return;
	entry_t* entry_temp = entry_head;
	while (entry_temp != NULL) {
		printf("dst: %d,hop: %d\n",
				entry_temp->destination,
				entry_temp->next_hop);

		entry_temp = entry_temp->next_entry;
	}

}

int
find_next_hop(entry_t* entry_head, int destination)
{
	if (entry_head == NULL) return -1;

	entry_t* entry_temp = entry_head;
	int idx = 0;
	while (entry_temp != NULL) {

		if (entry_temp->destination == destination && entry_temp->next_hop != 0) {
			printf("Entry #%d, Next Hop: %d\n",
					idx,
					entry_temp->next_hop);
			return entry_temp->next_hop;
		}	
		
		if (entry_temp->destination == destination && entry_temp->next_hop == 0) {
			printf("Arrived to Destination\n");
			return -2;
		}

		idx++;
		entry_temp = entry_temp->next_entry;
	}

	return -1;
}

void
main(void)
{
	entry_t* entry1 = create_route_entry(1, 0);
	entry_t* entry2 = create_route_entry(2, 2);
	entry_t* entry3 = create_route_entry(3, 2);
	entry_t* entry4 = create_route_entry(4, 2);

	entry1->next_entry = entry2;
	entry2->next_entry = entry3;
	entry3->next_entry = entry4;

	display_route_table(entry1);
	find_next_hop(entry1, 2);
}
