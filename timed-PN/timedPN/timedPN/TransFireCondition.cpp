#include "OrthogonalList.h"
#include "TransFireCondition.h"

/*
* Comments: 判断在标识m下，变迁t是否可以激发
* Param CrossList SMatrix_C_pre :  前置关联矩阵
* Param int new_m[] :  标识
* Param  int Transition : 变迁
* @Return int  0表示在标识new_m下变迁Transition不能激发，1则反之
*/
int TransFireCondition( int new_m[], int Transition)
{
	int flag = 1;
	int a;
	OLink p;
	//	for(j=0;j<SMatrix_C_pre.nu;j++)
	p = SMatrix_C_pre.chead[Transition];
	while (p)
	{
		a = p->e;
		if (new_m[p->i] > a || new_m[p->i] == a)
		{
			p = p->down;
		}
		else
		{
			flag = 0;
			break;
		}
	}

	if (flag == 0)
	{

		return 0;
	}
	else
	{
		return 1;
	}
}