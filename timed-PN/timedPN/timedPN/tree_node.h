#pragma once
#ifdef MaxRow
#else
#define MaxRow 200
#endif // MaxRow
#define Len_node         sizeof(struct Node)
#define Len_Astarnode         sizeof(struct AstarNode)



////////// 完全搜索，生成模型所需数据
typedef struct Node
{
	int new_m_num;//新标识的下标
	int new_m[MaxRow]; //新标识的具体标识
	int new_m_x[MaxRow]; // 此时刻库所中托肯已经等待时间
	int new_m_g; //已耗费的时间代价
	int new_m_h; //估计值
	int new_m_h_min; // 估计值最小值
	int new_m_come;//新标识的标识来源
	struct Node *source; //新标识的来源节点 
	int new_m_transition;//新标识的变迁来源
	struct Node *next_open;//下一个要扩展的标识
	struct Node *next; //下一个结点地址
	int old; //旧的标识
	struct Node *same; //首次相同的标识 
	struct Node *same_end; //末尾相同的标识 
	int old_mark;//旧的标识的下标
	int finish;  //终止扩展结点 
	struct Node *finish_node; // 首次连接终止结点
	//struct Node *bcak_tree; //对每棵反向树的结点进行连接，避免结点多次搜索，加快计算速度
	//struct Node *finish_node_end; // 末尾连接终止结点
} *Nodelink;



typedef struct
{
	Node *head_Node; //指向树的第一个结点
	Node *former;  //当前结点
	Node *latter;  //当前结点的上一个结点
	Node *finish_head_Node; //树的终止结点
	Node *finish_node_end; // 末尾连接终止结点
	Node *open_end;  //扩展的尾结点
	Node *source_come; //结点的来源结点
	int  place_num;  //库所数量
	int  transition_num; //变迁数量
	int  Node_num; // 树的结点个数
}Tree;



/////////A*算法局部搜索，其中启发式函数h由训练模型所得
typedef struct AstarNode
{
	int new_m_num;//新标识的下标
	int new_m[MaxRow]; //新标识的具体标识
	int new_m_x[MaxRow]; // 此时刻库所中托肯已经等待时间
	int new_m_g; //已耗费的时间代价
	float new_m_h; //估计值
	int new_m_come;//新标识的标识来源
	struct AstarNode *source; //新标识的来源节点 
	int new_m_transition;//新标识的变迁来源
	struct AstarNode *open_next;// 连接open表
	struct AstarNode *close_next; //  连接close表
} *AstarNodelink;



typedef struct
{
	AstarNode *open_head; //指向open表的第一个结点
	AstarNode *close_head;  //指向close表的第一个结点
	AstarNode *former;  //当前结点close
	AstarNode *latter;  //当前结点的上一个结点close
	AstarNode *open_end;  //open表的尾结点
	AstarNode *close_end;  //close表的尾节点
	AstarNode *source_come; //结点的来源结点
	int  place_num;  //库所数量
	int  transition_num; //变迁数量
	int  Node_num; // 树的结点个数
}AstarTree;
