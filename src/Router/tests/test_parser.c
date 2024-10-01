#include "../../Router/router.h"
#include "../../Utils/utils.h"
#include "../../Utils/error.h"

int main(void) 
{
	char data1[28] = {
		0x01,
		0x01,
		0x01,
		0x02,0x00,0x00,0x00,
		0x08,0x00,0x00,0x00,
		0x11,0x00,0x41,0x00,
		0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,
		0x3b,0x41,0x41,0x41,0x00
	};


	
	char item1[50];
	char item2[50];

	printf("data1: %s\n", data1);
	int header_len;
	int payload_len;

	int status = parse_routing_message(data1,28, item1, &header_len, item2, &payload_len);
		
	if (status == -1) {
		print_error("Failed to parse routing message test1");
		return 1;
	}

	for (int i = 0; i < header_len; i++) {
		printf("0x%02X\n ", item1[i]);
	}
	printf("----\n");

	for (int i = 0; i < payload_len-1; i++) {
		printf("0x%02X ", item2[i]);
	}

	print_info("Test result:");
	printf("[+] (header_data=%s), (payload_data=%s)", item1, item2);

	rheader_t* routing_header;

	routing_header = create_routing_header(item1);

	if (routing_header == NULL) {
		printf("faield to create header\n");
	}
	
	display_header_info(routing_header);

	return 0;
