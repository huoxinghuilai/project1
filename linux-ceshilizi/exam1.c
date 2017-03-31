#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 100//��صĺ궨��
#define NIL -1
#define false 0
#define true 1

struct sem{//������̵���Ϣ�ṹ��
int num;
int pro;
struct sem *next;
};


struct task{//��������ṹ��

int id;//���
char state;//״̬
int next;//�ȴ�ͬһ���ź�������һ������
struct sem *s;//��Ϣ
int count;//���д���
char addr;//����ʱ�ĵ�ַ
int prio;//���ȼ�
};

struct sign{//�����ź����ṹ��
int value;
int first;//�ȴ����ź����ĵ�һ������
};

struct task pcb[4];//������ȫ�ֱ���
struct sign si[3];
char addr;
int i,seed,exe;

void eexit(int n){
	pcb[n].state='c';
	printf("prcess %d is completed\n",n);
	exe=NIL;
}

void send(int sender,int receiver,int snum){//���̷�����Ϣ

struct sem *p,*q;//������������Ϣ�ṹ��
p=(struct sem *)malloc(sizeof(struct sem));//����ռ�
p->num=snum;//p->num���д���
p->next=NULL;//ָ�����һ���ڵ�Ϊ��
p->pro=sender;//p->proΪ���ͽ��̵ı��
printf("send message to %d process\n",receiver);
printf("process %d already run %d times\n",sender,snum);

q=pcb[receiver].s;//qΪ���ս��̵���Ϣָ��
if(q==NULL)
pcb[receiver].s=p;
else{
while(q->next!=NULL)
q=q->next;
q->next=p;
}
}

void wakeup(int se){

int w;
w=si[se].first;
if(w!=NIL){
si[se].first=pcb[w].next;
pcb[w].state='r';
printf("process %d is wakeup\n",w);
}
} 

int v(int se,char ad){

si[se].value=si[se].value+1;
if(si[se].value>0)
return false;
else{
wakeup(se);
pcb[exe].count=i;
pcb[exe].addr=ad;
return true;
}
}

float random(){

int m;
if(seed<0)
m=-seed;
else
m=seed;
seed=(25171*seed+13841)%65536;
return (float)(m/32767.0);
}

int timeint(char ad){

float x;
x=random();
if((x<0.33)&&(exe==1))
return false;
if((x<0.66)&&(exe==2))
return false;
if((x<1.00)&&(exe==3))
return false;
else{
pcb[exe].count=i;
pcb[exe].addr=ad;
pcb[exe].state='t';
printf("time slice interrupt\n");
printf("process %d enter into ready\n",exe);
exe=NIL;
return true;
}
}

void block(int se){//������������

int w;
printf("process %d is blocked\n",exe);
pcb[exe].state='w';//״̬��Ϊ�ȴ�״̬
pcb[exe].next=NIL;//�ѵȴ��ý����ͷ��źŵĽ������
w=si[se].first;//��¼
if(w==NIL)
si[se].first=exe;
else{
while(pcb[w].next!=NIL)
w=pcb[w].next;
pcb[w].next=exe;
}
}

int p(int se,char ad){

si[se].value=si[se].value-1;//�ź�����1
if(si[se].value>=0 )   
return false;
else{
block(se);
pcb[exe].count=i;
pcb[exe].addr=ad; 
exe=NIL;    
return true;          
}
}

void receive(int receiver){//���̽����ź���

struct sem *p,*q;
p=pcb[receiver].s;
while(p!=NULL){
printf("receive message from process %d\n",p->pro);
printf("process %d already run %d times\n",p->pro,p->num);
q=p;
p=p->next;
free(q);
}
pcb[receiver].s=NULL;
}

void process3(int s1,int s2){

if(addr=='a')
goto a3;
if(addr=='b')
goto b3;
if(addr=='c')
goto c3;
while(i<5){
receive(3);
printf("p3 calls p on sem1\n");
if(p(2,'a'))
goto stop3;
a3:printf("p3 is exe on its c-s1\n");
if(timeint('b'))
goto stop3;
b3:s2=s2+1;
printf("s2=%d",s2);
printf("p3 calls v on sem1 quit c-s1\n");
if(v(2,'c'))
goto stop3;
c3:printf("p3 cyclen count=%d\n",i+1);
i=i+1;
send(3,1,i);
send(3,2,i);
stop3:if(i>=5)
eexit(3);
}
}

void process2(int s1,int s2){

if(addr=='a')
goto a2;
if(addr=='b')
goto b2;
if(addr=='c')
goto c2;
if(addr=='d')
goto d2;
if(addr=='e')
goto e2;
if(addr=='f')
goto f2;
while(i<5){
receive(2);
printf("p2 calls p on sem1\n");
if(p(1,'a'))
goto stop2;
a2:printf("p2 is exe on its c-s1\n");
if(timeint('b'))
goto stop2;
b2:s1=s1+1;
printf("s1=%d\n",s1);
printf("p2 calls v on sem1 quit c-s1\n");
if(v(1,'c'))
goto stop2;
c2:printf("p2 calls on sem2\n");
if(p(2,'d'))
goto stop2;
d2:printf("p2 is exe on its c-s2\n");
if(timeint('e'))
goto stop2;
e2:s2=s2+1;
printf("s2=%d\n",s2);
printf("p2 calls v on sem2 quit c-s2\n");
if(v(2,'f'))
goto stop2;
f2:printf("p2 cyclen count=%d\n",i+1);
i=i+1;
send(2,1,i);
send(2,3,i);
}
stop2:if(i>=5)
eexit(2);
}

//����1������
void process1(int s1,int s2){

if(addr=='a')
goto a1;
if(addr=='b')
goto b1;
if(addr=='c')
goto c1;
if(addr=='d')
goto d1;
if(addr=='e')
goto e1;
if(addr=='f')
goto f1;
while(i<5){
receive(1);//�鿴receive����
printf("p1 calls p on sem1\n");//p1���������ź���sem1
if(p(1,'a'))//�鿴p��������ַΪa
goto stop1;
a1:printf("p1 is exe on its c-s1\n");
if(timeint('b'))//��ַΪb 
goto stop1;
b1:s1=s1+1;
printf("s1=%d\n",s1);
printf("p1 calls v on sem1 quit c-s1\n");
if(v(1,'c'))//��ַΪc
goto stop1;
c1:printf("p1 calls on sem2\n");
if(p(2,'d'))//��ַΪd
goto stop1;
d1:printf("p1 is exe on its c-s2\n");
if(timeint('e'))//��ַΪe
goto stop1;
e1:s2=s2+1;
printf("s2=%d\n",s2);
printf("p1 calls v on sem2 quit c-s2\n");
if(v(2,'f'))//��ַΪf
goto stop1;
f1:printf("p1 cyclen count=%d\n",i+1);
i=i+1;
send(1,2,i);
send(1,3,i);
}
stop1:if(i>=5)
eexit(1);
}

//���ҽ��̺���
int find(){

int j,pd,w;
pd=NIL;
w=MAX;//����һ���������ȼ�Ϊ100

for(j=1;j<=3;j++)//����߾���̬�п�ʼѭ�����Σ��ҳ����ȼ���ߵĽ���
if(pcb[j].state='r')
if(pcb[j].prio<w){
w=pcb[j].prio;
pd=j;
}
//�������߾���̬��û�У�������;���̬��ʼѰ�����ȼ���ߵĽ���
if(pd==NIL)
for(j=1;j<=3;j++)
if(pcb[j].state=='t')
if(pcb[j].prio<w){
w=pcb[j].prio;
pd=j;
}
return pd;//�����ҳ��Ľ���ID
}

//���Ƚ���
int scheduler(){

int pd;//��¼����ID
pd=find();//�鿴find����
if((pd==NIL)&&(exe==NIL))
return NIL;
else{
if(pd!=NIL){//û������ִ�еĽ��̣�����ҵ��Ľ��̷���ִ��̬
if(exe==NIL){
pcb[pd].state='e';//�ѽ���״̬��Ϊe
exe=pd;//��¼��ǰ���еĽ���ID
printf("process %d is executing\n",exe);
}
else if(pcb[pd].prio<pcb[exe].prio){//������ȵĽ������ȼ�������ִ�е����ȼ��ߣ�����ռ������Դ���������С�
pcb[exe].state='r';//������ִ�еĽ��̷��뵽�߾���̬
printf("process %d enter into ready\n",exe);
pcb[pd].state='e';//�ѵ��ȵĽ��̷���ִ��̬
exe=pd;//��¼��ǰ���̵�ID
printf("process %d is executing\n",exe);
}
}
i=pcb[exe].count;//��¼��ǰ�������еĴ���
addr=pcb[exe].addr;//��¼��ǰ���̵ĵ�ַ
return exe;//���ؽ���ID
}
}

//��ʼ������
void init(){

int j;
for(j=1;j<=3;j++){//3��ѭ�����ֱ��3�����̽��г�ʼ��
pcb[j].id=j;//���̱�ʶ��
pcb[j].state='r';//��ʼ�����ڸ߾���̬
pcb[j].next=NIL;//�ȴ�ͬһ���ź�������һ�����̵�ID
pcb[j].s=NULL;//��Ϣ��ָ��
printf("process %d priority?  ",j);
scanf("%d",&pcb[j].prio);//���ȼ�
pcb[j].count=0;//���еĴ���
pcb[j].addr='0';//���صĵ�ַ
}

si[1].value=1;//�ź�������ʾ��Դ�Ƿ�ռ�ã�Ϊ1��û��ռ�ã�Ϊ0����ռ��
si[1].first=NIL;//�ȴ����ź�������һ������ID
si[2].value=1;
si[2].first=NIL;
exe=NIL;//��ǰ���еĽ��̵ı�ʶ��
}



//��������ڵ�ַ
int main(){

int k,s1,s2;//k������¼�����Ƚ��̵�ID��s1,s2���ٽ���Դ���õļ�����
printf("C.O.S example one\n");
init();//���̽ṹ���ʼ���������ṹ����ÿ��������ֵ
s1=0;
s2=0;
printf("s1=%d,s2=%d\n",s1,s2);
loop:k=scheduler();//��ʼ���Ƚ��̣�����ʼģ��������
if(k!=NIL)
switch(k){//����k��ֵ����ID�ţ������в�ͬ�Ľ���
case 1:process1(s1,s2);goto loop;//�鿴process_����
case 2:process2(s1,s2);goto loop;
case 3:process3(s1,s2);goto loop;
default:printf("process identifer error\n");
}
printf("s1=%d,s2=%d",s1,s2);
printf("completed\n");
}


