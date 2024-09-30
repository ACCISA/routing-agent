#include "../Server/server.h"

void
init_openssl(void)
{
	SSL_load_error_strings();
	OpenSSL_add_ssl_algorithms();
}

void
cleanup_openssl(void)
{
	EVP_cleanup();
}

SSL_CTX*
create_ssl_context(void)
{
	const SSL_METHOD* method;
	SSL_CTX *ctx;

	method = SSLv23_client_method();

	ctx = SSL_CTX_new(method);
	if (!ctx) {
		print_error("Unable to create SSL context");
		ERR_print_errors_fp(stderr);
		return NULL;
	}

	return ctx;
}

int
create_socket(const char* hostname, int port)
{
	int sock;
	struct sockaddr_in  addr;

	sock  = socket(AF_INET, SOCK_STREAM, 0);
	if (sock <  0) {
		print_error("Unable to create socket");
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
    	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if (inet_pton(AF_INET, hostname, &addr.sin_addr) <= 0) {
		print_error("Invalid hostname/address");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		print_error("Failed to connect to agent");
		return -1;
	}

	return sock;
}

int
create_ssl_connection(const char* hostname, int port)
{
	SSL_CTX *ctx;
	SSL *ssl;

	init_openssl();
	ctx = create_ssl_context();

	sock = create_socket(hostname, port);

	ssl = SSL_new(ctx);
	SSL_set_fd(ssl, sock);

	if (SSL_connect(ssl) <= 0) {
		ERR_print_errors_fp(stderr);
	} else {
		print_info("Connected with encryption:");
		printf("alg_enc: %s\n", SSL_get_cipher(ssl));
	}
}


