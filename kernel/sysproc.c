#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

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
sys_getppid(void)
{
    return myproc()->parent->pid;
}

uint64
sys_getancestor(void)
{
    int n, pid_ancestor;
    struct proc *p = myproc();
    argint(0, &n);
    if (n < 0)
        return -1;

    for (int i = 0; i < n; i++)
    {
        if (p->parent == 0)
            return -1; // No hay suficientes ancestros
        p = p->parent;
    }
    pid_ancestor = p->pid;
    return pid_ancestor;
}
/*uint64
sys_getancestor(void)
{
  int i;
  argint(0, &i);
  struct proc *ancestor = myproc();
  int anc_pid = myproc()->pid;

  for (int j = 0; j < i; j++){
    if (ancestor->parent){
      anc_pid = ancestor->parent->pid;
      ancestor = ancestor->parent;
    }
    else{
      anc_pid = -1;
      break;
    }
  };

  return anc_pid;
}*/