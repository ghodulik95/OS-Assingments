#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(){
    /*** Variables for calculating runtime later ***/
	time_t begin;
	time(&begin);
	time_t end;
	double runtime;
	
	pid_t pid;
	int f1;
	int f2;
	f1 = 1;
	f2 = 1;
	
	//Make first child
	pid=fork();
	
	//Check if there was a fork error
	if( pid<0 ){
		printf("error in fork!");
    }
    //If this is the firts child
	else if(pid == 0){
	    int i;
	    
	    for( i = 1; i <= 10; i += 2){
	        f2 = f1 + f2;
	        f1 = f1 + f2;
            printf("The process id %d produced the Fibonnaci number f%d as %d\n", getpid(), i+3, f1);  
            
            sleep(2);
	    }
	}
	//If this is the parent
	else{
	    //Make second child
	    pid = fork();
	    //Check for errors
	    if( pid<0 ){
		    printf("error in fork!");
        }
        //If this is the second child
	    else if(pid == 0){
	        int i;
	        sleep(1);
	        f1 = f1 + f2;
	        for( i = 2; i <= 10; i += 2){
	            f2 = f1 + f2;
	            f1 = f1 + f2;
                printf("The process id %d produced the Fibonnaci number f%d as %d\n", getpid(), i+3, f1);
                
                sleep(2);
            }
	    }
	}
	
	//Parent waits for children to finish (otherwise the parent finished
	//super quickly and the children become orphans!)
	wait();
	
	/*** 1) Get username, parent and child processes' real and effective ***
	 ***    user ids, and their group ids                                ***/
	//Allocate a string of size 10
	char buf[10];
	//Save username to string
	cuserid(buf);
	//Print username, parent process id, group id, euid and uid
	printf("\nProcess id %d is being run by user %s\n", getpid(), buf);
	//If this is the parent process
	if( pid > 0 ){
	    printf("Process id %d is the parent process\n", getpid() );
	    //Get and print the cwd
	    char cwd[1024];
	    getcwd(cwd, sizeof(cwd) );
	    printf("Current directory is %s\n", cwd);
	}
	//If this is either child, print the parent process id
	else{
	    printf("Process id %d has parent process id %d\n", getpid(), getppid() ); 
	}
	printf("Process id %d has group id %d\n", getpid(),  getpgrp() );
	printf("Process id %d has real user id %d\n", getpid(),  getuid() );
	printf("Process id %d has effective user id %d\n", getpid(),  geteuid() );
	
	//Caluclate runtime
	time(&end);
	runtime = (double) (end - begin);
	
	//Print runtime
	printf("Process id %d took %f seconds to execute\n", getpid(), runtime);
	
	//Wait again, so there are no print statments in my command line
	wait();
	exit(0);
}
