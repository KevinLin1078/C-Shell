
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "cse320_functions.h" 
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int called = 0;
void kill_process(void); 
pid_t pid;
int f =0;
int time = 0;

void cse320_settimer(int N) {
	called = 1;
	time = N;
	signal(SIGALRM, (void (*)(int)) kill_process);
	alarm(time);


}

void kill_process(void) {
  	
	while(waitpid(-1, 0, 0) >0){
		printf("Reaped Child\n");
	}
}

pid_t cse320_fork(){
    
	if(called == 0){
		signal(SIGALRM, (void (*)(int)) kill_process);
		alarm(1);
	}

    pid =fork();
    if(pid < 0){  
    	printf("fork error\n");
    	return pid;
    }
    return pid;
}