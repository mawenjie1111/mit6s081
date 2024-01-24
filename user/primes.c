#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void solution(int *flag)
{
    close(flag[1]);
    int n;
    if(read(flag[0],&n,sizeof(n))==0) return;
    printf("prime %d\n", n);

    int flag2[2];
    pipe(flag2);
    int pids=fork();
    
    if (pids>0){
        close(flag2[0]);
        int m;
        while(read(flag[0],&m,sizeof(n))){
            if(m % n){
                write(flag2[1],&m,sizeof(m));
            }
        }
        close(flag[0]);
        close(flag2[1]);
        wait(0);
    }
    else{
        close(flag2[1]);
        solution(flag2);
        close(flag[0]);
    }
    exit(0);
}

int main(int argc,char *argv[])
{
    int flag[2];
    pipe(flag);
    int start=2,end=35;
    int pids=fork();
    if (pids>0){
        close(flag[0]);
        for (int i = start; i <= end; i++)
        {
            write(flag[1],&i,sizeof(i));
            /* code */
        }
        close(flag[1]);
        wait(0);
    }
    else{
        solution(flag);
    }
    exit(0);
    return 0;
}