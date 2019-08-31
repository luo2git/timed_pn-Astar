
#include "Heuristic_methon.h"

void link_delete_num(AstarTree *Tr, AstarNode *Node_min)
{
	struct AstarNode *P, *D;
	P = (*Tr).close_head;
	D = NULL;
	if (P == NULL)//链表为空链表
	{
		printf("链表为空\n");
		return;
	}
	while (P->new_m_num != Node_min->new_m_num && P->close_next != NULL)//循环查找要删除的节点
	{
		D = P;
		P = P->close_next;
	}
	if (P->new_m_num == Node_min->new_m_num)//找到了一个节点的num和num相等
	{
		if (P == (*Tr).close_head) //找到的节点是头节点
		{
			(*Tr).close_head = P->close_next;
		}
		else if(P == (*Tr).close_end)//找到的节点是尾节点
		{
			D->close_next = P->close_next;
			(*Tr).close_end = D;
		}
		else
		{
			D->close_next = P->close_next;
		}
		(*Tr).former = (*Tr).latter = (*Tr).close_end;
		/*free(P);*/
	}
	else//没有找到咱们要删除的节点
	{
		printf("没有找到您要删除的节点\n");
	}
}







void select_openNode(AstarTree *Tr) //在close表中选择g+h最小的扩展结点
{
	float min_val, val;
	//int n = 0;
	//int n_min = -1;
	min_val = 10000;
	struct AstarNode *P, *Q;
	P = (*Tr).close_head;
	if (P == NULL)//链表为空链表
	{
		printf("链表为空\n");
		return;
	}
	Q  =  NULL;
	do
	{
		val = P->new_m_g + P->new_m_h;
		if (val < min_val)
		{
			Q = P;
			min_val = val;
			//n_min = n;
		}
		P = P->close_next;
		//n += 1;
	} while (P != NULL);

	(*Tr).open_end->open_next = Q;
	(*Tr).open_end = Q;
	link_delete_num(Tr, Q);
}