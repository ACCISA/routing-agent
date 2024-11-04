import ssl
import socket
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

key = b"a"*32  # 32-byte key
iv = b"a"*16   # 16-byte IV

data = bytes([
    0x01, 0x01, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x32, 0x00, 0x00, 0x00, 
    0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
    0x3b, 0xc1, 0x54, 0x17, 0x99, 0x11, 0x76, 0x01, 0x09, 0xae, 0xfa, 0xca, 0x71, 0x82, 0x97, 0xbb, 0xff,
    0x44, 0x51, 0xed, 0xaf, 0xf9, 0x14, 0xb5, 0x2f, 0xc4, 0xa7, 0x9b, 0xeb, 0xc7, 0x5a, 0xbd, 0x5c
])

data2 = bytes([
    0x01, 0x01, 0x00, 0x01,
    0x02, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x32, 0x00, 0x00, 0x00, 
    0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
    0x3b, 0xc1, 0x54, 0x17, 0x99, 0x11, 0x76, 0x01, 0x09, 0xae, 0xfa, 0xca, 0x71, 0x82, 0x97, 0xbb, 0xff,
    0x44, 0x51, 0xed, 0xaf, 0xf9, 0x14, 0xb5, 0x2f, 0xc4, 0xa7, 0x9b, 0xeb, 0xc7, 0x5a, 0xbd, 0x5c
])

forward_hostname = bytes([
    0x00, 0x01, 0x00, 0x01,
    0x01, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 
    0x3b, 
    0x41, 0x31, 0x2c, 0x41, 0x32, 0x2c, 0x41, 0x33,
    0x41, 0x32, 0x2c, 0x41, 0x33, 0x2c, 0x41, 0x33
])


print(bytes(data))
print("data_len", len(forward_hostname))

cipher = AES.new(key, AES.MODE_CBC, iv)
encrypted_data = cipher.encrypt(pad(forward_hostname, AES.block_size))
cipher2 = AES.new(key, AES.MODE_CBC, iv)
encrypted_data2 = cipher2.encrypt(pad(data2, AES.block_size))

hex_data = ''.join(f'{byte:02x}' for byte in forward_hostname)
enc_hex_data = ''.join(f'{byte:02x}' for byte in encrypted_data)
print(hex_data)
print("header",hex_data[0:28])
print("payload", hex_data[28:])
print(enc_hex_data)

for i in range(0,10):
    if i != 0:
        break

    context = ssl.create_default_context(ssl.Purpose.SERVER_AUTH)
    context.check_hostname = False
    context.verify_mode = ssl.CERT_NONE

    with socket.create_connection(('localhost', 2222)) as sock:
        with context.wrap_socket(sock, server_hostname='localhost') as tls_conn:
            tls_conn.sendall(encrypted_data)
            response = tls_conn.recv(1024)
            print(response)

