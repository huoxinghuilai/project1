#include<stdio.h>
#include<stdlib.h>

#define m 13

struct link{
	int num;
	struct link *next;
};
struct link *b[m];

//��ʼ����ϣ��
struct link *init()
{
	int i=0;
	for(i;i<m;i++)
	{
		b[i]=(struct link *)malloc(sizeof(struct link));
		b[i]->next=NULL;
	}
	return b[0];
}

//��ȡ��������
int sushu()
{
	int i=0;
	int j=m;
	while(j)
	{
		for(i=2;i<j;i++)
		{
			if(!(j%i))
				break;
		}
		if(i==j)
			break;
		j--;
	}
    return j;	
}

//������ϣ���ǵ�ַ�������ʽ
struct link *create(int *a)
{
	int i=0;
	int j=m;
	int k=0;
	int d=0;
	struct link *p;
	k=sushu();
	for(i;i<m-1;i++)
	{
		d=a[i]%k;
		
		//��ȡ�ռ�
		p=(struct link *)malloc(sizeof(struct link));
		p->num=a[i];

		//��ͷ��ķ�ʽ����
		p->next=b[d]->next;
		b[d]->next=p;
	}
	return b[0];
}

//��ʾ�����ַ�Ĵ洢
struct link *show()
{
	int i=0;
	struct link *p;
	for(i;i<m;i++)
	{
		printf("b[%d]",i); 
		p=b[i]->next;
		while(p!=NULL)
		{
			printf(" -> %d",p->num);
			p=p->next;
		}
		printf("\n");
	}
}	

//Ѱ������λ��
int search(int i)
{
	int d;
	int j=1;
	struct link *p; 
	
	//�����ֵ���ڵ���
	d=i%m;
	p=b[d]->next;
	
	//�����ֵ���ڵ���
	while(p!=NULL)
	{
		if(p->num==i)
		{
			printf("λ�ã�(%d,%d)\n",d,j);
			return;
		}
		p=p->next;
		j++;
	}
	printf("no this num!\n");
	return;
}

int main()
{
	int i=0;
	int a[m-1];
	int t;
	for(i=0;i<m-1;i++)
	{
		scanf("%d",&a[i]);
	}
    
	init();
	create(a);
	show();

	scanf("%d",&t);
	search(t);

}

