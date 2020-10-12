#include <stdio.h>
#include "general.h"
#include <string.h>
#include <pthread.h>
void* slowPrintThread(void* msgAsVoid)
{
	// type casting to void* is free so you can pass anything in
	char* msg = msgAsVoid;
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
		NULL, 		 // Attributes - can specify priorities (if you want it to run first)
		slowPrintThread, 	// Function
		"This is a new message\n");				// Arguments - can pass in a string as a pointer
	
	//sleep_msec(1000);

	pthread_t threadPID2;
	pthread_create(
		&threadPID2,
		NULL,
		slowPrintThread,
		"************************** OOP\n");
	// in this second thread, if we print out more than the first thread does,
	// the program will once again end before the thread finishes
	// (this is because the following pthread join command only adapts to the first thread)
	// solution: call another pthread_join for threadPID2

	// program ends before pthread finishes
	// so we gotta use:
	// join threads

	// if we're only waiting for one thread then the program will termninate once one thread finishes
	// so we can just wait for the longer thread
	// pthread_join(threadPID, NULL); 
	pthread_join(threadPID2, NULL);
	// 2nd param is a return value can be stored in a pointer to void*
	// whatever you return in the slowPrintThread will be returned in the second param
	return 0;
}