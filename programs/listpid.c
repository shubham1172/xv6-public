#include "types.h"
#include "user.h"
#include "stat.h"
#include "pstat.h"

int
main()
{
  int i;
  struct pstat p;
  printf(1, "Sno\tPID\tHigh\tLow\n");
  listpid(&p);
  for( i = 0; i < NPROC ; i++) {
    if(p.inuse[i])
      printf(1, "%d\t%d\t%d\t%d\n", i, p.pid[i], p.hticks[i], p.lticks[i]);
  }
  exit();
}
