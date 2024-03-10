//
// Created by deivih84 on 3/6/24.
//
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{

    // make two process which run same
    // program after this instruction
    pid_t p = fork();
    pid_t p1 = fork();
    if(p<0){
        perror("fork fail");
        exit(1);
    } else if (p == 0) {
        printf("soy el hijo0");
        printf("Hello world!, process_id(pid) = %d \n",getpid());
    }
    if (p1 == 0) {
        printf("Hello world!, process_id(pid) = %d \n",getpid());
    }
    return 0;
}
