#ifndef _3DPOINTLIST_H_
#define _3DPOINTLIST_H_
#include <stdbool.h>

/* 类型定义 */
typedef struct {
	double X;
	double Y;
	double Z;
} _3DPoint;					/* 三维坐标点 */

typedef struct node {
	_3DPoint point;
	struct node* right;		/* 右端节点 */
	struct node* bottom;	/* 底端节点 */
} Node;

typedef Node* _3DPointList;

/* 函数原型 */

/* 函数操作：初始化一个链表							*/
/* 前提条件：plist指向一个链表						*/
/* 后置条件：plist初始化为空						*/
void InitList(_3DPointList* plist);

/* 函数操作：判断一个链表是否为空					*/
/* 前提条件：plist指向一个已初始化的链表				*/
/* 后置条件：plist为空，返回true；否则返回false		*/
bool ListIsEmpty(const _3DPointList* plist);

/* 函数操作：判断一个链表是否为满					*/
/* 前提条件：plist指向一个已初始化的链表				*/
/* 后置条件：plist为满，返回true；否则返回false		*/
bool ListIsFull(const _3DPointList* plist);

/* 函数操作：在链表右端的末尾插入点				*/
/* 前提条件：plist指向一个已初始化的链表				*/
/*		    point是一个待添加至链表的三维坐标点		*/
/* 后置条件：添加成功，返回true；否则返回false		*/
bool AddRightEndPoint(_3DPointList* plist, _3DPoint point);

/* 函数操作：在链表底端的末尾插入点				*/
/* 前提条件：plist指向一个已初始化的链表				*/
/*		    point是一个待添加至链表的三维坐标点		*/
/* 后置条件：添加成功，返回true；否则返回false		*/
bool AddBottomEndPoint(_3DPointList* plist, _3DPoint point);

/* 函数操作：在链表右端相邻节点中间插入点				*/
/* 前提条件：plist指向一个已初始化的链表				*/
/*		    point是一个待添加至链表的三维坐标点		*/
/* 后置条件：添加成功，返回true；否则返回false		*/
bool AddRightMidPoint(Node* node, _3DPoint point);

/* 函数操作：在链表底端相邻节点中间插入点				*/
/* 前提条件：plist指向一个已初始化的链表				*/
/*		    point是一个待添加至链表的三维坐标点		*/
/* 后置条件：添加成功，返回true；否则返回false		*/
bool AddBottomMidPoint(Node* node, _3DPoint point);

/* 函数操作：清空链表，并释放已分配的内存				*/
/* 前提条件：plist指向一个已初始化的链表				*/
/* 后置条件：释放了为链表分配的所有内存，链表设置为空	*/
void EmptyTheList(_3DPointList* plist);

#endif
