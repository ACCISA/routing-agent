#include "../../Router/router.h"
#include "../../Utils/utils.h"
#include "../../Utils/error.h"

int main(void) 
{
	char data1[44] = {
		0x01, // is_destination
		0x01, // is_forward
		0x01, // has_response
		0x02,0x00,0x00,0x00, // num_sections
		0x08,0x00,0x00,0x00, // cur_section
		0x11,0x00,0x41,0x00, // response_len
		0x32,0x00,0x00,0x00, // msg_id
		0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00, // sections_len
		0x3b,
		0x41,0x31,0x2c,0x41,0x32,0x2c,0x41,0x33,
		0x41,0x32,0x2c,0x41,0x33,0x2c,0x41,0x34
	};


	
	char item1[50];
	char item2[50];

	printf("data1: %s\n", data1);
	int header_len;
	int payload_len;

	int status = parse_routing_message(data1,44, item1, &header_len, item2, &payload_len);
		
	if (status == -1) {
		print_error("Failed to parse routing message test1");
		return 1;
	}

	for (int i = 0; i < header_len; i++) {
		printf("0x%02X\n ", item1[i]);
	}
	printf("----\n");
	printf("len: %d\n", payload_len);
	for (int i = 0; i < payload_len; i++) {
		printf("0x%02X\n", item2[i]);
	}

	print_info("Test result:");
	printf("[+] (header_data=%s), (payload_data=%s)", item1, item2);

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

	return 0;
}
