#ifndef _MOUNTAIN3D_H_
#define _MOUNTAIN3D_H_
#include "_3DPointList.h"

/* 函数原型 */

/* 函数操作：遍历链表并打印（测试用）				*/
/* 前提条件：plist指向一个已初始化的链表				*/
/* 后置条件：打印链表中三维坐标点的信息				*/
void PrintList(const _3DPointList* plist);

/* 函数操作：初始化3D分形山脉链表					*/
/* 前提条件：plist指向	一个链表						*/
/*			point指向大小为4的初始种子点数组		*/
/* 后置条件：初始化成功，返回true；否则返回false		*/
bool InitMountain3D(_3DPointList* plist, const _3DPoint* point);

/* 函数操作：获取以plist为头节点的相邻四个点的中心点O的三维坐标信息		*/
/* 前提条件：plist指向	一个已初始化的3D分形山脉链表					*/
/*			h为高度因子，tflag和lflag为寻点标记						*/
/* 后置条件：返回中点O的三维坐标点									*/
_3DPoint GetCentre(const _3DPointList* plist, double h, bool tflag, bool lflag);

/* 函数操作：求出以A，B，C，D组成的四条边的中点的三维坐标信息并插入		*/
/* 前提条件：A，B，C，D表示四个相邻的端点							*/
/*			h为高度因子，tflag和lflag为寻点标记						*/
/* 后置条件：添加成功，返回true，否则返回false						*/
bool SetFourPoint(Node* pA, Node* pB, Node* pC, Node* pD, double h, bool tflag, bool lflag);

/* 函数操作：将中心点O三维坐标信息插入3D分形山脉链表	*/
/* 前提条件：plist指向	一个已初始化的3D分形山脉链表	*/
/*			point为中心点O的三维坐标信息			*/
/* 后置条件：添加成功，返回true，否则返回false		*/
bool SetCentre(_3DPointList* plist, _3DPoint point);

/* 函数操作：迭代3D分形山脉的节点					*/
/* 前提条件：plist指向	一个已初始化的3D分形山脉链表	*/
/*			h为高度因子，b为缩放因子，n为迭代次数	*/
/* 后置条件：迭代成功，返回true，否则返回false		*/
bool IterMountain3D(_3DPointList* plist, double h, const double b, const int n);

/* 函数操作：绘制3D分形山脉链表的节点连线				*/
/* 前提条件：plist指向	一个已初始化的3D分形山脉链表	*/
/* 后置条件：绘制出3D分形山脉						*/
void DrawMountain3D(const _3DPointList* plist);

#endif
