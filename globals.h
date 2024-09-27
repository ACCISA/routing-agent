typedef struct {
	char* agent_name;
	int port;
	char* ip_addr;
	routing_t* routing;
} AgentInfo;

typedef struct peer {
	char* ip_addr;
	int port;
	char* agent_name;
	struct peer next_route;
} peer_t;

typedef struct routing {
	int size;
	peer_t* table;
} routing_t;

extern AgentInfo* Agent;
