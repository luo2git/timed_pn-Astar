#include <stdlib.h> 
#include<stdio.h>
#include "tree_node.h"
#include "AddNewNode.h"

/*
* Comments: 判断是否为终止扩展结点
* Param Tree *Tr :  树
* @Return void
*/
void finish_node(Tree *Tr)
{
	int have_transition_fire = 0;
	int Transition, can_fire;
	for (Transition = 0; Transition < (*Tr).transition_num; Transition++)
	{
		can_fire = TransFireCondition((*Tr).former->new_m, Transition);
		if (can_fire == 1)
		{
			have_transition_fire = 1;
		}
	}
	if (have_transition_fire == 0)
	{
		(*Tr).former->finish = 1;
		(*Tr).former->finish_node = NULL;
		if ((*Tr).finish_head_Node == NULL)
		{
			(*Tr).finish_head_Node = (*Tr).former;
			(*Tr).finish_node_end = (*Tr).former;
		}
		else
		{
			(*Tr).finish_node_end->finish_node = (*Tr).former;
			(*Tr).finish_node_end = (*Tr).former;
		}

	}
	else
	{
		(*Tr).former->finish = 0;
		(*Tr).former->finish_node = NULL;
	}
}

/*
* Comments: 将新结点连接到open链的末尾
* Param Tree *Tr :  树
* Param int is_new :  树的当前结点为新
* @Return void
*/
void AddNewNode(Tree *Tr,int is_new)
{
	int f = 0;
	if (is_new == 1)//是新标识，则需要将扩展下一个新节点 
	{
		(*Tr).former->old = 0;
		(*Tr).former->old_mark = 0;
		finish_node(Tr);
		(*Tr).open_end->next_open = (*Tr).former;
		(*Tr).open_end = (*Tr).former;
		(*Tr).former->same = NULL;
		(*Tr).former->same_end = NULL;
	}
}
