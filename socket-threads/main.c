#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "receiver.h"


int main(int argc, char** args)
{
	// initialize
	printf("********starting********\n");
	Receiver_init();

	
	// sleep_msec(1000);
	// wait for user input
	printf("enter something to kill the receive thread\n");
	char x;
	scanf("%c", &x);

	// shut down the module
	Receiver_shutdown();
	printf("done\n");
	return 0;
}