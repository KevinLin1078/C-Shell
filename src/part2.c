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
pthread_mutex_t lock;


int stop_file=0;
addr_in_use address[25];
files_in_use files[25];
int add_i = 0;
int file_i = 0;
int init =0;
int f_init = 0;

void* cse320_malloc(size_t size){
	if(size == 0){
        return NULL;
    }
	pthread_mutex_lock(&lock);
    if(init == 0){
        int i = 0;
        for(i = 0; i < 25; i++){
            address[i].ref_count =0;
        }
        init = 1;
    }

    if(add_i == 25){
        printf("Not enough memory\n");
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    
    
    void *ptr = malloc(size);
    address[add_i].addr = ptr;
    address[add_i].ref_count++;
    add_i +=1;
    pthread_mutex_unlock(&lock);
    return ptr;
}

int cse320_free(void *ptr){
	pthread_mutex_lock(&lock);
    int i =0;
    int found = 0;
    for(i= 0; i < 25; i++){
        if(ptr == address[i].addr){
            if(address[i].ref_count == 0){
                printf("Free: Double free attempt\n");
                errno = EADDRNOTAVAIL;
                pthread_mutex_unlock(&lock);
                return -1;
            }
            found = 1;
            //printf("i: %d \n", i);
            //free(address[i].addr);
            free(ptr);
            address[i].ref_count = 0;
        }
    }
    if(found != 1){
        printf("Free: Illegal address\n");
        errno = EFAULT;
        pthread_mutex_unlock(&lock);
        return -1;
    }
    pthread_mutex_unlock(&lock);
    return 0;
}

FILE* cse320_fopen(char* filename, char* mode){
	pthread_mutex_lock(&lock);
    if(f_init == 0){
        int i = 0;
        for(i = 0; i < 25; i++){   
            files[i].ref_count =0;
        }
        f_init = 1;
        
        FILE* ret;
        for(i = 0; i < 25; i++){
            if(files[i].ref_count == 0){
                FILE* f = fopen(filename, mode);
                files[i].filename = (char*)malloc(sizeof(char) * 255);
                strcpy(files[i].filename,filename);
                files[i].ref_count++;
                files[i].fd = fileno(f);
                files[i].f = f;
                ret = files[i].f;
                file_i +=1;
                break;
            }
        }
        pthread_mutex_unlock(&lock);
        return ret;
    }
    
    if(file_i > 25){
        printf("Too many opened ﬁles\n");
        
        pthread_mutex_unlock(&lock);
        
        return NULL;
    }
    int i = 0;
    for(i =0; i < file_i;i++){
        if(strcmp(filename, files[i].filename) == 0 ){
            files[i].ref_count++;
            pthread_mutex_unlock(&lock);
            return files[i].f;
        }
    }
    FILE* ret;
    if(file_i < 25){
        for(i = 0; i < 25; i++){
            if(files[i].ref_count == 0 ){
                FILE* f = fopen(filename, mode);
                files[i].filename = (char*)malloc(sizeof(char) * 255);
                strcpy(files[i].filename,filename);
                files[i].ref_count++;
                files[i].fd = fileno(f);
                files[i].f = f;
                ret = files[i].f;
                file_i +=1;     
                break;
            }   
        }

    }else{
        printf("Too many opened ﬁles\n");
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    pthread_mutex_unlock(&lock);
    
    return ret;
}
int cse320_fclose(FILE* fd){
    pthread_mutex_lock(&lock);
    int i =0;
    
    for(i= 0; i < 25; i++){
        if(fd == files[i].f){//change fd to filename
            if(files[i].ref_count == 0){
                printf("Close: Ref count is zero\n");
                errno = EINVAL;
                pthread_mutex_unlock(&lock);
                return -1;
            }else if(files[i].ref_count > 0){
                files[i].ref_count = 0;
                free(files[i].filename);
                fclose(files[i].f);
                file_i -=1;
                pthread_mutex_unlock(&lock);
                return 0;
            }
            pthread_mutex_unlock(&lock);
            return 0;//found it and closded it
        }
    }
    errno = ENOENT;
    printf("Close: Illegal filename\n");
    pthread_mutex_unlock(&lock);
    return -1;
}
void cse320_clean(){
	pthread_mutex_lock(&lock);
    int i = 0;
    for(i = 0; i< 25;i++){
        if(address[i].ref_count > 0){
            free(address[i].addr);
            address[i].ref_count = 0;
        }
        
        if(files[i].ref_count > 0){
        	//printf("Closing %d\n", i+1);
            free(files[i].filename);
            files[i].ref_count =0;
			fclose(files[i].f);  
        }
        
    }
    file_i = 0;
    pthread_mutex_unlock(&lock);
}

void display_file(){
	pthread_mutex_lock(&lock);
    int i = 0;
    for(i = 0; i< 25;i++){
        if(files[i].ref_count > 0){
            printf("%d: %s, %d\n", i+1, files[i].filename,files[i].ref_count);
        }else if(files[i].ref_count == 0   ){//&& i < file_i
            printf("%d: *****, %d\n",i + 1 ,files[i].ref_count);
        }

    }

    printf("----------------\n");
    pthread_mutex_unlock(&lock);
}

void display_add(){
	int i = 0;
    for(i = 0; i< 25;i++){
        if(address[i].ref_count > 0){
            printf("%d: %p, %d\n", i+1, address[i].addr, address[i].ref_count);
        }else if(files[i].ref_count == 0   && i < file_i){
            printf("%d: *****, %d\n",i + 1 ,address[i].ref_count);
        }

    }

    printf("----------------\n");
}