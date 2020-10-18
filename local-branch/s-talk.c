
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include "helper.h"
#include "input-send.h"
#include "receive-output.h"
#include "list.h"

// initialize everything here, pass in other files
static pthread_cond_t s_OkToSend = PTHREAD_COND_INITIALIZER;
static pthread_cond_t s_OkToPrint = PTHREAD_COND_INITIALIZER;

static pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;

//CONVERT HOSTNAME TO IP
//struct hostent *hp = gethostbyname(argv[whatever postion the hostname is in]);
//memcpy(&sin.sin_addr.s_addr, hp->h_addr_list[0], hp->h_length);

int main(int argc, char* argv[]) {
    List* SendList = List_create();
    List* PrintList = List_create();
	int socketDescriptor = socket_init();

	// checks if there are 4 arguments when the program is initialized in terminal
	if (argc != 4) {
	    perror("usage: ./s-talk myPortNumber RemoteMachineName RemotePort\n");
	    exit(EXIT_FAILURE);
	}
	char* portName = argv[3];
	int portNumber = atoi(portName);
	
	
	struct hostent *remoteHost = gethostbyname(argv[2]);
	char* remoteHostAddr = remoteHost->h_addr_list[0];
	int remoteHostSize = remoteHost->h_length;
	
	
	sendVariables_init(&s_mutex, &s_OkToSend, SendList, &socketDescriptor, remoteHostAddr, &portNumber, &remoteHostSize);

	inputThread_init();
	sendThread_init();
	receiveThread_init(&s_mutex, &s_OkToPrint, PrintList, &socketDescriptor);
	printThread_init(&s_mutex,&s_OkToPrint, PrintList);


	sendThread_shutdown();
	inputThread_shutdown();
	receiveThread_shutdown();
	printThread_shutdown();
}
