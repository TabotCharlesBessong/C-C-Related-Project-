 
/*
This project consists of designing a C program to serve as a shell interface that accepts user commands and then executes each command in a separate process. A shell interface gives the user a prompt, after which the next command is entered.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 1024 // max length of command
#define MAX_PATH 1024

/*
	main function, all logic contained
*/
int main(void) {
	int run = 1; // flag to determine when to exit program
	
	char cmd[MAX_LINE]; // command input
	char cwd[MAX_PATH]; // directory with max path 
	const char delim[] = " \t\r\n\v\f"; // delimiter to remove all spaces and extraneous chars
	char *token[256]; // token char for strtok
	size_t len; // simple flag check to make sure users type a command or not
	
	pid_t bg_pids[50]; // stores background process pids
	int bg_count = 0; // number of pids running in background
	
	// run while flag is true
	while (run) { 
		
		// get current working directory for use with cd, print along with daniel_ish:
   		if (getcwd(cwd, sizeof(cwd)) != NULL) {} 
   		else { perror("getcwd() error");
       		return 1;
   		}
	
		printf("Xenunmakuzi ~%s: ", cwd); // print prompt
		fflush(stdout);
	
		// get user command input
		int i = 0; // i is global variable for number of total arguments
		if (fgets(cmd, sizeof cmd, stdin)) {
			token[i] = strtok(cmd, delim); // tokenize cmd
			
			while (token[i] != NULL) {
				i++; // increment to loop
				token[i] = strtok(NULL, delim); // store null terminator at end of array
			}
		}
		
		/*
			After reading user input, the steps are:
			1) fork a child process using fork() 
			2) the child process will invoke execlp()
			3) if command included & parent will invoke wait()
		*/
		
		// check to see if user entered any chars, continue if returns 1
		len = strlen(cmd); 
		if (len == 1) {
			continue; 
		} 
		
		// exit shell if first token of string is "exit"
		if (strcmp("exit", cmd) == 0) {
			run = 0; // run flag is false
			return 1;
		} 
		
		// if cd command 
  		int cdf = 0; // cd flag false
  		if (strcmp(token[0], "cd") == 0) {
  			cdf = 1; // cd flag true 
			if (chdir(token[1]) == 0) {} // do cd on path specified
			else if (i == 1) { chdir("/"); } // if only cd is typed
			else { printf("cd: %s: No such file or directory\n", token[1]); } // if dir not found, error 
			continue;
  		}
		
		// if fg is entered
		if (strcmp(token[0], "fg") == 0) {
			if (bg_count != 0) {
			 	pid_t bg_pid = bg_pids[bg_count-1]; // get bg pid and put it in array 
				waitpid(bg_pid, NULL, 0); // wait until done
				bg_count--; // decrement on finish
			}
			
			continue;
		}
		
		// if & is entered for bg
		int bgf = 0; // background process flag
		if (strcmp(token[i-1], "&") == 0) {
			bgf = 1; // background set to true
			token[--i] = NULL; // remove & arg
		}
		
		// if pipe is found
		int pipef = 0; // pipe flag
		int n = 0; // loop index
		int p; // store index of pipe
		char *prog1[256]; // stores commands before pipe
		char *prog2[256]; // stores commands after pipe
		while (n < i) {
		  	if (strcmp(token[n], "|") == 0) {
		  		pipef = 1; // pipe flag to true
		  		p = n; // get index of pipe
		  		
		  		// 0 to p-1 are commands before pipe
		  		// p+1 to i are commands after pipe
		  		
		  		n++;
		  		
		  		// loop to load first program
				int v = 0;
				while (v <= p-1) { // loop up until the pipe
					prog1[v] = token[v]; // load linearly
					v++; // increment to loop
					prog1[i] = strtok(NULL, delim); // store null at end of array
				}
				
				int k = p+1; // start of commands after pipe
				int l = 0; // index to store at new array prog2
				while (k <= i) {
					prog2[l] = token[k]; // store k at l to i indexes of prog2
					l++; // increment prog2
					k++; // increment loop index
				}
		 	}
		  			
		  	n++; // increment main loop index
		}
		
		// if > symbol entered
		int rdf = 0; // redirect flag
		for (int c = 0; c < i; c++) {
  			if (strcmp(token[c], ">") == 0) {
  				rdf = 1;
  			}
		}

 		pid_t pid = fork(); // fork!
 		
		// fork failed
		if (pid < 0) {
			return 1;
		}

		// child process
		if (pid == 0) { 
		
			// if pipe flag true
			if (pipef == 1) {
				int pfd[2]; // open read/write pipe fd
				pipe(pfd); // pipe 

				if (fork() == 0) {      
				    close(STDOUT_FILENO); //close stdout 
				    dup(pfd[1]); //assign stdout to copy fd pipe for write 
				    close(pfd[1]); // close write end of pipe

				    execvp(prog1[0], prog1); // exec on first set of arguments before pipe
				}

				if (fork() == 0) {
				    close(STDIN_FILENO); // close stdin
				    dup(pfd[0]); // assign stdin to copy fd pipe for read
				    close(pfd[0]); // close read end of pipe

				   	execvp(prog2[0], prog2); // exec on second set of arguments after pipe
				}
				
		   	 	wait(NULL);	// wait 
			}  
			
			// if ridirect flag true
			if (rdf == 1) {
				FILE *fp1; // first file pointer
				FILE *fp2; // second file pointer
					
				// open read/write files, check read file if DNE (write file will create if DNE)
				fp1 = fopen(token[1], "r");
				fp2 = fopen(token[3], "w");
				if (fp1 == NULL) {
					fprintf(stderr, "%s: No such file or directory\n", token[1]);
					return 0;
				}						
				
				dup2(fileno(fp1), STDIN_FILENO); // copy fp1 to stdin
				dup2(fileno(fp2), STDOUT_FILENO); // copy fp2 to stout
						
				// close files
				fclose(fp1); 
				fclose(fp2);
						
				// pass in file arguments to execvp {"cat", "file2", "file1", NULL}
				char *arg[] = {token[0], token[3], token[1], 0};
				execvp(arg[0], arg); // exec on args
			
			}
			
			execvp(token[0], token); // exec on path, with commands	
			
			// if command is not found, print error message	
			if (cdf) {} 
			else { printf("\nCommand '%s' not found\n\nTry: apt install <deb name>\n\n", cmd); }
			return 0;
		} 
		
		// parent process
		else { 
			// if background flag, parent won't wait
			if (bgf) {
				bg_pids[bg_count] = pid; // add pid to array of background processes at end
				bg_count++; // increment background process number
				printf("[%d]+ Running (pid: %d) %s\n", bg_count, pid, cmd); // print pid info
			} else {
				waitpid(pid, NULL, 0); // make parent wait
			}
		}
		
	}
	
	return 0; 
}
