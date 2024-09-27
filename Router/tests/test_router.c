#include "../router.h"
#include "../../globals.h"
#include "../../Utils/utils.h"
#include "../../Utils/error.h"


int main(void)
{

	char sequence[] = "3;A2;A3;A4;0;1";
	char sequence2[] = "4;A2;A3;A4;A5;0;1";
	char sequence_invalid[] = "3;A2;A3;A4;A5;0;1";

	initialize_agent_info();

	set_agent_name("AgentBoss");
	set_agent_ip_addr("127.0.0.1");
	set_agent_port(9999);
	
	display_agent_info();

	peer_t* peer1 = create_peer_entry("127.0.0.1",1111, "A1");
	peer_t* peer2 = create_peer_entry("127.0.0.1",2222, "A2");
	peer_t* peer3 = create_peer_entry("127.0.0.1",3333, "A3");

	display_peer_info(peer1);
	display_peer_info(peer2);
	display_peer_info(peer3);

	add_peer_entry(peer1);
	add_peer_entry(peer2);
	add_peer_entry(peer3);

	int status = process_route_sequence(sequence);

	if (status != 0) {
		print_info("Failed to run route sequence process test");
		return 1;
	}
	print_info("-----------");
	//process_route_sequence(sequence2);
	//print_info("-----------");
	//process_route_sequence(sequence_invalid);
	
	return 0;

}
