#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

void run(char *program, char **args) {
	if(fork() == 0) { // child exec
		exec(program, args);
		exit(0);
	}
	return; // parent return
}

int main(int argc,char* argv[])
{   
    char* buf[MAXARG];
    char para[MAXARG];
    char* p = para, *last_p = para; 
    char** buf_p=buf, **buf_p2=buf;
    for(int i=1;i<argc;i++)
    {   
        buf[i-1]=malloc(strlen(argv[i]+1));
        strcpy(buf[i-1],argv[i]);
        buf_p++;
    }
    buf_p2=buf_p;
    while (read(0,p,1)!=0)
    {
        if(*p==' '|| *p=='\n'){
            *p='\0';
            *(buf_p2++)=last_p;
            last_p=p+1;
            if(*p=='\n'){
                *buf_p2=0;
                run(buf[0],buf);
                buf_p2=buf_p;
            }
        }
        p++;
        /* code */
    }
    if(buf_p2!=buf_p){
        *p='\0';
        *(buf_p2++)=last_p;
        *buf_p2=0;
        run(buf[0],buf);
    }
    while(wait(0) != -1) {}; // 循环等待所有子进程完成，每一次 wait(0) 等待一个
	exit(0);
}