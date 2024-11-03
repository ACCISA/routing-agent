#include "../Router/router.h"
#include "../Reactor/reactor.h"
#include "../Queue/queue.h"
#include "../Message/message.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"
#include "../Instructor/task.h"
#include "../Instructor/commands.h"
#include "../globals.h"

#include <string.h>
#include <stdint.h>

void
display_header_info(rheader_t* routing_header)
{
	printf("---------------------------------------------------\n");
	print_info("ROUTER - Displaying routing header");
	printf("[+] ROUTER - (is_destination=%d), (is_forward=%d), (has_response=%d), (instruction=%d)\n",
			routing_header->is_destination,
			routing_header->is_forward,
			routing_header->has_response,
			routing_header->instruction);
	printf("[+] ROUTER - (num_sections=%d), (cur_section=%d), (response_len=%d)\n",
			routing_header->num_sections,
			routing_header->cur_section,
			routing_header->response_len);
	printf("[+] ROUTER - Sequences len:\n");
	for (int i = 0; i < routing_header->num_sections; i++) {
		printf("[+] ROUTER - (section%d=%d)\n", i+1, routing_header->sections_len[i]);
	}

	printf("---------------------------------------------------\n");
}

int
parse_routing_message(unsigned char* data, int data_len, unsigned char* header_data, int* header_len, unsigned char* payload_data, int* payload_len)
{
	int header_idx = 0;
	int payload_idx = 0;
	int found3B = 0;
	unsigned char* dec_data = (unsigned char*)malloc(sizeof(unsigned char)*100);

	if ((data_len = AES_decrypt(data, data_len,
					Agent->decrypt_key,
					Agent->iv,
					dec_data)) == 1) {
		print_error("ROUTER - Failed to decrypt routing message");
		return -1;
	}

	dec_data[data_len] = '\0';
	print_hex(dec_data, data_len);
	
	//TODO deal with bad formats
	for (int i = 0; i < data_len; i++) {
		if (dec_data[i] == 0x3B) {
			found3B = 1;
			continue;
		}

		if (!found3B) {
			header_data[header_idx++] = dec_data[i];
		} else {
			payload_data[payload_idx++] = dec_data[i];
		}
	}

	*header_len = header_idx;
	*payload_len = payload_idx;

	return 0;
}
rheader_t*
create_routing_header(unsigned char* data)
{
	rheader_t* routing_header = (rheader_t*)malloc(sizeof(rheader_t));

	memcpy(&routing_header->is_destination, data, sizeof(int8_t));
	memcpy(&routing_header->is_forward, data + sizeof(int8_t), sizeof(int8_t));
	memcpy(&routing_header->has_response, data + 2 * sizeof(int8_t), sizeof(int8_t));
	memcpy(&routing_header->instruction, data + 3 * sizeof(int8_t), sizeof(int8_t));
	memcpy(&routing_header->num_sections, data + 4 * sizeof(int8_t), sizeof(int32_t));
	memcpy(&routing_header->cur_section, data  + 4 * sizeof(int8_t) + sizeof(int32_t), sizeof(int32_t));
	memcpy(&routing_header->response_len, data + 4 * sizeof(int8_t) + 2 * sizeof(int32_t), sizeof(int32_t));
	memcpy(&routing_header->msg_id, data + 4 * sizeof(int8_t) + 3 * sizeof(int32_t), sizeof(int32_t));
	routing_header->sections_len = (int32_t*)malloc(sizeof(int32_t)*routing_header->num_sections);
	for (int i = 0; i < routing_header->num_sections; i++) {
		memcpy(&routing_header->sections_len[i], data + 4 * sizeof(int8_t) + 4 * sizeof(int32_t) + i * sizeof(int32_t), sizeof(int32_t));
	}
	print_info("ROUTER - Created routing header struct");

	return routing_header;
}

rpayload_t*
create_routing_payload(unsigned char* data, int32_t num_sections, int32_t* sections_len)
{
	rpayload_t* routing_payload = (rpayload_t*)malloc(sizeof(rpayload_t));

	if (routing_payload == NULL) {
		print_error("ROUTER - Failed to malloc routing_payload");
		return NULL;
	}

	routing_payload->sections = (char**)malloc(num_sections*sizeof(char*));

	if (routing_payload->sections == NULL) {
		print_error("ROUTER - Failed to malloc routing_payload");
		free(routing_payload);
		return NULL;
	}

	unsigned char* position = data;

	for (int i = 0; i < num_sections; i++) {
		routing_payload->sections[i] = (char*)malloc(sections_len[i]);
		
		if (routing_payload->sections[i] == NULL) {
			print_error("ROUTER - Failed to malloc routing_payload");
			for (int j = 0; j < i; j++) {
				free(routing_payload->sections[j]);
			}
			free(routing_payload->sections);
			free(routing_payload);
			return NULL;
		}
		memcpy(routing_payload->sections[i], position, sections_len[i]);
		position += sections_len[i];
	}

	return routing_payload;
}
