#include<stdio.h>
#include<fcntl.h>

#define CLOSE_DUP
#define USE_DUP2

int main(){
int fd;
int newfd;
char line[100];

fgets(line,100,stdin);printf("%s",line);
fgets(line,100,stdin);printf("%s",line);
fgets(line,100,stdin);printf("%s",line);

fd=open("data",O_RDONLY);
printf("%d ",fd);

#ifdef CLOSE_DUP
close(0);
newfd=dup(fd);
#else
newfd=dup2(fd,0);
#endif
printf("%d ",newfd);

if(newfd!=0){
fprintf(stderr,"could not duplicate fd to 0\n");
exit(1);
}
close(fd);

fgets(line,100,stdin);printf("%s",line);
fgets(line,100,stdin);printf("%s",line);
fgets(line,100,stdin);printf("%s",line);

}
