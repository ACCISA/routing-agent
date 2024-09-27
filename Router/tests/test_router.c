#include "../router.h"
#include "../../Utils/utils.h"
#include "../../Utils/error.h"


int main(void)
{

	char sequence[] = "3;A2;A3;A4;0;1";
	char sequence2[] = "4;A2;A3;A4;A5;0;1";
	char sequence_invalid[] = "3;A2;A3;A4;A5;0;1";

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
