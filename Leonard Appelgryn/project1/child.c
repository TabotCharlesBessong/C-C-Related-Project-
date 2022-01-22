#include<sys/types.h>
#include<unistd.h>
void program(void){
    processId child_processId;
    /*create a duplicate: child process */
    child_processId = fork();
    if(child_processId == -1)
    ERROR;
    else if(child_processId == 0)
    run_childProcess();
    else
    run_parentParent();
}