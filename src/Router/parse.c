#include "../Router/router.h"
#include "../Utils/error.h"
#include "../Utils/utils.h"

int
parse_routing_message(unsigned char* data, unsigned char* header_data, unsigned char* payload_data)
{
	char *token = strtok((char *)data, ";");
	int idx = 0;
    	if (token != NULL) {
		if (idx > 2) {
			print_error("ROUTER - Failed to parse routing message");
			return -1;
		}
        	strcpy(header_data, token);
        
        	token = strtok(NULL, ";");
        	if (token != NULL) strcpy(payload_data, token);
		idx++;
    	}

	return 0;
}
rheader_t*
create_routing_header(unsigned char* data)
{

}

rpayload_t*
create_routing_payload(unsigned char* data, int32_t num_sections, int32_t* sections_len)
{
}
