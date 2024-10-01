#include "../../Router/router.h"
#include "../../Utils/utils.h"
#include "../../Utils/error.h"

int main(void) 
{
	char data1[] = "alksjdlaksjdlaksd;alsidjjalkshda";
	char item1[50];
	char item2[50];

	int status = parse_routing_message(data1,item1,item2);

	if (status == -1) {
		print_error("Failed to parse routing message test1");
		return 1;
	}

	print_info("Test result:");
	printf("[+] (header_data=%s), (payload_data=%s)", item1, item2);


}
