#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"


// adds tickets to current process so it gets higher priority in lottery schedular
int
main(int argc, char *argv[])
{

    if(argc < 2){
      fprintf(2, "usage: nice ticketCount...\n");
      exit(1);
    }

    int ticketCount = atoi(argv[1]);

    if(ticketCount < 1){
        printf("Ticket count needs to be +ve");
        exit(1);
    }

    if(settickets(ticketCount) < 0){        
        printf("Set Tickets Failed\n");
        exit(-1);
    }

    printf("tickets set to process \n");

    int pid = fork();

    if(pid==0){
        // child infinite loop so we can check scheduling count
        for(;;){}
    }
    else if(pid < 0){
        printf("fork failed\n");
        exit(-1);
    }
    
    // parent should just exit so we can go back to shell
    exit(0);
}
