//����ϵͳ���ú���
int sys_exit();
int sys_fork();

//����ϵͳ���ñ�
struct syscall_table{
int (*func)(void);
};
struct syscall_table sys[2];

//ʵ��exit����
int sys_exit(){
printf("ϵͳ����exit\n");
return 0;
}

//ʵ��fork����
int sys_fork(){
printf("ϵͳ����fork\n");
return 1;
}

//�������жϣ�����ģ��int &80
int softintr(int ax){
if(ax>=0 && ax<2){
ax=sys[ax].func();����
return ax;
}
else
return -1;
}

//����ϵͳ���ú�
#define nr_exit 0
#define nr_fork 1

//�������ax������ģ��ͨ�üĴ���ax
int ax=0;

//�궨��ϵͳ���ýӿں���
#define systemcall(type,name,nr_name) \
type name(){ \ 
ax=nr_name; \
ax=softintr(ax); \
return ax; \
}