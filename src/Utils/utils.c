#include <stdio.h>
#include <stdlib.h>

#include "../Utils/utils.h"

void 
print_info(char* str)
{
	printf("[+] %s\n", str);
}

void print_hex(unsigned char* buffer, int length) {
    for (int i = 0; i < length; ++i) {
        printf("%02x", buffer[i]);
    }
    printf("\n");
}
