#include <stdio.h>
#include <stdlib.h>

#include "receiver.h"
#include <pthread.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define MSG_MAX_LEN 1024
#define PORT 22110

static int socketDescriptor;
static pthread_t threadPID;

void* ReceiveThread(void* msgAsVoid)
{
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(PORT);

	//create socket for UDP
	socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);

	// bidn the socket to the port (PORT) that we specify
	bind(socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));

	while(1){
		struct sockaddr_in sinRemote;
		unsigned int sin_len = sizeof(sinRemote);
		char messageRx[MSG_MAX_LEN];
		recvfrom(socketDescriptor, messageRx, MSG_MAX_LEN, 0, (struct sockaddr*) &sinRemote, &sin_len);

		// do something with received message
		printf("Message received : %s\n", messageRx);
		memset(&messageRx, 0, sizeof(messageRx));
	}
	printf("Done rx thread!\n");
	return NULL;
	
}
void Receiver_init(void){
	pthread_create(
		&threadPID,  // PID (by pointer)
		NULL, 		 // Attributes - can specify priorities (if you want it to run first)
		ReceiveThread, 	// Function
		NULL);				// Arguments - can pass in a string as a pointer
	
}
void Receiver_shutdown(void){
// cancel the thread
	pthread_cancel(threadPID);

	// join waits for the thread to be done
	pthread_join(threadPID, NULL);
	// 2nd param is a return value can be stored in a pointer to void*
}