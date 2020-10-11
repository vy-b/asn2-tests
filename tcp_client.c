#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {
	//create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specify address structure for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002); //pass port number
	server_address.sin_addr.s_addr = INADDR_ANY;

	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	//check for error with the connection
	if (connection_status == -1) {
		printf("error making connection")
	}
	//receive data from server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response),0); //second parameter is the location that we want to put the data we got from our socket

	//print out data we got back
	printf("the server sent the data: %s",server_response);

	//then close the socket
	close(sock);

	return 0;
}

