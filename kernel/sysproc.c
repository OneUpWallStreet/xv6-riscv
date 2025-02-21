#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "pstat.h"
#include <stddef.h>  // Contains definition for NULL

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_settickets(void ){

  int ticketCount;
  argint(0, &ticketCount);

  // Ticket count needs to be +ve
  if(ticketCount < 0){
    return -1;
  }

  // Going to proc.c and adding tickets to current process
  addticketstoproc(ticketCount);

  return 0;
}

uint64
sys_getpinfo(void){

  // user pointer for pstat struct to return back
  uint64 uptr;
  struct pstat kpstats;

  argaddr(0, &uptr);
  
  getpstats(&kpstats);

  // don't need to do user address checking because copyout does it.
  if(copyout(myproc()->pagetable,uptr,(char *)&kpstats,sizeof(kpstats)) < 0){
    return -1;
  } 
  
  return 0;

}