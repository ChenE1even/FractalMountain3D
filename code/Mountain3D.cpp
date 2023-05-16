#include "Mountain3D.h"
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* 局部函数原型 */
static void LogPoint(_3DPoint point);

/* 函数定义 */

/* 打印链表（测试用） */
void PrintList(const _3DPointList* plist) {
	if (ListIsEmpty(plist))
		printf("[INFO] 链表为空");
	else {
		Node* rightNode = *plist;
		Node* bottomNode = *plist;
		while (bottomNode) {						/* 检索底端 */
			while (rightNode) {						/* 检索右端 */
				LogPoint(rightNode->point);			/* 打印 */
				rightNode = rightNode->right;		/* 更新 */
			}
			bottomNode = bottomNode->bottom;
			rightNode = bottomNode;
		}
	}
}


/* 初始化3D分形山脉 */
bool InitMountain3D(_3DPointList* plist, const _3DPoint* ppoint) {
	if (ListIsFull(plist))
		return false;

	/* A点 */
	AddRightEndPoint(plist, ppoint[0]);
	/* B点 */
	AddRightEndPoint(plist, ppoint[1]);
	/* C点 */
	AddBottomEndPoint(plist, ppoint[2]);
	/* D点 */
	AddBottomEndPoint(&((*plist)->right), ppoint[3]);
	AddRightEndPoint(&((*plist)->bottom), ppoint[3]);

	return true;
}

/* 获取中心点O */
_3DPoint GetCentre(const _3DPointList* plist, double h, bool tflag, bool lflag) {
	double r = (double(rand() % 200) - 67) / 100;	/* 随机数 [-0.67, 1.33) */
	Node* tempNode = *plist;
	_3DPoint pointO = { 0, 0, 0 };

	_3DPoint pointA = tempNode->point;
	_3DPoint pointB;
	_3DPoint pointD;
	if (tflag) {									/* 上边已插入中点 */
		pointB = tempNode->right->point;
		pointD = tempNode->right->bottom->point;
	}
	else {
		pointB = tempNode->right->right->point;
		pointD = tempNode->right->right->bottom->point;
	}

	_3DPoint pointC;
	if (lflag)										/* 左边已插入中点 */
		pointC = tempNode->bottom->point;
	else
		pointC = tempNode->bottom->bottom->point;

	/* 计算中心点 */
	pointO.X = (pointA.X + pointB.X) / 2.0;
	pointO.Y = (pointA.Y + pointC.Y) / 2.0;
	pointO.Z = (pointA.Z + pointB.Z + pointC.Z + pointD.Z) / 4.0 + h * r;

	return pointO;
}

/* 插入中点E，F，G，H */
bool SetFourPoint(Node* pA, Node* pB, Node* pC, Node* pD, double h, bool tflag, bool lflag) {
	double r = (double(rand() % 200) - 67) / 100;	/* 随机数 [-0.67, 1.33) */
	_3DPoint E = { (pA->point.X + pB->point.X) / 2.0, 
				   (pA->point.Y + pB->point.Y) / 2.0,
				   ((pA->point.Z + pB->point.Z) / 2.0) + h * r };

	r = (double(rand() % 200) - 67) / 100;
	_3DPoint F = { (pA->point.X + pC->point.X) / 2.0, 
				   (pA->point.Y + pC->point.Y) / 2.0,
				   ((pA->point.Z + pC->point.Z) / 2.0) + h * r };

	r = (double(rand() % 200) - 67) / 100;
	_3DPoint G = { (pC->point.X + pD->point.X) / 2.0, 
				   (pC->point.Y + pD->point.Y) / 2.0,
				   ((pC->point.Z + pD->point.Z) / 2.0) + h * r };

	r = (double(rand() % 200) - 67) / 100;
	_3DPoint H = { (pB->point.X + pD->point.X) / 2, 
				   (pB->point.Y + pD->point.Y) / 2,
				   ((pB->point.Z + pD->point.Z) / 2.0) + h * r };

	if (tflag)										/* 上边已插入中点 */
		AddRightMidPoint(pA, E);
	if (lflag)										/* 左边已插入中点 */
		AddBottomMidPoint(pA, F);
	AddRightMidPoint(pC, G);
	if (!(AddBottomMidPoint(pB, H)))
		return false;

	return true;
}

/* 插入中心点O */
bool SetCentre(_3DPointList* plist, _3DPoint point) {
	/* 得到E，F，G，H四个中点 */
	Node* nodeE = (*plist)->right;
	Node* nodeF = (*plist)->bottom;
	Node* nodeG = (*plist)->bottom->bottom->right;
	Node* nodeH = (*plist)->right->right->bottom;

	Node* nodeO = (Node*)malloc(sizeof(Node));

	if (nodeO == NULL)
		return false;

	/* 插入中心点O */
	nodeO->point = point;
	nodeE->bottom = nodeO;
	nodeF->right = nodeO;
	nodeO->right = nodeH;
	nodeO->bottom = nodeG;

	return true;
}

/* 迭代3D分形山脉 */
bool IterMountain3D(_3DPointList* plist, double h, double b, int n) {
	if (ListIsEmpty(plist))
		return false;								/* 错误返回 */

	Node* bottomNode;
	Node* rightNode;
	_3DPoint pointO;
	Node* nodeA;
	Node* nodeB;
	Node* nodeC;
	Node* nodeD;

	srand((unsigned)time(NULL));					/* 设置随机数种子 */

	for (int count = 0; count < n; count++) {		/* 进入迭代 */
		bottomNode = *plist;						/* 初始化底端检索开始点 */
		nodeA = bottomNode;							/* 初始化A，B，C，D四顶点位置 */
		nodeB = nodeA->right;
		nodeC = nodeA->bottom;
		nodeD = nodeC->right;
		bool topFlag = 1, leftFlag = 1;				/* 初始化标记 */

		while (bottomNode->bottom) {				/* 检索底端 */
			rightNode = bottomNode;					/* 初始化右端检索开始点 */
			while (rightNode->right) {				/* 检索右端 */
				pointO = GetCentre(&rightNode, h, topFlag, leftFlag);
				if (!(SetFourPoint(nodeA, nodeB, nodeC, nodeD, h, topFlag, leftFlag)))
					return false;
				leftFlag = 0;						/* 更新标记 */
				if (!(SetCentre(&rightNode, pointO)))
					return false;
				if (nodeB->right) {					/* 检验并更新A，B，C，D四顶点 */
					nodeA = nodeB;
					nodeC = nodeD;
					if (topFlag)
						nodeB = nodeB->right;
					else
						nodeB = nodeB->right->right;
					nodeD = nodeD->right;
				}
				if (rightNode->right->right)		/* 检验是否能继续迭代右端 */
					rightNode = rightNode->right->right;
				else
					rightNode = rightNode->right;
			}
			topFlag = 0;							/* 更新标记 */
			leftFlag = 1;
			if (bottomNode->bottom->bottom)			/* 检验是否能继续迭代底端 */
				bottomNode = bottomNode->bottom->bottom;
			else
				bottomNode = bottomNode->bottom;
			if (bottomNode->bottom)					/* 检验并更新A，B，C，D四顶点 */
			{
				nodeA = bottomNode;
				nodeB = nodeA->right->right;
				nodeC = nodeA->bottom;
				nodeD = nodeC->right;
			}
		}
		h = h / b;									/* 更新高度因子 */
	}

	return true;
}

/* 绘制3D分形山脉 */
void DrawMountain3D(const _3DPointList* plist) {
	if (ListIsEmpty(plist))
		return;

	Node* rightNode = *plist;
	Node* bottomNode = *plist;
	double bias = 0.5;								/* 偏差 */
	while (bottomNode) {							/* 检索底端 */
		while (rightNode) {							/* 检索右端 */
			if (rightNode->right)					/* 连线 */
				line(rightNode->point.X + bias * rightNode->point.Y, 
					 rightNode->point.Z + bias * rightNode->point.Y,
					 rightNode->right->point.X + bias * rightNode->right->point.Y, 
					 rightNode->right->point.Z + bias * rightNode->right->point.Y);
			if (bottomNode->bottom)
				line(rightNode->point.X + bias * rightNode->point.Y, 
					 rightNode->point.Z + bias * rightNode->point.Y,
					 rightNode->bottom->point.X + bias * rightNode->bottom->point.Y, 
					 rightNode->bottom->point.Z + bias * rightNode->bottom->point.Y);
			rightNode = rightNode->right;
		}
		bottomNode = bottomNode->bottom;
		rightNode = bottomNode;
	}
}

/* 局部函数定义 */
static void LogPoint(_3DPoint point) {
	printf("X = %.0lf, Y = %.0lf, Z = %.0lf\n",
		point.X, point.Y, point.Z);
}