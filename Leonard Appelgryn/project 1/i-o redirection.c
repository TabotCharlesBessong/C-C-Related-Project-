int fd;
int pid = fork();
int current_out;

if (in) { //if '<' char was found in string inputted by user
    fd = open(input, O_RDONLY, 0);
    dup2(fd, STDIN_FILENO);
    in = 0;
    current_out = dup(0);
}

if (out) { //if '>' was found in string inputted by user
    fd = creat(output, 0644);
    dup2(fd, STDOUT_FILENO);
    out = 0;
    current_out = dup(1);
}

if (pid == -1) {
    perror("fork");
} else if (pid == 0) {
    execvp(res[0], res);
    perror("execvp");
    _exit(1);
} else {
    waitpid(pid, 0, 0);
    dup2(current_out, 1);
    free(res);
}
