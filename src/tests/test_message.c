#include "../../Router/router.h"
#include "../../globals.h"
#include "../../Utils/utils.h"
#include "../../Utils/error.h"
#include "../../Message/message.h"


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
	peer_t* peer4 = create_peer_entry("127.0.0.1",4444, "A4");

	display_peer_info(peer1);
	display_peer_info(peer2);
	display_peer_info(peer3);

	add_peer_entry(peer1);
	add_peer_entry(peer2);
	add_peer_entry(peer4);
	add_peer_entry(peer3);

	display_peer_table();

	message_t* msg1 = create_message("111", peer1);
	message_t* msg2 = create_message("222", peer2);
	message_t* msg3 = create_message("333", peer3);
	message_t* msg4 = create_message("444", peer4);

	store_message(msg1);
	store_message(msg2);
	store_message(msg3);
	store_message(msg4);

	display_message_store();

	remove_message("222");
	display_message_store();
	remove_message("333");
	display_message_store();
	remove_message("444");
	display_message_store();
	remove_message("111");

	display_message_store();
	
	return 0;

}
