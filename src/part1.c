#include <stdlib.h>
#include <stdio.h>
#include "cse320_functions.h" 
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char**argv){
	//printf("exit -- exits the application\n");
	//printf("run [X] -- runs the application\n");
	printf("Type help to display list of available commands\n");
	
	char input[255];
	pid_t pid;
	
prompt:

	printf("CSE320->");
	fgets (input, 100, stdin);
	input[strlen(input)-1] = '\0';
	
	char file[255];
	
	int read = 0;
	int space =0;
	while(input[read] != ' '){
		file[read] = input[read];
		read++;
	}
	file[read] = '\0';

	if(strcmp(input, "\0")  == 0 || strcmp(input, "\n")  == 0){
		
		goto prompt;
	}else if(  strcmp(file, "exit") != 0 && strcmp(file, "run") != 0 && strcmp(file, "help") != 0 ){
		printf("Command not found\n");
		goto prompt;
	}else if(strcmp(file, "exit") == 0){
		
		exit(0);
	}else if(strcmp(file, "run") == 0){
		read = 0;
		
		while(input[read] != '\0'){
			if(input[read] == ' '){
				space++;
			}
			read++;			
		}
		space+=1;
		
		
		char *arg[space];
		char *string = strtok(input, " ");
		read = 0;
		while(string != NULL){
			string = strtok(NULL, " ");
			arg[read] = string;
			read++;
		}
		arg[read-1]= NULL;
		pid_t pid = fork();
		
		if(pid == 0){
			
			
			if( (execvp(arg[0], arg)) < 0 ){
				printf("%s: Execution error\n", arg[0]);
			}

			exit(0);
		}	
		signal(SIGINT, SIG_IGN);
		wait(NULL);
		signal(SIGINT, SIG_DFL);

		goto prompt;
	}else if(strcmp(file, "help") == 0){
		printf("exit -- exits the application\n");
		printf("run [X] -- runs the application\n");
		printf("help -- displays list of available commands\n");
		goto prompt;
	}
	
	return 1;
}