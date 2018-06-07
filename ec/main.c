#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "ec.h" 
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include<pthread.h>


int main(){
	FILE* a1 = cse320_fopen("filetest/file1", "r");
	FILE* a2 = cse320_fopen("filetest/file2", "r");
	FILE* a3 = cse320_fopen("filetest/file3", "r");
	FILE* a4 = cse320_fopen("filetest/file4", "r");
	FILE* a5 = cse320_fopen("filetest/file5", "r");
	
	
	cse320_fclose(a1);
	cse320_fclose(a2);
	cse320_fclose(a3);
	cse320_fclose(a4);
	cse320_fclose(a5);

	//displayfile();
	


	/*
	printf("Hey Kevin Lin\n");
	char* a1 = "bitch";
	char* a2 = (char*)cse320_malloc(sizeof(char) * 12);
	char* a3 = (char*)cse320_malloc(sizeof(char) * 12);
	char* a4 = (char*)cse320_malloc(sizeof(char) * 12);
	char* a5 = (char*)cse320_malloc(sizeof(char) * 12);
	char* a6 = (char*)cse320_malloc(sizeof(char) * 12);
	//addr_in_use* a1 = (addr_in_use*)cse320_malloc(sizeof(addr_in_use));
	//addr_in_use* a2 = (addr_in_use*)cse320_malloc(sizeof(addr_in_use));
	//addr_in_use* a3 = (addr_in_use*)cse320_malloc(sizeof(addr_in_use));
	//addr_in_use* a4 = (addr_in_use*)cse320_malloc(sizeof(addr_in_use));
	//addr_in_use* a5 = (addr_in_use*)cse320_malloc(sizeof(addr_in_use));
	//addr_in_use* a6 = (addr_in_use*)cse320_malloc(sizeof(addr_in_use));
	display();
	
	cse320_free(a1);
	display();


	char* a7 = (char*)cse320_malloc(sizeof(char) * 12);
	display();
	*/
}