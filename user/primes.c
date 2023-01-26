#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime(int *,int *);
void exitprime();
int ans[37];
int cnt=0;
int main(int argc,char *argv[]){
    int fd1[2];
    int fd2[2];
    int buf1[1];
    int buf2[1];

    pipe(fd1);
    pipe(fd2);
    int pid=fork();
    if(pid>0){
        int i;
        for(i=2;i<=35;i++){
            buf1[0]=i;
            //fprintf(2,"%d",i);
            write(fd1[1],buf1,4);
            read(fd2[0],buf2,4);
        }
        buf1[0]=113;
        write(fd1[1],buf1,4);
        read(fd2[0],buf2,4);
        wait((int*)0);
    }else{
        prime(fd1,fd2);
        wait(0);
    }
    exit(0);
}
void prime(int *f1,int *f2){
    int buf1[1];
    int buf2[1];
    int nums[40];
    int cnt=0;
    int p=0;
    int pid=-1;
    while(1){
        read(f1[0],buf1,4);
        write(f2[1],buf2,4);
        if(p==0){
            p=buf1[0];
            if(p!=113)fprintf(2,"%d prime\n",p);
            if(buf1[0]==113)exit(0);
        }else{
                int num=buf1[0];
                if(num%p==0){
                    continue;
                }
                nums[++cnt]=num;
                if(buf1[0]==113)break;
        }
    }
    pid=fork();
    if(pid>0){
        int i;
        for(i=1;i<=cnt;i++){
            buf1[0]=nums[i];
            write(f1[1],buf1,4);
            read(f2[0],buf2,4);
        }
        wait(0);
    }else{
        prime(f1,f2);
        wait(0);
    }
    exit(0);
}
void exitprime(){
    exit(0);
}