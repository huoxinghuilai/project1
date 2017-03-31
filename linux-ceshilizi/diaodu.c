#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

struct task{ //���̽ṹ��
	int id; //���
	int pro; //���ȼ�
	int time; //����ʱ��`
	int flag; //��־λ
	struct task *next; //��̽ڵ�
	struct task *prev; //ǰ���ڵ�
};

struct task *rq[6]; //�������У���Ϊ6
struct task *wq[6]; //��������
struct task *head; //�Ĵ����

struct task *mkrq(){ //��ʼ����������
	int i=0;
	
	for(i;i<6;i++){ 
		rq[i]=(struct task *)malloc(sizeof(struct task));
		rq[i]->next=rq[i];
		rq[i]->prev=rq[i];
	}
}

struct  task *mkwq(){ //��ʼ����������
	int i=0;
	
	for(i;i<6;i++){ 
		wq[i]=(struct task *)malloc(sizeof(struct task));
		wq[i]->next=wq[i];
		wq[i]->prev=wq[i];
	}
}

int pt(struct task *p){ //���ȼ�Խ�ߣ�ʱ��ƬԽ��
	p->pro=rand()%5; //�ؼ���Ϊ5����Ϊ��<=6��������������������ֵ��Ϊ���ȼ�
	p->time=10-p->pro;
}

struct task *init(int i){
	int j=0;
	
	struct task *p; //�γ�һ��˫ѭ������
	head=(struct task *)malloc(sizeof(struct task));
	head->next=head;
	head->prev=head;
	for(j;j<i;j++){
		p=(struct task *)malloc(sizeof(struct task));
		p->id=j;
		pt(p);
		p->flag=0; //������н��̿�ʼ��Ϊ����̬
		head->prev->next=p;
		p->prev=head->prev;
		head->prev=p;
		p->next=head;
	}	
}

struct task *add(struct task *t[],struct task *p){ //���뵽������
	t[p->pro]->prev->next=p; 
	p->prev=t[p->pro]->prev;
	p->next=t[p->pro];
	t[p->pro]->prev=p;
}

struct task *del(struct task *t[],struct task *p){ //�Ӷ�����ɾ��
	t[p->pro]->next=p->next; 
	p->next->prev=t[p->pro];
	p->next=p;
	p->prev=p;
	return p;
}

int cwr(){ //�������Ƿ�������̬���뵽����̬������ת��
	int i;
	struct task *p;
	for(i=0;i<6;i++){ //����Լ���֪������̬�Ļָ���ôģ������������õ��ǰ����ȼ�������˳����ִ�е�
		if(wq[i]->next!=wq[i]){
			p=del(wq,wq[i]->next);
			p->flag=0;
			add(rq,p);
			break;
		}
	}
	return 0;
}

int crw(struct task *p){
	p->flag=1;
	add(wq,p);
	return 0;
}

int pp(){ //��ӡ���������˳��
	struct task *p;
	p=head->next;
	while(p!=head){
		printf("%d %d %d %d\n",p->id,p->pro,p->time,p->flag);
		head->next=p->next;
		p->next->prev=head;
		if(p->flag==0)
			add(rq,p);			
		else
			add(wq,p);
		p=head->next;
	}
}

int cq(struct task *t[]){ //���������Ƿ��н���
	int i=0;
	int j=0;
	for(i;i<6;i++){
		if(t[i]->next==t[i])
			j++;
	}
	if(j==6)
		return 0;
	else
		return 1;
}

int prq(){ //��ӡ���������еĽ���
	int i=0;
	struct task *p;
	for(i;i<6;i++){
		p=rq[i]->next;
		while(p!=rq[i]){
		printf("%d %d %d %d\n",p->id,p->pro,p->time,p->flag);
		p=p->next;
		}
	}
	if(cq(rq)==0)
		printf("���������޽���\n");
}

int pwq(){ //��ӡ���������еĽ���
	int i=0;
	struct task *p;
	for(i;i<6;i++){
		p=wq[i]->next;
		while(p!=wq[i]){
			printf("%d %d %d %d\n",p->id,p->pro,p->time,p->flag);
			p=p->next;
		}	
	}
	if(cq(wq)==0)
		printf("���������޽���\n");
}

int run(){ //��������
	int i;
	struct task *p;
	int t;
	t=rand()%5;
	
	while(cq(rq)==0 && cq(wq)==1) //����Լ�û�����ô���
		cwr();
	if(t<3)
		cwr();

    for(i=0;i<6;i++){ //�Ӿ���������ȡ��Ҫ���еĽ���
		if(rq[i]->next!=rq[i]){
			p=del(rq,rq[i]->next);
			p->flag=2;
			break;
		}
	}
	while(--(p->time)){
		printf("�������еĽ���Ϊ:\n");
		printf("%d %d %d %d\n",p->id,p->pro,p->time,p->flag);
		Sleep(1);
		t=rand()%5;
		if(t>=3){
			crw(p);
		    break;
		}
		Sleep(1);	
	}
	if(t<3){
		printf("�ý����������\n");
		free(p);
		return 0;
	}
    return 0;
}


int main(){

	//��ʼ����ص�����
	mkrq();
	mkwq();
	init(5);

	printf("��ʼ����:\n");
	pp();
	printf("��������:\n");
	prq();
	printf("��������:\n");
	pwq();
	
	//���̿�ʼ����
	while(1){
		run();
		printf("��������:\n");
		prq();
		printf("��������:\n");
		pwq();
		if((cq(rq) || cq(wq))==0)
			break;
	}
}
