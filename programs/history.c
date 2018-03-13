#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

// show help
void
help(){
    printf(1, "history [-c]\n");
    printf(1, "Display or manipulate the history list.\n\n");
    printf(1, "\tOptions:\n");
    printf(1, "\t-c\t\tclear the history list by deleting all the entries\n");
    printf(1, "\t--help\t\tdisplay this help\n");
}

// panic for fd
void panic(int fd){
    printf(2, "history: error reading .history");
    close(fd);
    exit();
}

// clear .history

void
clear_history(){
    if(unlink(".history")<0)
        printf(2, "history: error clearing .history");
    close(open(".history", O_CREATE|O_WRONLY));
}

// read .history and dump it
void
dump(){
    char buffer[512];
    int fd = open(".history", O_CREATE|O_RDONLY);
    if(fd<0)
        panic(fd);
    while(read(fd, buffer, sizeof(buffer)))
        printf(1, buffer);
    close(fd);
}

int
main(int argc, char *argv[])
{
  if(argc<2){
      // dump history
      dump();
  }else{
      if(strcmp(argv[1], "-c") == 0){
          // clear history
          clear_history();
      }else if(strcmp(argv[1], "--help") == 0){
          help();
      }else{
          // show help
          help();
      }
  }
  exit();
}
