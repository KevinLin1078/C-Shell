#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



void* cse320_malloc(size_t size);
int cse320_free(void *ptr);

FILE* cse320_fopen(char* filename, char* mode);
int cse320_fclose(FILE* fd);

void cse320_clean();

void cse320_settimer(int N);
pid_t cse320_fork();



void display_file();
void display_add();



typedef struct addr_in_use{
	void *addr;
	int ref_count;

}addr_in_use;

typedef struct files_in_use{
	 char* filename;
	 int ref_count;
	 int fd;
	 FILE* f;
}files_in_use;
