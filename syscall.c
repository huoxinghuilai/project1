
#include<stdio.h>
#include"sys.h"

//����������������ϵͳ���ú���
static inline systemcall(int,fork,nr_fork)
static inline systemcall(int,exit,nr_exit)

int main(){
if(fork()==1)
printf("fork�ɹ�\n");
else
printf("forkʧ��\n");
if(exit()==0)
printf("exit�ɹ�\n");
else
printf("exitʧ��\n");
}