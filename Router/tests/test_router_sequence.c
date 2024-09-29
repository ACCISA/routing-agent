#include "../router.h"
#include "../../globals.h"
#include "../../Utils/utils.h"
#include "../../Utils/error.h"


int main(void)
{

	char sequence[] = "3;A2;A3;A4;0;1;111";
	char sequence2[] = "4;A2;A3;1;1;111";
	char sequence_invalid[] = "3;A2;A3;A4;A5;0;1;333";

	initialize_agent_info();

	set_agent_name("A3");
	set_agent_ip_addr("127.0.0.1");
	set_agent_port(3333);
	
	display_agent_info();

	peer_t* peer1 = create_peer_entry("127.0.0.1",1111, "A1");
	peer_t* peer2 = create_peer_entry("127.0.0.1",2222, "A2");
	peer_t* peer3 = create_peer_entry("127.0.0.1",3333, "A3");
	peer_t* peer4 = create_peer_entry("127.0.0.1",4444, "A4");

	add_peer_entry(peer1);
	add_peer_entry(peer2);
	add_peer_entry(peer4);
	add_peer_entry(peer3);
	
	display_peer_table();

	printf("sequence: %s\n", sequence);
	int status = process_route_sequence(sequence);

	if (status != 0) {
		print_info("Failed to run route sequence process test");
		return 1;
	}

	status = process_route_sequence(sequence2);

	if (status != 0) {
		print_info("Failed to run route sequence process test");
		return 1;
	}



	
	return 0;

}
