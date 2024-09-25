#include <stdlib.h>
#include <stdio.h>

void error(const char* reason)
{
   (void) printf("Fatal error: %s\n", reason);
   
   exit(EXIT_FAILURE);
}

void
print_error(char * str)
{
	printf("[!] %s\n", str);
}
