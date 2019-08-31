#include <stdlib.h> 
#include<stdio.h>
#include "tree_node.h"
#include "back_tree.h"

void back_output(Node *node, Tree *Tr)
{
	printf("m%2d的标识是", node->new_m_num);
	for (int i = 0; i < (*Tr).place_num; i++)
	{
		printf("%2d", node->new_m[i]);
	}
	printf("%s", " 已等待时间x是");
	for (int i = 0; i < (*Tr).place_num; i++)
	{
		printf("%2d", node->new_m_x[i]);
	}
	printf("%s", " 已耗费时间g为");
	printf("%2d", node->new_m_g);
	printf("%s", " 估计耗费时间h为");
	printf("%2d", node->new_m_h);
	printf("%s", " 估计最小耗费时间h为");
	printf("%2d", node->new_m_h_min);
	printf("%s", " 标识来源于M");
	printf("%2d", node->new_m_come);
	printf("%s", " 激发的变迁");
	printf("%2d", node->new_m_transition);
	if (node->finish == 0)
	{
		printf("%s", " 它不是终止标识 NO");
	}
	else
	{
		printf("%s", " 它是终止标识 YES");
	}
	if (node->old == 0)
	{
		printf("%s", " 它不是重复标识");
	}
	else
	{
		printf("%s", " 它的重复标识是");
		printf("%2d", node->old_mark);
	}
	printf("\n");
}


void node_back_open(Node *node, Tree *Tr, int time_cost)
{
	if (node !=NULL)
	{ 
		node->new_m_h = time_cost - node->new_m_g;
		if (node->new_m_h < node->new_m_h_min)
		{
			node->new_m_h_min = node->new_m_h;
		}
		//back_output(node, Tr);
		node_back_open(node->source, Tr, time_cost);
		struct Node *same_node, *source_node;
		same_node = node->same;
		while (same_node != NULL)
		{
			source_node = same_node->source;
			node_back_open(source_node,Tr,time_cost);
			same_node = same_node->same;
		}
	}
}


void back_tree(Tree *Tr)
{
	struct Node *finish_node;
	//struct Node *head_backtree;
	finish_node = Tr->finish_head_Node;
	int num = 1;
	while (finish_node != NULL)
	{
		printf("\n");
		printf("第%2d棵反向树输出", num);
		printf("\n");
		node_back_open(finish_node, Tr, finish_node->new_m_g);
		printf("第%2d棵反向树输出结束", num);
		printf("\n");
		num = num + 1;
		finish_node = finish_node->finish_node;
	}
}