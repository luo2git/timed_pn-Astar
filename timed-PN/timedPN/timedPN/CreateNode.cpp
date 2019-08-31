#include<stdio.h>
#include <stdlib.h>
#include "tree_node.h"
#include "OrthogonalList.h"
#include "CreateNode.h"
#include "h_evaluate.h"
/*
* Comments: 在（new_m,new_m_x,new_m_g）下，变迁Transition激发，生成新的结点
* Param Tree *Tr :  树
* Param int Transition :  激发变迁
* Param  int Delay[] : 赋时时间
* Param  int new_m[] : 标识
* Param  int new_m_x[] : 已等待时间
* Param  int new_m_g : 已耗费的时间代价
* @Return void
*/
void CreateNode(Tree *Tr, int Transition, int Delay[], int new_m[], int new_m_x[], int new_m_g)
{
	int T_num, i;
	int m[MaxRow];
	int x[MaxRow];
	int ans, step, g;  //step表示当前标识到下一标识的损耗时间 
	step = 0;
	OLink P, Q;
	P = SMatrix_C.chead[Transition];
	Q = SMatrix_C_pre.chead[Transition];
	for (i = 0; i < (*Tr).place_num; i++)
	{
		m[i] = new_m[i];
		x[i] = new_m_x[i];
	}

	while (P != NULL)//更新m 
	{
		m[P->i] = m[P->i] + (P->e);
		P = P->down;
	}

	while (Q != NULL) //更新step 
	{
		ans = Delay[Q->i] * (Q->e) - x[Q->i];
		if (ans > step)
			step = ans;
		Q = Q->down;
	}
	//printf("%2d", step);
	g = new_m_g + step;
	for (i = 0; i < (*Tr).place_num; i++) //更新结点处的x 
	{
		if (Delay[i] == 0)
		{
			x[i] = 0;
		}
		else
		{
			if (m[i] == 0)
			{
				x[i] = 0;
			}
			else
			{
				if (new_m[i] == 0)
				{
					x[i] = 0;
				}
				else
				{
					x[i] = x[i] + step;
				}
			}
		}
	}
	T_num = Transition + 1;
	(*Tr).Node_num++;//链表的节点数加一 
	(*Tr).former = (Nodelink)malloc(Len_node);//建立新的结点，其地址赋给former 
	(*Tr).latter->next = (*Tr).former;//将上一个结点的next指向新建的结点 
	(*Tr).latter = (*Tr).former;//使latter也指向新建的结点 
	for (i = 0; i < (*Tr).place_num; i++)//给新建的结点赋值 
	{
		(*Tr).former->new_m[i] = m[i]; //产生的新标识放到输出表中 
		(*Tr).former->new_m_x[i] = x[i];
	}
	(*Tr).former->new_m_g = g;
	(*Tr).former->new_m_h_min = -1;
	(*Tr).former->new_m_come = ((*Tr).source_come)->new_m_num;//标识的来源下标放到输出表中 
	(*Tr).former->source = (*Tr).source_come;
	(*Tr).former->new_m_transition = T_num;//标识激发的变迁的下标放到输出表中 
	(*Tr).former->new_m_num = (*Tr).Node_num;
	(*Tr).former->next = NULL;
	(*Tr).former->next_open = NULL;
}

void CreateAstarNode(AstarTree *Tr, int Transition, int Delay[], int new_m[], int new_m_x[], int new_m_g)
{
	int T_num, i;
	int m[MaxRow];
	int x[MaxRow];
	int ans, step, g;  //step表示当前标识到下一标识的损耗时间 
	step = 0;
	OLink P, Q;
	P = SMatrix_C.chead[Transition];
	Q = SMatrix_C_pre.chead[Transition];
	for (i = 0; i < (*Tr).place_num; i++)
	{
		m[i] = new_m[i];
		x[i] = new_m_x[i];
	}

	while (P != NULL)//更新m 
	{
		m[P->i] = m[P->i] + (P->e);
		P = P->down;
	}

	while (Q != NULL) //更新step 
	{
		ans = Delay[Q->i] * (Q->e) - x[Q->i];
		if (ans > step)
			step = ans;
		Q = Q->down;
	}
	//printf("%2d", step);
	g = new_m_g + step;
	for (i = 0; i < (*Tr).place_num; i++) //更新结点处的x 
	{
		if (Delay[i] == 0)
		{
			x[i] = 0;
		}
		else
		{
			if (m[i] == 0)
			{
				x[i] = 0;
			}
			else
			{
				if (new_m[i] == 0)
				{
					x[i] = 0;
				}
				else
				{
					x[i] = x[i] + step;
				}
			}
		}
	}
	T_num = Transition + 1;
	(*Tr).Node_num++;//链表的节点数加一 
	(*Tr).former = (AstarNodelink)malloc(Len_Astarnode);//建立新的结点，其地址赋给former 
	if ((*Tr).close_head == NULL)
	{
		(*Tr).close_head = (*Tr).close_end = (*Tr).latter = (*Tr).former;
	}
	else
	{
		(*Tr).latter->close_next = (*Tr).former;//将上一个结点的next指向新建的结点 
		(*Tr).close_end = (*Tr).latter = (*Tr).former;//使latter也指向新建的结点 
	}
	for (i = 0; i < (*Tr).place_num; i++)//给新建的结点赋值 
	{
		(*Tr).former->new_m[i] = m[i]; //产生的新标识放到输出表中 
		(*Tr).former->new_m_x[i] = x[i];
	}
	(*Tr).former->new_m_g = g;
	(*Tr).former->new_m_h = h_eval(Tr);
	(*Tr).former->new_m_come = ((*Tr).source_come)->new_m_num;//标识的来源下标放到输出表中 
	(*Tr).former->source = (*Tr).source_come;
	(*Tr).former->new_m_transition = T_num;//标识激发的变迁的下标放到输出表中 
	(*Tr).former->new_m_num = (*Tr).Node_num;
	(*Tr).former->open_next = NULL;
	(*Tr).former->close_next = NULL;
}