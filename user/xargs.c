#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char const *argv[])
{

    char buf[MAXARG];
    int j=0;
    while (read(0,buf+j,1))
    {
        printf("%c\n",buf[j]);
        /* code */
        j++;
    }
    exit(0);
}
