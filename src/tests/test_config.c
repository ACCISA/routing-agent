#include "../config.h"
#include "../../globals.h"
#include "../../Utils/utils.h"
#include "../../Utils/error.h"


int main(void)
{
	initialize_agent_info();
	
	set_agent_from_config("config");	

	display_agent_info();

	return 0;
}
