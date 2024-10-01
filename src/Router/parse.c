#include "../Router/router.h"
#include "../Utils/error.h"
#include "../Utils/utils.h"

void
display_header_info(rheader_t* routing_header)
{
	printf("---------------------------------------------------");
	print_info("ROUTER - Displaying routing header");
	printf("[+] ROUTER - (is_destination=%d), (is_forward=%d), (has_response=%d)\n",
			routing_header->is_destination,
			routing_header->is_forward,
			routing_header->has_response);
	printf("[+] ROUTER - (num_sections=%d), (cur_section=%d), (response_len=%d)\n",
			routing_header->num_sections,
			routing_header->cur_section,
			routing_header->response_len);
	printf("[+] ROUTER - Sequences len:");
	for (int i = 0; i < routing_header->num_sections; i++) {
		printf("[+] ROUTER - (section%d=%d)\n", i+1, routing_header->sections_len[i]);
	}

	printf("---------------------------------------------------");
}

int
parse_routing_message(unsigned char* data, int data_len, unsigned char* header_data, int* header_len, unsigned char* payload_data, int* payload_len)
{
	int i;
	int header_idx = 0;
	int payload_idx = 0;
	int found3B = 0;

	for (i = 0; i < data_len; i++) {
		if (data[i] == 0x3B) {
			found3B = 1;
			continue;
		}

		if (!found3B) {
			header_data[header_idx++] = data[i];
		} else {
			payload_data[payload_idx++] = data[i];
		}
	}

	*header_len = header_idx+1;
	*payload_len = payload_idx+1;

	return 0;
}
rheader_t*
create_routing_header(unsigned char* data)
{
	rheader_t* routing_header = (rheader_t*)malloc(sizeof(rheader_t));

	memcpy(&routing_header->is_destination, data, sizeof(int8_t));
	memcpy(&routing_header->is_forward, data + sizeof(int8_t), sizeof(int8_t));
	memcpy(&routing_header->has_response, data + 2 * sizeof(int8_t), sizeof(int8_t));
	memcpy(&routing_header->num_sections, data + 3 * sizeof(int8_t), sizeof(int32_t));
	memcpy(&routing_header->cur_section, data  + 3 * sizeof(int8_t) + sizeof(int32_t), sizeof(int32_t));
	memcpy(&routing_header->response_len, data + 3 * sizeof(int8_t) + 2 * sizeof(int32_t), sizeof(int32_t));
	
	routing_header->sections_len = (int32_t*)malloc(sizeof(int32_t)*routing_header->num_sections);
	for (int i = 0; i < routing_header->num_sections; i++) {
		memcpy(&routing_header->sections_len[i], data + 3 * sizeof(int8_t) + 3 * sizeof(int32_t) + i * sizeof(int32_t), sizeof(int32_t));
	}
	print_info("ROUTER - Created routing header struct");

	return routing_header;
}

rpayload_t*
create_routing_payload(unsigned char* data, int32_t num_sections, int32_t* sections_len)
{
}
