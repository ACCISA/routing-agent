typedef struct {
	char* agent_name;
	int port;
	char* ip;
} Agent;

typedef struct routing {
	char* ip_addr;
	int port;
	char* agent_name;
	struct routing next_route;
} routing_t
