 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <errno.h>

 # define MAX_PROCESS 10

 typedef struct c_state child_stat;


 int main(int argc,char *argv[])
 {
 FILE *fp;
 pid_t child_pid[MAX_PROCESS];
 int status[MAX_PROCESS];
 int i=1;

switch(fork())
{
  case 0:
  for(i=1;i<argc;i++)
  {
 child_pid[i]=vfork();
 switch(child_pid[i])
 {
   case -1:
      printf("Error creating main child\n");
      abort();
      break;
   case 0:
         if(argv[i]==NULL)
         break;
     else
     status[i]=execl(argv[i],argv[i],(char*)NULL);
     if(status[i]==-1)
         exit(-1);
     break;
   default :
      printf("\ncommand : %s \n pid : %d\n status=%d\n",argv[i],child_pid[i],status[i]);
      break;
   }
 }
   default:
    wait(NULL);`enter code here`
    printf("\nAll done !! bye bye\n");
  }
 }


 //create a child process to execute any command

 #include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unist.h>
#include <stdlib.h>

#define LINE_MAX 255
#define ARG_MAX  10

#define SH_PROMPT "next> "

int run_command(char *[]);
int getline(char *);
void parse_line(char *, char*[]);

int main(void)
{
    char line[LINE_MAX+1];
    char *argbuf[ARG_MAX+!];
    int temp;

    do{
        printf(SH_PROMPT); fflush(stdout);
        if ((temp = getline(line)) != -1){
            parse_line(line, argbuf);
            run_command(argbuf);
        }
    } while (temp != -1);
    return 0;
}


int run_command(char *command[]){
    pid_t child;
    pid_t c;

    if ((child = fork()) == 0){
        execvp(command[0], command);
        fprintf(stderr, "Child process could not do execvp.\n");
        exit(1);
    }
    else{
        if(child == (pid_t)(-1)){
            fprintf(stderr, "Fork failed - Use spoon. \n");
            exit(1);
        }
        else {
            c = wait(NULL);
            return 0;
        }
    }
}
