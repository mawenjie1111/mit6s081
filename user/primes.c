#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int *fds)
{
    close(fds[1]);
    int p,q;
    if(read(fds[0],(char*)&p,sizeof(p))==sizeof(p))
    {
        printf("primes %d\n", p);
        int fds1[2];
        pipe(fds1);
        int pid=fork();
        if(pid!=0)
        {
            while (read(fds1[1],(char*)&q,sizeof(q)))
            {
                /* code */
                if (q%p!=0)
                {
                    write(fds1[1],(char*)&q,sizeof(q));
                }
            }
            close(fds1[1]);
            close(fds1[0]);
            wait(0);
          
        }
        else{
            primes(fds);
        }
        
    }
    exit(1);
}


int
main(int argv,int argc[])
{

    int start=2;
    int end=35;
    int fds[2];
    pipe(fds);
    int pid=fork();
    if(pid!=0)
    {
        close(fds[0]);
        for (int i = start; i <=end; i++)
        {
            /* code */
            write(fds[1],(char *)&i,sizeof(i));
        }
        close(fds[1]);
        wait(0);
    }
    else{
        primes(fds);
    }
    exit(1);
}
