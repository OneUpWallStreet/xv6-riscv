#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"

int main(int argc, char *argv[]) {
    struct pstat ps;

    // Run for a certain number of iterations
    for (int i = 0; i < 100; i++) {
        if (getpinfo(&ps) < 0) {
            printf("getpinfo failed\n");
            exit(1);
        }

        // Print in CSV format:
        // iteration, PID_1, ticks_1, PID_2, ticks_2, ..., PID_N, ticks_N
        printf("%d", i);

        // Loop through all processes and print their PID and ticks
        for (int j = 0; j < NPROC; j++) {
            if (ps.pid[j] != 0) {  // Only consider processes with a non-zero PID
                printf(",%d,%d", ps.pid[j], ps.ticks[j]);
            }
        }

        // New line after each iteration's output
        printf("\n");

        // Sleep for some ticks (adjust as needed)
        sleep(5);  // Sleep for 5 ticks (can adjust to your needs)
    }

    exit(0);
}
