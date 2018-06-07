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



pthread_mutex_t lock;
addr_in_use *address = NULL;
addr_in_use *head = NULL;
files_in_use* file_head = NULL;
files_in_use* file_add = NULL;

int delete = 0; 

void* cse320_malloc(size_t size){
	if(size == 0){
        return NULL;
    }
    pthread_mutex_lock(&lock);
    if(address == NULL){
    	
		void* p = malloc(size);
		address = (addr_in_use*)malloc(sizeof(addr_in_use));
		address->addr = p;
		address->ref_count = 1;
		address->next = NULL;

		address->d = delete;//-----------------------------
    	delete++;//-------------------------------------    	

    	head = address;
    	pthread_mutex_unlock(&lock);
    	return p;
    }else if(head != NULL){
    	addr_in_use* pointer = head;
    	while(pointer->next != NULL){
    		pointer = pointer->next;
    	}

    	addr_in_use* add_new =(addr_in_use*)malloc(sizeof(addr_in_use));
    	void* temp = malloc(sizeof(size));
    	add_new->addr = temp;
    	add_new->ref_count = 1;
		
		add_new->d = delete;//------------------------
		delete++;//--------------------------

		add_new->next = NULL;
		pointer->next = add_new;
		pthread_mutex_unlock(&lock);
		return temp;
    }
}

int cse320_free(void *ptr){
	pthread_mutex_lock(&lock);
	if(head != NULL ){
		addr_in_use* pointer = head;
		if(head->addr == ptr){
			head = pointer->next;
			free(pointer->addr);
			free(pointer);
			pthread_mutex_unlock(&lock);
			return 1;
		}
		addr_in_use* current  = NULL;

		while(pointer->addr != ptr && pointer->next != NULL){
			current = pointer;
			pointer = pointer->next; 
		}
		if(pointer->next == NULL || pointer->addr != ptr){
			printf("Free: Illegal address\n");
			pthread_mutex_unlock(&lock);
			return -1;
		}
		if(pointer->addr == ptr){
			current->next = pointer->next;
			free(pointer);
			free(pointer->addr);
			pthread_mutex_unlock(&lock);
			
		}
		return 0;
	}
	printf("Free: Illegal address\n");
	return -1;

}

int start = 0;
FILE* cse320_fopen(char* filename, char* mode){
	pthread_mutex_lock(&lock);
	if(file_head == NULL){
		FILE* ret;
		FILE* f = fopen(filename, mode);
		file_head = (files_in_use*)malloc(sizeof(files_in_use));
		file_head->filename = (char*)malloc(sizeof(char)*255);
		strcpy(file_head->filename, filename);
		file_head->ref_count =1;
		file_head->fd = fileno(f);
		file_head->f = f;
		file_head->next = NULL;

		ret = file_head->f;
		pthread_mutex_unlock(&lock);
		return ret;
	}
	FILE* ret;
	files_in_use* pointer = file_head;
	while(pointer->next != NULL && strcmp(pointer->filename, filename) != 0){
		pointer = pointer->next;
	}
	if(strcmp(pointer->filename, filename) == 0){
			pointer->ref_count +=1;
			return pointer->f;
	}

	FILE* f = fopen(filename, mode);
	files_in_use* new_file = (files_in_use*)malloc(sizeof(files_in_use));
	new_file->filename = (char*)malloc(sizeof(char)*255);
	strcpy(new_file->filename, filename);
	new_file->ref_count =1;
	new_file->fd = fileno(f);
	new_file->f = f;
	new_file->next= NULL;
	pointer->next = new_file;

	ret = new_file->f;
	return ret; 

}



int cse320_fclose(FILE* fd){
	pthread_mutex_lock(&lock);
	if(file_head != NULL){
		files_in_use* pointer = file_head;
		if(file_head->f == fd){
			file_head = pointer->next;
			fclose(pointer->f);
			free(pointer->filename);
			free(pointer);
			pthread_mutex_unlock(&lock);
			return 1;
		}
		files_in_use* current = file_head;

		while(pointer->f != fd && pointer->next != NULL){
			current = pointer;
			pointer = pointer->next;
		}
		if(pointer->next == NULL || pointer->f != fd){
			printf("Close: Illegal filename\n");
			pthread_mutex_unlock(&lock);
			return -1;
		}
		if(pointer->f == fd){
			current->next = pointer->next; 
			free(pointer->filename);
			fclose(pointer->f);
			free(pointer);
			pthread_mutex_unlock(&lock);
		}

		return 1;
	}

	printf("Close: Illegal filename\n");

}








void displayfile(){

	files_in_use* pointer = file_head;
	while(pointer != NULL){
		printf("%s, %d\n", pointer->filename, pointer->ref_count );
		pointer = pointer->next;
	}
	printf("-------------------------\n");
}



void display(){
	addr_in_use* pointer = head;
	if(pointer != NULL){
		addr_in_use* pointer = head;
		while(pointer != NULL){
			//sleep(1);
			printf("%d : %p\n", pointer->d + 1, pointer->addr);
			pointer = pointer->next;
		}
		printf("-------------------------\n");
	}


}