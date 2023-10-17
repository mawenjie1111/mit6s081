#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc,char *argv[])
{
    int pid;
    int fds[2];
    pipe(fds);
    pid=fork();
    if(pid==0){
        char buf[1]={'\0'};
        int len=read(fds[0],buf,1);
        close(fds[0]);
        if (len==1){
            printf("%d: received ping\n",getpid());
            write(fds[1],buf,1);
            close(fds[1]);
            exit(1);
        }
    }
    else{
        write(fds[1],"1",1);
        close(fds[1]);
        char buf[1]={'\0'};
        int len=read(fds[0],buf,1);
        close(fds[0]);
        if (len==1)
        {
            printf("%d: received pong\n",getpid());
            exit(1);
        }
    }
    exit(1);
}