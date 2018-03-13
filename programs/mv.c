#include "types.h"
#include "user.h"
#include "copy.h"

int main (int argc, char *argv[]){
  if (argc != 3){
    printf(2, "Usage: mv source destination\n");
    exit();
  }
  if(copy(argv[1], argv[2]) < 0){
    printf(2, "mv: cannot move %s to %s\n", argv[1], argv[2]);
    exit();
  }
  if (unlink(argv[1]) < 0)
    printf(2, "mv: move %s to %s failed\n", argv[1], argv[2]);
  exit();
}
