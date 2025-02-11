#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 

#define PING_PONG_BYTE_SIZE 1


int main(){

	// 1 byte i.e. 8 bits
	char parentWriteByte = 'p';
	char parentReadByte;

	char childWriteByte = 'c';
	char childReadByte;

	int childPipe[2];
	int parentPipe[2];


	if (pipe(childPipe) < 0 || pipe(parentPipe) < 0) {
	    printf("Something went wrong while creating pipes\n");
	    exit(1);
	}

	int pid = fork();

	
	if(pid == 0){

		close(parentPipe[1]);
		close(childPipe[0]);

	    // Child
	    while(1){
	        read(parentPipe[0], &childReadByte, PING_PONG_BYTE_SIZE);
	        printf("Child read %c from parent\n", childReadByte);
	        write(childPipe[1], &childWriteByte, PING_PONG_BYTE_SIZE);
	    }
	} else if(pid > 0){
	    // Parent

		close(parentPipe[0]);
		close(childPipe[1]);

	    while(1){
	        write(parentPipe[1], &parentWriteByte, PING_PONG_BYTE_SIZE);
	        read(childPipe[0], &parentReadByte, PING_PONG_BYTE_SIZE);
	        printf("Parent read %c from child\n", parentReadByte);
	    }
	} else{
		// Error
		printf("Something went wrong");
	}


	return 0;
}