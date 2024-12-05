# The following is an example of how to send ASCII commands over the UDP network to a Copley Controls servo drive. 
# NOTE: Bit 9 of the network options parameter (ASCII ID 0x121) needs to be set in the drive to enable UDP communications

import socket

def send_UDP_CMD(message, sock, server_address, server_port):
    encode_message = message.encode('utf-8')
    sock.sendto(encode_message, (server_address, server_port))
    data, addr = sock.recvfrom(1024)  # call returns a tuple, this accesses the part we need.
    decoded_response = data.decode('utf-8')
    return decoded_response

server_address = "192.168.1.1"  # note parameter r0x11F in the drive contains this IP address.
server_port = 19658  # port that the drive listens to for ASCII formatted packets according to AN121

# create UDP socket connection
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print("try command g r0xca")

response = send_UDP_CMD('g r0xca', sock, server_address, server_port)

print("drive response is: " + response)

# While loop prompts for desired ASCII command that it sends to stage until input is 'exit'
while True:
	print("Enter serial command")
	cmd = input()
	response = send_UDP_CMD(cmd, sock, server_address, server_port)
	print("drive response is: " + response)
	if cmd == 'exit':
		break

sock.close()