#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[]){
    
    char buf[1];
    char *argxx[MAXARG];
    char buff[1024];
    int bufcnt=0;
    int argxc=1;
    int i;
    for(i=2;i<argc;i++){
        argxx[argxc++]=argv[i];
    }
    argxx[0]=malloc(16);
    while(read(0,buf,1)>0){
        buff[bufcnt]=buf[0];
        if(buff[bufcnt]==' '){
            buff[bufcnt]=0;
            char *p=malloc(sizeof(char)*(bufcnt+1));
            //fprintf(2,"%s",p);
            strcpy(p,buff);
            argxx[argxc++]=p;
            bufcnt=0;
        }else if(buff[bufcnt]=='\n'){
            buff[bufcnt]=0;
            char *p=malloc(sizeof(char)*(bufcnt+1));
            strcpy(p,buff);
            argxx[argxc++]=p;
            bufcnt=0;
            int pid=fork();
            if(pid==0){
                //fprintf(2,"%d %s %s %s\n",argxc,argxx[0],argxx[1],argxx[2]);
                exec(argv[1],argxx);
                exit(0);
            }else{
                wait(0);
                for(int i=argc-1;i<argxc;i++)free(argxx[i]);
                argxc=argc-1;
            }
        }else{
            buff[bufcnt++]=buf[0];
        }
    }
    exit(0);
}