#include<stdio.h>
#include<signal.h>
main(){
void wakeup(int);
printf("about to sleep for 4 seconds\n");
signal(SIGALRM,wakeup);
alarm(4);
pause();
printf("morning so soon?\n");
}
void wakeup(int signum){
#ifndef SHHHH
printf("alarm received from kernel\n");
#endif
}

