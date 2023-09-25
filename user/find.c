#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), '\0', DIRSIZ-strlen(p));
  return buf;
}

void
find(char *path,char *target)
{
  //buf存储了文件路径，p指向buf最后一位
  char buf[512], *p;
  int fd;

  struct dirent de;
  struct stat st;

  //打开一个文件符
  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }
  //获取文件状态，st存储了文件符信息
  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
  //判断文件符类型
  switch(st.type){
  case T_FILE:
  {
    //printf("比较文件\n");
    char *fe =fmtname(path);
    //printf("%s %s\n",fe,target);
    if(strcmp(target,fe)==0)
    {
      printf("%s\n",path,fe);
    }
    //printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;
  }
  case T_DIR:
    //越界处理
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    // printf("比较文件夹名\n");
    // char *fe2 =fmtname(path);
    // if(strcmp(target,fe2)==0)
    // {
    //   printf("%s/%s\n",path,fe2);
    // }
    // //把path拷贝给buf
    // printf("比较文件名\n");
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if((de.inum == 0) || (strcmp(de.name, ".") == 0) || (strcmp(de.name, "..") == 0)){
                    continue;
                }
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      //printf("%s %s\n",buf,target);
      find(buf,target);
    }
    break;
  }
  close(fd);
}



int main(int argc, char  *argv[])
{
    if (argc!=3){
        exit(1);
    }
    else{
        char *path=argv[1];
        char *target=argv[2];
        find(path,target);
        exit(0);
    }
    /* code */
    return 0;
}
