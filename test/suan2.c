#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char s[100],*p;
    float a[2], x,y,z,d;

	gets(s);
    
	p=s;
    
	while(1)
	{
	a[0]=(*p)%48*10+*(p+1)%48;  //ʱ��
	if(a[0]>12)                 //ʱ��ȡ0~12
		a[0]=a[0]-12;
	a[1]=*(p+3)%48*10+*(p+4)%48;//����
	
	x=a[1]/60*30;               //ʱ��С����ƫ�ƽǶ�
	y=a[1]/60*360;              //����ƫ�ƽǶ�
	z=a[0]/12*360;              //ʱ��ƫ�ƽǶ�
	if(z>=y)                    //���뿿��
		d=z-y+x;
	else                        //���뿿ǰ
		d=y-z-x;
	if(d>180)
		d=360-d;
	printf("%f\n",d);

    if(*(p+5)=='\n')
		break;
	
	p=p+6;
	}


struct time{
	char s[50];
	struct time *next;
};
int i=3;
struct time *head,*p;
head=(struct time *)malloc(sizeof(struct time));
p=head->next;
p=(struct time *)malloc(sizeof(struct time));
while(i--)
{
	scanf("%s",p->s);
	if(strlen(p->s)==0)
		break;
	p=p->next;
	p=(struct time *)malloc(sizeof(struct time));						
	
}
p=head->next;
while(p!=NULL)
{
	printf("%s\n",p->s);
	p=p->next;
}

  float length,area;
    scanf("%f",&length);
    area=length*length;
    printf("%f\n",area);

  
}
