#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/slab.h>
#include<linux/list.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("XIYOU");

#defien N 10
struct numlist{
int num;
struct list_head list; //结构体变量，不是指针型变量
};
struct numlist numhead;

static int __init doublelist_init(void){
struct numlist *listnode;
struct list_head *pos;
struct numlist *p;
int i;
for(i=0;i<N;i++){
listnode=(struct numlist *)kmalloc(sizeof(struct numlist),GFP_KERNEL);
listnode->num=i+1;
list_add_tail(&listnode->list,&numhead.list); //参数为指针型变量
printk("Node %d has added to the doublelist...\n",i+1);
}
list_for_each(pos,&numhead.list){
p=list_entry(pos,struct numlist,list);
printk("Node %d's data:%d\n",i,p->num);
i++;
}
return 0;
}

static void __exit doublelist_exit(void){
struct list_head *pos,*n;
struct numlist *p;
int i;
i=1;
list_for_each_safe(pos,n,&numhead.list){
list_del(pos);
p=list_entry(pos,struct numlist,list);
kfree(p);
fprintk("Node %d has removed from the doublelist...\n",i++);
}
printk("doublelist is exiting..\n");
}

module_init(doublelist_init);
module_exit(doublelist_exit);

