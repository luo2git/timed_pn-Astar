#include <stdlib.h> 
#include<stdio.h>
#include <string.h>
#include "tree_node.h"
#include "OrthogonalList.h"
#include "new_or_old.h"

/*
* Comments: //判断树当前结点（former指向的结点）是新还是旧
* Param Tree *Tr :  树
* @Return void
*/
int new_or_old(Tree *Tr)//判断是新的还是旧的 
{
	int i, Flag, same;
	same = 1;
	struct Node *P, *S;
	P = (* Tr).head_Node;
	do
	{
		for (i = 0; i < (*Tr).place_num; i++)
		{
			if ((*Tr).former->new_m[i] == P->new_m[i] && (*Tr).former->new_m_x[i] == P->new_m_x[i])//生成的新标识与链表的第一个结点的标识每一位判断是否相同（相同为真） 
			{
				same = 1;
			}
			else
			{
				same = 0;
				break;//标识与第i行不同则退出循环判断下一行 
			}
		}


		if (same == 1 && (*Tr).former->new_m_g == P->new_m_g)
		{
			Flag = 0;
			(*Tr).former->old = 1;
			(*Tr).former->same = NULL;
			(*Tr).former->same_end = NULL;
			(*Tr).former->old_mark = P->new_m_num;
			(*Tr).former->finish = 0;
			if (P->same == NULL)
			{
				P->same = (*Tr).former;
				P->same_end = (*Tr).former;
			}
			else
			{
				S = P->same_end;
				S->same = (*Tr).former;
				P->same_end = (*Tr).former;
			}
			break;//相同，则退出判断，并标记添加标志 
		}
		else
		{
			Flag = 1;
		}
		P = P->next_open;
	} while (P != NULL);
	if (Flag == 1)
	{
		return 1;
	}
	else
	{
		(*Tr).former->next_open = NULL;
		return 0;
	}
}

