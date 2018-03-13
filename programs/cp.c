#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#define MAX_BUF 512

int
main(int argc, char *argv[])
{
  int sfd, dfd, r=0, w=0;
  char *src, *dest;
  char buf[MAX_BUF];

  if(argc != 3){
      printf(2, "Usage: cp src dest\n");
      exit();
  }

  src = argv[1];
  dest = argv[2];

  // open fds
  if((sfd = open(src, O_RDONLY))<0){
      printf(2, "cp: failed to open source %s\n", src);
      exit();
  }

  if((dfd = open(dest, O_CREATE|O_WRONLY))<0){
      printf(2, "cp: failed to open destination %s\n", dest);
      exit();
  }

  // copy
  while((r = read(sfd, buf, MAX_BUF))>0){
      w = write(dfd, buf, r);
      if(w != r || w < 0)
        break;
  }

  // check for errors
  if(r < 0 || w < 0)
      printf(2, "cp: error copying %s to %s\n", src, dest);

  // close fds
  close(sfd);
  close(dfd);

  exit();

}
