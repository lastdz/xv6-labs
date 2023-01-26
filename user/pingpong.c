#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int readall(int fd,void * p,int len){
    while(len>0){
        int n=read(fd,p,len);
        len-=n;
        p+=(n)/sizeof(void);
    }
    return 0;
}

int
main(int argc, char *argv[]){
    if(argc!=1){
        fprintf(2,"input error:no arg needed");
        return 1;
    }
    int fd[2];
    char buf[1];
    buf[0]=0;
    pipe(fd);
    int pid=fork();
    if(pid!=0){
        int curpid=getpid();
        buf[0]=pid;
        write(fd[1],buf,1);
        wait((int*)0);
        readall(fd[0],buf,1);
        fprintf(2,"%d: received pong\n",curpid);
    }else{
        readall(fd[0],buf,1);
        fprintf(2,"%d: received ping\n",(int)buf[0]);
        write(fd[1],buf,1);
        
    }
    exit(0);
}