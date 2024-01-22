#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char* argv[])
{
    int flag[2];
    pipe(flag);
    int pids=fork();
    int p,q;
    if (pids<0){
        printf("fork error");
    }
    if(pids==0){
        read(flag[0],(char*)&p,sizeof(p));
        int id=getpid();
        printf("%d: received ping\n",&id);
        write(flag[1],"1",1);
        close(flag[0]);
        exit(0);
    }
    else{

        write(flag[1],"1",1);
        close(flag[1]);
        read(flag[0],(char*)&q,sizeof(q));
        int id=getpid();
        printf("%d: received pong\n",&id);
        exit(0);
    }    
    return 0;

}