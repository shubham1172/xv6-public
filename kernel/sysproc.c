#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_waitp(void)
{
    int *wtime, *rtime;
    if(argptr(0, (char**)&wtime, sizeof(int)) < 0)
      return -1;

    if(argptr(1, (char**)&rtime, sizeof(int)) < 0)
      return -1;

    return waitp(wtime, rtime);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

struct pstat pstat;
int
sys_listpid(void)
{
  struct pstat *p;
  if(argptr(0, (void*)&p, sizeof(&p))<0)
    return -1;
  int i;
  for(i = 0;i < NPROC; i++) {
    p->inuse[i] = pstat.inuse[i];
    p->pid[i] = pstat.pid[i];
    p->name[i][0] = pstat.name[i][0];
    p->name[i][1] = pstat.name[i][1];
    p->name[i][2] = pstat.name[i][2];
    p->hticks[i] = pstat.hticks[i];
    p->lticks[i] = pstat.lticks[i];
  }
  return 0;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_ps(void)
{
  return ps();
}

int
sys_top(void)
{
  return top();
}

int
sys_shutdown(void){
  outb(0xf4, 0x00);
  return 0;
}

int
sys_date(void) {
  struct rtcdate* date;
  argptr(0, (void*)(&date), sizeof(*date));
  cmostime(date);
  return 0;
}
