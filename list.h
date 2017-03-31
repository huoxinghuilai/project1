#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H

//�ṹ��
struct list_head {
	struct list_head *next, *prev;
};

//��ʼ��ͷ���
 void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

//��ӽ��
 void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

//β�巨
 void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

//ɾ�����
 void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

//ɾ�����
 void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

//��������׵�ַ
#ifndef container_of
#define container_of(ptr, type, member) \
    (type *)((char *)(ptr) - (char *) &((type *)0)->member)
#endif

//�����׵�ַ
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#endif