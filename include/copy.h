#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"
#define MAX_BUF 512

int copy_(int sfd, int dfd){
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
copy(char *src, char* dest)
{
  int sfd, dfd;
  struct stat *ssrc, *sdest;

  // open fd
  if((sfd = open(src, O_RDONLY))<0)
      return -1;

  ssrc = malloc(sizeof(struct stat));
  if(fstat(sfd, ssrc)<0)
    return -1;

  // check types
  if(ssrc->type == T_DIR){
    /** not supported now */
    return -1;
  }
  else if(ssrc->type == T_FILE){
    if((dfd = open(dest, 0))<0){
        // create file
        dfd = open(dest, O_CREATE);
    }
    sdest = malloc(sizeof(struct stat));
    if(fstat(dfd, sdest)<0)
        return -1;
    close(dfd);
    if(sdest->type == T_FILE){
        dfd = open(dest, O_WRONLY);
        if(copy_(sfd, dfd)<0)
            return -1;
        else
            close(dfd);
    }
    else if(sdest->type == T_DIR){
        char* dest_file = malloc(sizeof(char)*(strlen(src)+strlen(dest)+1));
        strcpy(dest_file, dest);
        dest_file[strlen(dest)] = '/';
        strcpy(dest_file + strlen(dest) + 1, src);
        dfd = open(dest_file, O_CREATE|O_WRONLY);
        if(copy_(sfd, dfd)<0)
            return -1;
        else
            close(dfd);
    }
    else
        return -1;
  }
  else
      return -1;

  close(sfd);
  return 0;

}
