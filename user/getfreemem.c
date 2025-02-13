#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int free_mem = getfreemem();  // Use uint64 to avoid truncation
    printf("Free memory: %d bytes\n", free_mem);  // Print properly
    exit(0);
}
