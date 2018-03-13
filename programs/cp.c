#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#define MAX_BUF 512

int copy(int sfd, int dfd){
    char buf[MAX_BUF];
    int r = 0, w = 0;

    while((r = read(sfd, buf, MAX_BUF))>0){
        w = write(dfd, buf, r);
        if(w != r || w < 0)
          break;
    }
    // check for errors
    if(r < 0 || w < 0)
        return -1;
    return 0;
}

int
main(int argc, char *argv[])
{
  int sfd, dfd;
  char *src, *dest;
  struct stat *ssrc, *sdest;

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

  ssrc = malloc(sizeof(struct stat));
  if(fstat(sfd, ssrc)<0){
    printf(2, "cp: cannot stat source %s\n", src);
    exit();
  }

  // check types
  if(ssrc->type == T_DIR){
    /** not supported now */
    printf(2, "cp: unsupported action\n");
    exit();
  }
  else if(ssrc->type == T_FILE){
    if((dfd = open(dest, 0))<0){
        // create file
        dfd = open(dest, O_CREATE);
    }
    sdest = malloc(sizeof(struct stat));
    if(fstat(dfd, sdest)<0){
        printf(2, "cp: cannot stat destination %s\n", dest);
        exit();
    }
    close(dfd);
    if(sdest->type == T_FILE){
        dfd = open(dest, O_WRONLY);
        if(copy(sfd, dfd)<0)
            printf(2, "cp: error copying %s to %s\n", src, dest);
        else
            close(dfd);
    }
    else if(sdest->type == T_DIR){
        char* dest_file = malloc(sizeof(char)*(strlen(src)+strlen(dest)+1));
        strcpy(dest_file, dest);
        dest_file[strlen(dest)] = '/';
        strcpy(dest_file + strlen(dest) + 1, src);
        dfd = open(dest_file, O_CREATE|O_WRONLY);
        if(copy(sfd, dfd)<0)
            printf(2, "cp: error copying %s to %s\n", src, dest);
        else
            close(dfd);
    }
    else{
        printf(2, "cp: cannot be copied to device %s\n", dest);
    }
  }
  else{
      printf(2, "cp: device %s cannot be copied\n", src);
  }

  close(sfd);
  exit();

}
