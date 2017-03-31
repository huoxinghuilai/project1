#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc,char argv[]){
pid_t pid;
char cmd;
char *arg_psa[]={"ps","-a",NULL};
char *arg_psx[]={"ps","-x",NULL};
while(1){
printf("-----------------------\n");
printf("输入a执行'ps -a'命令\n");
printf("输入x执行'ps -x'命令\n");
printf("输入q退出\n")；
cmd=getchar();
if((pid=fork())<0){
perror("fork error:");
return -1;
}
if(pid==0){
switch(cmd){
case 'a':execve("/bin/ps",arg_psa,NULL);break;
case 'x':execve("/bin/ps",arg_psx,NULL);break;
case 'q':break;
default:perror("wrong cmd:\n");break;
}
exit(0);
}
else if(pid>0){
if(cmd=='q')
break;
}
}
while(waitpid(-1,NULL,WNOHANG)>0);
return 0;
}
