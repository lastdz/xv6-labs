#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int *);
void exitprime();
int ans[37];
int cnt=0;
int main(int argc,char *argv[]){
    int fd1[2];
    int buf1[1];

   while(pipe(fd1)!=0){

   }
    int pid=fork();
    if(pid>0){
        close(fd1[0]);
        int i;
        for(i=2;i<=35;i++){
            buf1[0]=i;
            //fprintf(2,"%d",i);
            write(fd1[1],buf1,4);
        }
        buf1[0]=113;
        write(fd1[1],buf1,4);
        close(fd1[1]);
        wait((int*)0);
    }else{
        prime(fd1);
        wait(0);
    }
    exit(0);
}
void prime(int *f1){
    close(f1[1]);
    int buf1[1];
    int p=0;
    int pid=-1;
    int fd1[2];
    while(pipe(fd1)!=0);
    while(1){
        read(f1[0],buf1,4);
        if(buf1[0]==113){
            close(f1[0]);
            write(fd1[1],buf1,4);
            close(fd1[1]);
            wait(0);
            exit(0);
        }
        if(p==0){
            p=buf1[0];
            if(p!=113)fprintf(2,"prime %d\n",p);
            if(buf1[0]==113)exit(0);
        }else{
                int num=buf1[0];
                if(num%p==0){
                    continue;
                }
                if(pid==-1){
                    pid=fork();
                }
                if(pid==0){
                    prime(fd1);
                    wait(0);
                }
                if(pid>0){
                    write(fd1[1],&num,4);
                }
        }
    }
}
void exitprime(){
    exit(0);
}