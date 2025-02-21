#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/pstat.h"

int
main(int argc, char *argv[])
{

    struct pstat ps;
    if (getpinfo(&ps) == 0) {
        for (int i = 0; i < NPROC; i++) {
            if (ps.inuse[i]) {
                printf("Process ID: %d, Tickets: %d, Ticks: %d\n",
                       ps.pid[i], ps.tickets[i], ps.ticks[i]);
            }
        }
    } else {
        printf("getpinfo failed!\n");
    }
    
    exit(0);
}
