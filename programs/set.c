#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  if(argc!=3){
      printf(1, "USAGE: set VARIABLE VALUE\n");
      exit();
  }else{
      char buffer[512];
      char* entry = malloc(sizeof(char)*(strlen(argv[1])+strlen(argv[2])+2));
      strcpy(entry, argv[1]);
      strcpy(entry+strlen(argv[1]), "=");
      strcpy(entry+strlen(argv[1])+1, argv[2]);
      entry[strlen(entry)] = '\n';
      int fd = open(".tcshrc", O_CREATE|O_RDWR);
      if(fd<0){
        printf(2, "error reading .tcshrc\n");
        exit();
      }
      // goto end of file
      while(read(fd, buffer, sizeof(buffer)));
      write(fd, entry, strlen(entry));
      close(fd);
  }
  exit();
}
