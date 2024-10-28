import socket
import ssl

def connect_to_tls_server(host, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    context = ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT)

    context.check_hostname = False
    context.verify_mode = ssl.CERT_NONE

    tls_socket = context.wrap_socket(sock, server_hostname=host)

    try:
        tls_socket.connect((host, port))
        print(f"Connected to {host}:{port}")

        message = b"Hello, TLS Server!"
        tls_socket.send(message)
        print(f"Sent: {message}")

        response = tls_socket.recv(1024)
        print(f"Received: {response}")

    except Exception as e:
        print(f"Error: {e}")
    finally:
        tls_socket.close()
        print("Connection closed.")

if __name__ == "__main__":
    host = 'localhost'
    port = 2222
    connect_to_tls_server(host, port)

