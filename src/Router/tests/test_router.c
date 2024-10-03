#include "../router.h"
#include "../../globals.h"
#include "../../Utils/utils.h"
#include "../../Utils/error.h"


int main(void)
{
	unsigned char data[60] = {
		0x00, // is_destination
		0x01, // is_forward
		0x01, // has_response
		0x02,0x00,0x00,0x00, // num_sections
		0x08,0x00,0x00,0x00, // cur_section
		0x11,0x00,0x41,0x00, // response_len
		0x32,0x00,0x00,0x00, // msg_id
		0x10,0x00,0x00,0x00,0x10,0x00,0x00,0x00, // sections_len
		0x3b,
		0x3e, 0xa8, 0xef, 0xd3, 0xc1, 0x6f, 0x1e, 0xed, 0x25, 0x6a, 0xc0, 0x5e, 0xab, 0xae, 0xbe, 0x5d,
		0x36, 0x54, 0xab, 0x2c, 0x94, 0xee, 0x9c, 0xa5, 0x83, 0xae, 0xe8, 0x35, 0x89, 0x39, 0xb8, 0xe2
	};

	unsigned char decrypt_key[32] = {
		0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
		0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
		0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
		0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa
	};

	initialize_agent_info();

	set_agent_name("A2");
	set_agent_ip_addr("127.0.0.1");
	set_agent_port(9999);
	set_agent_key(decrypt_key);
	set_agent_iv(decrypt_key);
	
	display_agent_info();

	peer_t* peer1 = create_peer_entry("127.0.0.1",1111, "A1");
	peer_t* peer2 = create_peer_entry("127.0.0.1",2222, "A2");
	peer_t* peer3 = create_peer_entry("127.0.0.1",3333, "A3");
	peer_t* peer4 = create_peer_entry("127.0.0.1",4444, "A4");

	display_peer_info(peer1);
	display_peer_info(peer2);
	display_peer_info(peer3);
	display_peer_info(peer4);

	add_peer_entry(peer1);
	add_peer_entry(peer2);
	add_peer_entry(peer4);
	add_peer_entry(peer3);
	
	display_peer_table();

	unsigned char item1[50];
	unsigned char item2[50];

	int header_len;
	int payload_len;

	int status = parse_routing_message(data,60, item1, &header_len, item2, &payload_len);
		
	if (status == -1) {
		print_error("Failed to parse routing message test1");
		return 1;
	}


	print_info("Test result:");
	printf("[+] (header_data=%s), (payload_data=%s)\n", item1, item2);

	rheader_t* routing_header;

	routing_header = create_routing_header(item1);

	if (routing_header == NULL) {
		printf("faield to create header\n");
		return 1;
	}
	
	display_header_info(routing_header);

	rpayload_t* routing_payload;
	printf("item2: %s\n", item2);
	routing_payload = create_routing_payload(item2, routing_header->num_sections, routing_header->sections_len);

	if (routing_payload == NULL) {
		print_error("failed to create routing paylaod");
	}

	printf("payload: %s\n", routing_payload->sections[0]);


	process_route_sequence(routing_header, routing_payload);
	process_route_sequence(routing_header, routing_payload);

	return 0;

}
