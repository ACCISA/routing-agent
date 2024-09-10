typedef struct entry {
	struct entry* next_entry;
	int destination;
	int next_hop;
} entry_t;

entry_t* create_route_entry(int destination, int next_hop);
void display_route_table(entry_t* entry_head);
int find_next_hop(entry_t* entry_head, int destination);
