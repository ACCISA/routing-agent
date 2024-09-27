#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int encrypt(unsigned char*	data,
		int 		data_len, 
		unsigned char* 	key, 
		unsigned char* 	iv, 
		unsigned char* 	cipher);
int decrypt(unsigned char* 	cipher,
		int 		cipher_len,
		unsigned char* 	key,
		unsigned char* 	iv,
		unsigned char* 	data);
