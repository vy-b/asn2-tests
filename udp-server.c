#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#define MAX_LEN 1024
#define PORT 22110

int main(){
	printf("UDP SERVER DEMO\n");
	printf("CONNECT USING netcat -u 1270\n");
	struct sockaddr_in sin; //local variable creates a struct on the stack

	// set up struct to open up socket
	memset(&sin, 0 ,sizeof(sin)); // wipe out sin
	sin.sin_family = AF_INET;
	// don't care what port we're sending on -> in any addr
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	// refers to 22110
	sin.sin_port = htons(PORT);

	// function socket gives back a handle
	// pf is for protocol and af is address
	int socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0); //sock dgram is user datagram (UDP)
	// bind opens the socket
	bind(socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));
	// sin is where you contain the actual IP address

	while (1){
		// hold information of who we got it from when we receive something
		struct sockaddr_in sinRemote;
		unsigned int sin_len = sizeof(sinRemote);
		char messageRx[MAX_LEN]; // buffer for the receive function, 
		// contains client's data, max length is defined above as how long we want the message to be
		//avoid overflow - max length max bytes


		// recvfrom is a BLOCKING CALL - the thread will block until it receives something
		int bytesRx = recvfrom(socketDescriptor, messageRx, MAX_LEN, 0,
			(struct sockaddr*) &sinRemote, &sin_len);
		// pass the address of a struct (sinRemote) - gives you the IP info on who you received from
		// sin_len is the length of the address

		// null terminated (string)

		// here we're trying to figure out where to write the terminating 0 at
		// if it was less than the number received then put it at the number received
		// otherwise write it at the end of the string
		// need to null terminate because we want it to be a string at the print line
		int terminateldx = (bytesRx < MAX_LEN) ? bytesRx: MAX_LEN-1;
		messageRx[terminateldx] = 0;
		printf("Message received (%d bytes): '%s'\n", bytesRx, messageRx);
		// for the assignment we will dynamically allocate some memory, copy it into the memory
		// annd then put it in the queue

		//extract the value from the message:
		// (process the message any way your app requires)
		int incMe = atoi(messageRx);

		// Compose the reply message:
		// (NOTE: watch for buffer overflows)
		char messageTx[MAX_LEN];
		sprintf(messageTx, "Math: %d + 1 = %d\n", incMe, incMe+1);

		// transmit a reply:
		sin_len = sizeof(sinRemote);
		sendto(socketDescriptor, messageTx, strlen(messageTx),
			0,
			(struct sockaddr *) &sinRemote, sin_len);

		// close socket when done
		close(socketDescriptor);

	}
}