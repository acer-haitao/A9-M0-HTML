#include "sqlite_link_list.h"
#include "data_global.h"

extern slinklist slinkHead, slinkTail;

slinklist sqlite_CreateEmptyLinklist ()
{
	printf("--------------创建链表--------------\n");
	slinklist h;
	h = (slinklist)malloc (sizeof (slinknode));
	printf ("%d\n", sizeof (slinknode));
	slinkTail = h;
	h->next = NULL;
	return h;
}

int sqlite_EmptyLinklist (slinklist h)
{
	printf("--------------判断链表是否为空--------------\n");
	return NULL == h->next;
}

slinklist sqlite_GetLinknode (slinklist h)
{
	printf("--------------获取链表节点--------------\n");
	if (1 == sqlite_EmptyLinklist (h))	
	{
		return NULL;
	}
	slinklist p = h->next;
	h->next = p->next;
	if (p->next == NULL)
		slinkTail = h;
	return p;
}

int sqlite_InsertLinknode (int operation, struct env_info_clien_addr y, 
						   int storageNum_l, int goodsKinds_l)
{
	printf("--------------插入链表--------------\n");
	struct sqlite_operation sqlite_operation_t;
	switch(operation & 0xff)
	{
	case 0x00:
		sqlite_operation_t.table_select_mask = 0;
		sqlite_operation_t.env_operation_mask = 0;
		break;
	case 0x01:
		sqlite_operation_t.table_select_mask = 0;
		sqlite_operation_t.env_operation_mask = 1;
		break;
	case 0x10:
		sqlite_operation_t.table_select_mask = 1;
		sqlite_operation_t.table_operation_mask = 0;
		break;
	case 0x11:
		sqlite_operation_t.table_select_mask = 1;
		sqlite_operation_t.table_operation_mask = 1;
		break;
	case 0x12:
		sqlite_operation_t.table_select_mask = 1;
		sqlite_operation_t.table_operation_mask = 2;
		break;
	case 0x20:
		sqlite_operation_t.table_select_mask = 2;
		sqlite_operation_t.goods_operation_mask = 0;
		break;
	case 0x21:
		sqlite_operation_t.table_select_mask = 2;
		sqlite_operation_t.goods_operation_mask = 1;
		break;
	case 0x22:
		sqlite_operation_t.table_select_mask = 2;
		sqlite_operation_t.goods_operation_mask = 2;
		break;
	case 0x23:
		sqlite_operation_t.table_select_mask = 2;
		sqlite_operation_t.goods_operation_mask = 3;
		break;
	}

	slinklist q = (slinklist)malloc (sizeof (slinknode));
	if (NULL == q)
	{
		printf ("InsertLinknode Error\n");
		return -1;
	}
	slinkTail->next = q;
	slinkTail = q;
	q->data = sqlite_operation_t;
	q->data_link = y;
	q->storageNum = storageNum_l;
	q->goodsKinds = goodsKinds_l;
	q->next = NULL;
	return 0;
}


