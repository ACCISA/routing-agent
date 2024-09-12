#define ROUTING_ACTION 1
#define HOSTNAME_ACTION 2
#define RESPONSE_ACTION 3

typedef struct entry {
	struct entry* next_entry;
	int destination;
	int next_hop;
	int port;
	char* ip_addr;
} entry_t;

typedef struct message {
	int instruction;
	int source;
	int destination;
	char* data;
} message_t;

void add_route_entry(entry_t** entry_head, entry_t* new_entry);
entry_t* create_route_entry(int destination, int next_hop, char* ip_addr, int port);
void display_route_table(entry_t* entry_head);
entry_t* find_next_hop(entry_t* entry_head, int destination);
void forward_next_hop(entry_t* entry, int instruction, int source, char* data);

entry_t* parse_line(char* line);
entry_t* read_config(const char* config_path);

void start_listener(int port);
void send_response(void);
void process_instruction(message_t* msg);

extern entry_t* routing_table;
extern int source;
