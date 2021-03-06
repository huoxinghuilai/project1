#include<linux/module.h>
#include<linux/init.h>
#include<linux/workqueue.h>

static struct workqueue_struct *queue=NULL;
static struct work_struct work;

static void work_handler(struct work_struct *data){
printk(KERN_ALERT "work handler functiion\n");
}

static int __init test_init(void){
queue=create_singlethread_workqueue("helloworld");/*创建一个单线程的工作队列*/
if(!queue)
goto err;
INIT_WORK(&work,work_handler);
schedule_work(&work);
return 0;
err:
return -1;
}

static void __exit test_exit(void){
destory_workqueue(queue);
}

MODULE_LICENSE("GPL");
module_init(test_init);
module_exit(test_exit);

