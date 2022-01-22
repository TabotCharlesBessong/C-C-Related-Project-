#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE 80

char *history[10][MAX_LINE];
int po;




void setup(char inputBuffer[], char *args[],int *background)
{
     int length,
      i,
      start,
      ct;

  ct = 0;

   length = read(STDIN_FILENO, inputBuffer, MAX_LINE);

   start = -1;
   if (length == 0)
     exit(0);
  if (length < 0){
     perror("error ");
     exit(-1);
     }


  for (i = 0; i < length; i++) {
     switch (inputBuffer[i]){
     case ' ':
     case '\t' :
         if(start != -1){
            args[ct] = &inputBuffer[start];
            ct++;
         }
         inputBuffer[i] = '\0';
       start = -1;
         break;

     case '\n':
         if (start != -1){
             args[ct] = &inputBuffer[start];
             ct++;
          }
         inputBuffer[i] = '\0';
         args[ct] = NULL;
         break;

     case '&':
         *background = 1;
         inputBuffer[i] = '\0';
         break;

     default :
         if (start == -1)
             start = i;
       }
   }
 args[ct] = NULL;
 }



int main(void)
 {
     char inputBuffer[MAX_LINE];
     int background;
     char *args[MAX_LINE/2+1];

while (1){
    background = 0;
    printf("os>");
        fflush(0);
        setup(inputBuffer, args, &background);

    /**
 * After reading user input, the steps are:
 * (1) fork a child process using fork()
 * (2) the child process will invoke execvp()
 * (3) if command included &, parent will invoke wait()
 */

    pid_t pid = fork();
    printf("Fork created.\n");
/*
 For example, if the
 user enters the command ps -ael at the osh> prompt, the values stored in the
 args array are:
 args[0] = "ps"
 args[1] = "-ael"
 args[2] = NULL
 This args array will be passed to the execvp() function, which has the
 following prototype:
 execvp(char *command, char *params[]);
 */

    if(pid < 0){
        printf("Fork failed.\n");
    }else if(pid == 0){
        if( strcmp(args[0],"history") == 0){ /*  Print History */
            displayHistory();
        }else if(strcmp(args[0],"r") == 0){ /*  r num */
            int index = (int) args[1];
            /*runHistoryAt( index - 1);*/
        }else if(strcmp(args[0],"rr") == 0){ /*  Run recent */
            /*runHistoryAt(0);*/
        }else{  /*  Execute normally */
            printf("executing..., adding to history buffer\n");
            /* Add args to history buffer */
            int j;
            for (j = 0; j < sizeof(args); j++) {
                history[po][j] = args[j];
            }
            po = (po + 1) % 10;
            /* Execute!  */
            execvp(args[0],args);
        }
    }

        if(background == 0){
            wait(NULL);
            }else{
               setup(inputBuffer, args, &background);
           }
         }
    }
