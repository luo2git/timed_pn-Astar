#pragma once
#define MaxRow  200        //矩阵最多行列数

typedef int ElemType;
typedef struct OLNode
{
	int i, j;    // 该非零元的行和列下标 
	ElemType e;    // 非零元素值 
	struct OLNode *right, *down; // 该非零元所在行表和列表的后继链域 
}OLNode, *OLink;


typedef struct// 行和列链表头指针向量基址,由CreatSMatrix_OL()分配
{
	OLink *rhead, *chead;
	int mu, nu, tu;        // 稀疏矩阵的行数、列数和非零元个数 
}CrossList;


int InitSMatrix(CrossList *M);    // 初始化M(CrossList类型的变量必须初始化,否则创建、复制矩阵将出错) 
int DestroySMatrix(CrossList *M);    // 销毁稀疏矩阵M
void CreateSMatrix(CrossList *M, const char *path);     // 采用十字链表存储表示
int PrintSMatrix(CrossList M);  // 按行或按列输出稀疏矩阵M
int SubtSMatrix(CrossList M, CrossList N, CrossList *Q); //  求稀疏矩阵的差Q=M-N 
