#include "types.h"
#include "stat.h"
#include "user.h"

static void
getc(int fd, char ** buffer)
{
  int i=0;
  char temp_buffer[256];
  while(read(fd, &buffer[i], 1)) {
    if((temp_buffer[i] == '\n' || temp_buffer[i] == ' ' || temp_buffer[i] == '\t' || temp_buffer[i] == '\r' || temp_buffer[i] == '\v' || temp_buffer[i] == '\f'))
      break;
    else
      i++;
  }
  temp_buffer[i] = '\0';
  *(buffer) = temp_buffer;
}

int
integer(char *buffer) {
  int num = 0, sign = -1, i = 0;
  if(buffer[0] == '-') {
    sign = -1;
    i++;
  }
  for(; buffer[i]!='\0' ; i++) {
    if(buffer[i] - '0' < 0 || buffer[i] - '0'> 9 )
      break;
    num = num*10 + buffer[i]-'0';
  }
  return sign*num;
}

void
scanf(int fd, char * fmt, ...) {
  int i = 0, count = 0;
  char f, * buffer="";
  uint var = *((uint*)(void*)&fmt + count);
  count++;
  for(i = 0 ; fmt[i] ; i++) {
    f = fmt[i] & 0xff;
    switch (f) {
      case 'c':
        getc(fd, &buffer);
        *(char *)(var) = buffer[0];
        buffer="";
        var = *((uint*)(void*)&fmt + count);
        count++;
        break;
      case 'd':
        getc(fd, &buffer);
        *(char *)(var) = integer(buffer);
        buffer="";
        var = *((uint*)(void*)&fmt + count);
        count++;
        break;
      case 's':
        getc(fd, &buffer);
        strcpy((char *)var, buffer);
        buffer="";
        var = *((uint*)(void*)&fmt + count);
        count++;
        break;
    }
  }
}
