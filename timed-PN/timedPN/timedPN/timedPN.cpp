#include "OrthogonalList.h"
#include <iostream>
#include "tree_node.h"
#include "data_read.h"
#include "TransFireCondition.h"
#include "AddNewNode.h"
#include "Initialize.h"
#include "new_or_old.h"
#include "CreateNode.h"
#include"output.h"
#include "back_tree.h"
#include "tf_model_py.h"
#include "h_evaluate.h"
#include "Heuristic_methon.h"

#pragma warning(disable:4996)
CrossList SMatrix_C_pre, SMatrix_C_post;
CrossList SMatrix_C;



void timedPN_data()
{
	InitSMatrix(&SMatrix_C_pre);   // CrossList类型的变量在初次使用之前必须初始化 
	printf("创建前置关联矩阵SMatrix_C_pre: ");
	CreateSMatrix(&SMatrix_C_pre, "J:\\原--数据\\桌面\\timed-PN\\C_pref.txt");
	PrintSMatrix(SMatrix_C_pre);  // C_pre的十字链表

	printf("\n");


	InitSMatrix(&SMatrix_C_post);
	printf("创建后置关联矩阵SMatrix_C_post: ");
	CreateSMatrix(&SMatrix_C_post, "J:\\原--数据\\桌面\\timed-PN\\C_postf.txt");
	PrintSMatrix(SMatrix_C_post);    // C_post的十字链表

	printf("\n");


	SubtSMatrix(SMatrix_C_post, SMatrix_C_pre, &SMatrix_C);
	printf("关联矩阵SMatrix_C: ");
	PrintSMatrix(SMatrix_C);   // C的十字链表

	printf("\n");

	int place_num = SMatrix_C.mu; //库所数量
	int transition_num = SMatrix_C.nu; //变迁数量
	int j;
	int new_mark[MaxRow]; //当前标识
	int new_mark_x[MaxRow];//当前标识,库所中托肯已经等待时间
	int new_mark_g; // 当前标识下已耗费的时间 
	Tree ReachableTree; 
	int M0[MaxRow], Delay[MaxRow]; //初始标识， 赋时时间
	int Transition;
	int is_new;
	struct Node *q;

	data_read(place_num, M0, Delay);
	InitTree(&ReachableTree, place_num, transition_num);
	InitNode(&ReachableTree, M0);
	q = ReachableTree.head_Node;
	do
	{
		for (j = 0; j < place_num; j++)
		{
			new_mark[j] = q->new_m[j];//将新表中第i行的标识赋值给当前的标识
			new_mark_x[j] = q->new_m_x[j];
		}
		new_mark_g = q->new_m_g;
		ReachableTree.source_come = q;
		for (Transition = 0; Transition < transition_num; Transition++)
		{
			int Transition_fire = 0;
			Transition_fire = TransFireCondition(new_mark, Transition);
			if (Transition_fire)
			{
				CreateNode(&ReachableTree, Transition, Delay, new_mark, new_mark_x, new_mark_g);
				is_new = new_or_old(&ReachableTree);
				AddNewNode(&ReachableTree, is_new);
			}
		}


		q = q->next_open;
	} while (q != NULL);
	
	out_put(&ReachableTree);
	back_tree(&ReachableTree);
	out(&ReachableTree);
	data_process(&ReachableTree);



}




void Astar()
{
	InitSMatrix(&SMatrix_C_pre);   // CrossList类型的变量在初次使用之前必须初始化 
	printf("创建前置关联矩阵SMatrix_C_pre: ");
	CreateSMatrix(&SMatrix_C_pre, "J:\\原--数据\\桌面\\timed-PN\\C_pref.txt");
	PrintSMatrix(SMatrix_C_pre);  // C_pre的十字链表

	printf("\n");


	InitSMatrix(&SMatrix_C_post);
	printf("创建后置关联矩阵SMatrix_C_post: ");
	CreateSMatrix(&SMatrix_C_post, "J:\\原--数据\\桌面\\timed-PN\\C_postf.txt");
	PrintSMatrix(SMatrix_C_post);    // C_post的十字链表

	printf("\n");



	SubtSMatrix(SMatrix_C_post, SMatrix_C_pre, &SMatrix_C);
	printf("关联矩阵SMatrix_C: ");
	PrintSMatrix(SMatrix_C);   // C的十字链表

	printf("\n");

	int place_num = SMatrix_C.mu; //库所数量
	int transition_num = SMatrix_C.nu; //变迁数量
	int j;
	int new_mark[MaxRow]; //当前标识
	int new_mark_x[MaxRow];//当前标识,库所中托肯已经等待时间
	int new_mark_g; // 当前标识下已耗费的时间 
	AstarTree SearchTree;
	int M0[MaxRow], Delay[MaxRow]; //初始标识， 赋时时间
	int Transition;
	int h_is_min;
	struct AstarNode *q;
	data_read(place_num, M0, Delay);
	InitAstarTree(&SearchTree, place_num, transition_num);
	InitAstarNode(&SearchTree, M0);
	q = SearchTree.open_head;
	int flag = 0;
	do
	{
		for (j = 0; j < place_num; j++)
		{
			new_mark[j] = q->new_m[j];//将新表中第i行的标识赋值给当前的标识
			new_mark_x[j] = q->new_m_x[j];
		}
		new_mark_g = q->new_m_g;
		SearchTree.source_come = q;
		for (Transition = 0; Transition < transition_num; Transition++)
		{
			int Transition_fire = 0;
			Transition_fire = TransFireCondition(new_mark, Transition);
			if (Transition_fire)
			{
				flag = 1;
				CreateAstarNode(&SearchTree, Transition, Delay, new_mark, new_mark_x, new_mark_g);
			/*	is_new = new_or_old(&ReachableTree);
				AddNewNode(&ReachableTree, is_new);*/
			}
		}
		if (flag == 0)
		{
			break;
		}
		select_openNode(&SearchTree);
		q = q->open_next;
		flag = 0;
	} while (q != NULL);


	Astarout(&SearchTree);
	//out_put(&ReachableTree);
	//back_tree(&ReachableTree);
	//out(&ReachableTree);
	//data_process(&ReachableTree);



}







int main()
{
	//float a;
	//const char *path = "data_process/backout4.txt";
	//a = testAstar(path);
	//printf("%f", a);
	Astar();

}

