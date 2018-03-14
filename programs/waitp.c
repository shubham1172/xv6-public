#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main (int argc,char *argv[])
{

	int pid;
	int status, a, b;
	pid = fork();
	if (pid == 0)
  	{
  		exec(argv[1], argv);
    	printf(1, "exec %s failed\n", argv[1]);
      exit();
    }
  	else
 	{
    	status = waitp(&a, &b);
 	}
 	printf(1, "Wait time = %d \\| Run time = %d \\| PID = %d \n", a, b, status);
 	exit();
}
