#include "../Crypt/crypt.h"
#include "../Utils/utils.h"
#include "../Utils/error.h"

int
AES_encrypt(unsigned char* 		data,
		int		data_len,
		unsigned char*	key,
		unsigned char*	iv,
		unsigned char*	cipher)
{
	EVP_CIPHER_CTX 	*ctx;
	int		len;
	int		cipher_len;

	if (!(ctx = EVP_CIPHER_CTX_new())) {
		print_error("CRYPT - EVP_CIPHER_CTX_new");
		ERR_print_errors_fp(stderr);
		return -1;
	}

	if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1) {
		print_error("CRYPT - EVP_EncryptInit_ex");
		ERR_print_errors_fp(stderr);
		return -1;
	}

	if (EVP_EncryptUpdate(ctx, cipher, &len, data, data_len) != 1) {
		print_error("CRYPT - EVP_EncryptUpdate");
		ERR_print_errors_fp(stderr);
		return -1;
	}

	cipher_len = len;

	if (EVP_EncryptFinal_ex(ctx, cipher + len, &len) != 1) {
		print_error("CRYPT - EVP_EncryptFinal_ex");
		ERR_print_errors_fp(stderr);
		return -1;
	}

	cipher_len += len;

	EVP_CIPHER_CTX_free(ctx);
	print_info("Encrypted data");
	return cipher_len;

}


int
AES_decrypt(unsigned char*		cipher,
		int		cipher_len,
		unsigned char* 	key,
		unsigned char*	iv,
		unsigned char*	data)
{
	EVP_CIPHER_CTX 	*ctx;
	int		len;
	int		data_len;

	if (!(ctx = EVP_CIPHER_CTX_new())) {
		print_error("DECRYPT - EVP_CIPHER_CTX_new");
		ERR_print_errors_fp(stderr);
		return -1;
	}

	if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1) {
		print_error("DECRYPT - EVP_DecryptInit_ex");
		ERR_print_errors_fp(stderr);
		return -1;
	}

	if (EVP_DecryptUpdate(ctx, data, &len, cipher, cipher_len) != 1) {
		print_error("DECRYPT - EVP_DecryptUpdate");
		ERR_print_errors_fp(stderr);
		return -1;
	}
	data_len = len;

	if (EVP_DecryptFinal_ex(ctx, data+len, &len) != 1) {
		print_error("DECRYPT - EVP_DecryptFinal_ex");
		ERR_print_errors_fp(stderr);
		return -1;
	}
	data_len += len;

	EVP_CIPHER_CTX_free(ctx);

	print_info("Decrypted data");
	return data_len;


}
