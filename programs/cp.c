#include "types.h"
#include "user.h"
#include "copy.h"
#define MAX_BUF 512

int
main(int argc, char *argv[])
{
  if(argc != 3){
      printf(2, "Usage: cp src dest\n");
      exit();
  }
  if(copy(argv[1], argv[2])<0)
    printf(2, "cp: cannot copy %s to %s\n", argv[1], argv[2]);
  exit();

}
