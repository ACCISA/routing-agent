#include "../../Utils/utils.h"
#include "../../Utils/error.h"
#include "../crypt.h"


int main(void)
{
	unsigned char* data = "THISMESSAGEISNOTENCRYPTED";
	int data_len = 25;
	unsigned char* key = "Ig2aGBDQtPDRxERHo4x+xGWTHLXDHbO14gzBqc+z32s=";
	unsigned char* iv = "6teDkcdOaUenR1n4Ks30PZQq6Ri6HfLF+qhOOcnh8lQ=111";
	unsigned char* cipher = (unsigned char*)malloc(sizeof(unsigned char)*200);

	print_info("Initial decrypted message:");
	printf("%s\n", data);

	int cipher_len = encrypt(data, data_len, key, iv, cipher);

	if (cipher_len == -1) {
		print_error("Failed to encrypt message");
		return 1;
	}
	print_info("Cipher content:");
	printf("%s\n", cipher);
	print_info("Cipher len:");
	printf("%d\n", cipher_len);

	unsigned char* dec_data = (unsigned char*)malloc(sizeof(unsigned char)*100);

	int dec_data_len = decrypt(cipher, cipher_len, key, iv, dec_data);

	if (cipher_len == -1) {
		print_error("Failed to decrypt message");
		return 1;
	}

	print_info("Decrypted message content:");
	printf("%s\n", dec_data);

	if (strncmp(dec_data, data, strlen(data)) != 0) {
		print_error("Decrypted message is not equivalent to initial message");
		return 1;
	}

	return 0;
}
