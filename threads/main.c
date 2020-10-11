#include <stdio.h>
#include "general.h"
#include <string.h>
#include <pthread.h>
void* slowPrintThread(void* unused)
{
	char* msg = "HELLO WORLD\n";
	for (int i = 0; i < strlen(msg); i++){
		printf("%c", msg[i]);
		fflush(stdout); // file flush, print a single character at a time
		// fflush is needed because sometimes the screen only updates at the end (final line)
		sleep_msec(200);
	}
	return NULL;
}

int main(int argc, char** args)
{
	printf("********done program********\n");
	pthread_t threadPID;
	pthread_create(
		&threadPID,  // PID (by pointer)
		NULL, 		 // Attributes
		slowPrintThread, 	// Function
		NULL);				// Arguments
	sleep_msec(1000);
}