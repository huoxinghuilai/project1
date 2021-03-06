#include<linux/init.h>
#include<linux/module.h>
#include<linux/semaphore.h>
#include<linux/sched.h>
#include<asm/atomic.h>
#include<linux/delay.h>

#define PRODUCT_NUMS 10 //定义生产数为10

static struct semaphore sem_producer; //定义生产信号
static struct semaphore sem_consumer; //定义消费信号
static char product[12]; //定义一个字符数组
static atomic_t num; //定义一个原子操作数
static int producer(void *product); //定义一个生产内核线程
static int consumer(void *product); //定义一个消费内核线程
static int id=1;
static int consume_num=1;

static int producer(void *p){
char *product=(char *)p;
int i;
atomic_inc(&num);
printk("producer[%d] start...\n",current->pid);
for(i=0;i<PRODUCT_NUMS;i++){
down(&sem_producer);
snprintf(product,12,"2010-01-%d",id++);
printk("producer[%d] product %s\n",current->pid,product);
up(&sem_consumer);
}
printk("producer[%d] exit...\n",current->pid);
return 0;
}

static int consumer(void *p){
char *product=(char *)p;
printk("consumer[%d] start...\n",current->pid);
for(;;){
msleep(100);
down_interruptible(&sem_consumer);
if(consume_num>=PRODUCT_NUMS * atomic_read(&num))
break;
printk("consumer[%d] consume %s\n",current->pid,product);
consume_num++;
memset(product,'\0',12);
up(&sem_producer);
}
printk("consumer[%d] exit...\n",current->pid);
return 0;
}

static int __init procon_init(void){
printk(KERN_INFO "show producer and consumer\n");
sema_init(&sem_producer,1);
sema_init(&sem_consumer,0);
atomic_set(&num,0);
kernel_thread(producer,product,CLONE_KERNEL);
kernel_thread(consumer,product,CLONE_KERNEL);
return 0;
}

static int __exit procon_exit(void){
printk(KERN_INFO "exit producer and consumer\n");
return 0;
}

module_init(procon_init);
module_exit(procon_exit);
MODULE_LICENSE("GPL");

