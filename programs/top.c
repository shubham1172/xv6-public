#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main()
{
  char *buffer = "";
  while(strcmp(buffer, "q")!=0){
      top();
      gets(buffer, 2);
  }
  exit();
}
