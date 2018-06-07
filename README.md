# Kevin Lin


# Welcome to my SHELL
## **Part 1**
- Thank you for your time to read this :)

- In order to successfully run part1, go to the Linux terminal.
- Type "make" to compile the .c files for part 1

```
make
```
- Now that you have compiled part 1, it's time to run it
- Kindly type "./part1" to execute the program
```
./part1
```
- After executing ./part1, "CSE320->" will show up.
```
CSE320->
``` 
- Type "help" to see the available commands

```
CSE320->help
``` 
- Hope you enjoy my simple shell :)


## **Part 2.1 (Malloc & Free)**

- To compile part 2, be aware that all of the functions listed here belongs in src/part2.c
- Here is a sample command to compile part2 along with **your** main c file.
MAKE SURE YOU CREATE YOUR **main.c** file inside src folder
- I already created **main.c** with an empty **int main()**, free feel to use it.  
```
gcc src/part2.c src/main.c ./part2
```


### cse320_malloc()
```
void* cse320_malloc(size_t size);
							returns void* on success, NULL on failure
```
 - When this function is called, it returns a void pointer with the size allocated by the user. When cse320_malloc() is called, it will store the values of the pointer requested by the user in  ***struct add_in_use***, which can store up to only 25 malloc requests.<br /> <br />

### cse320_free()
```
int cse320_free(void *ptr)
						returns -1 on error, 0 on success
```
- When this function is called, it return an integer indicating whether a pointer is properly freed or not. A **-1**
indicates that a **free illegal address** occurred or a **double free attempt**.

<br />
## **Part 2.2 (File Open & Close)**

<br />

## cse320_fopen()
```
FILE* cse320_fopen(char* filename, char* mode);
										returns FILE* on success, NULL on failure
```
- This function returns **FILE***. This function calls fopen() with in cse320_fopen(), but return an **integer** representing a file descriptor. 
- Here is an example of how to use this function

    ```
	FILE* fd = cse320_fopen("file.txt", "r");
    ```

* Don't mistaken fopen() with open() as fopen() and open() take in different arguments. This function is based on **fopen()**.


<br /><br />

## cse320_fclose()
```
int cse320_fclose(FILE* fd);
//Be aware this function takes in FILE* as parameter
											returns -1 on error, 0 or 1 on success
```
- This function closes a file based on ***FILE****, 
- Here is a sample usage of this function <br /> 

    ``` 
	FILE* fd = cse320_fopen("file.txt", "r");
	cse320_fclose(fd);
    ```   

<br /> <br />
## **Part 2.3(Clean)**
## cse320_clean()
```
void cse320_clean();
```
- When this function is called, it will free and close all the addresses and files in two structs, respectively, with **ref_count** greater than zero

<br />

## **Part 3(Fork and Alarm)**

- To compile part 3, be aware that all of the functions listed here belongs in src/part3.c
- Here is a sample command to compile part2 along with **your** main c file.
MAKE SURE YOU CREATE YOUR **main.c** file inside src folder
- I already created **main.c** with an empty **int main()**, free feel to use it.  
```
gcc src/part3.c src/main.c ./part3
```

## cse320_settimer()
```
void cse320_settimer(int N);
```
- When this function is called, it will set the timer to N seconds and invoke the SIGALRM to reap all the child processes.
- Here is a sample usage of this function

	```
	pid_t pid = cse320_fork();
	cse320_settimer(4);
	if(pid == 0 ){
		.....
	}
	
	```

<br />

## cse320_fork()
```
pid_t cse320_fork();
```
* This function works exactly like fork. It returns the pid when called and it also prints an error message when pid is less than 0.

# Additional 
- To compile part 2 **AND** part 3, be aware that all of the functions listed here belongs in src/part2.c and src/part3.c
- Here is a sample command to compile part2 and part3 along with **your** main c file.
MAKE SURE YOU CREATE YOUR **main.c** file inside src folder
- I already created **main.c** with an empty **int main()**, free feel to use it.  
```
gcc src/part2.c src/part3.c src/main.c ./part23
```