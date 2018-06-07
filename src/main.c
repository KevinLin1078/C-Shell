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
#include<pthread.h>


int main(int argc, char const *argv[])
{	
	FILE* a1 = cse320_fopen("filetest/file1", "r");
	FILE* a2 = cse320_fopen("filetest/file2", "r");
	char* m1 = (char*)cse320_malloc(sizeof(char)*23);
	char* m2 = (char*)cse320_malloc(sizeof(char)*234);
	
	cse320_clean();
	
	
	
		

	
	
	
	return 0;
}