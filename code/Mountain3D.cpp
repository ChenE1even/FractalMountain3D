#include "Mountain3D.h"
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* �ֲ�����ԭ�� */
static void LogPoint(_3DPoint point);

/* �������� */

/* ��ӡ���������ã� */
void PrintList(const _3DPointList* plist) {
	if (ListIsEmpty(plist))
		printf("[INFO] ����Ϊ��");
	else {
		Node* rightNode = *plist;
		Node* bottomNode = *plist;
		while (bottomNode) {						/* �����׶� */
			while (rightNode) {						/* �����Ҷ� */
				LogPoint(rightNode->point);			/* ��ӡ */
				rightNode = rightNode->right;		/* ���� */
			}
			bottomNode = bottomNode->bottom;
			rightNode = bottomNode;
		}
	}
}


/* ��ʼ��3D����ɽ�� */
bool InitMountain3D(_3DPointList* plist, const _3DPoint* ppoint) {
	if (ListIsFull(plist))
		return false;

	/* A�� */
	AddRightEndPoint(plist, ppoint[0]);
	/* B�� */
	AddRightEndPoint(plist, ppoint[1]);
	/* C�� */
	AddBottomEndPoint(plist, ppoint[2]);
	/* D�� */
	AddBottomEndPoint(&((*plist)->right), ppoint[3]);
	AddRightEndPoint(&((*plist)->bottom), ppoint[3]);

	return true;
}

/* ��ȡ���ĵ�O */
_3DPoint GetCentre(const _3DPointList* plist, double h, bool tflag, bool lflag) {
	double r = (double(rand() % 200) - 67) / 100;	/* ����� [-0.67, 1.33) */
	Node* tempNode = *plist;
	_3DPoint pointO = { 0, 0, 0 };

	_3DPoint pointA = tempNode->point;
	_3DPoint pointB;
	_3DPoint pointD;
	if (tflag) {									/* �ϱ��Ѳ����е� */
		pointB = tempNode->right->point;
		pointD = tempNode->right->bottom->point;
	}
	else {
		pointB = tempNode->right->right->point;
		pointD = tempNode->right->right->bottom->point;
	}

	_3DPoint pointC;
	if (lflag)										/* ����Ѳ����е� */
		pointC = tempNode->bottom->point;
	else
		pointC = tempNode->bottom->bottom->point;

	/* �������ĵ� */
	pointO.X = (pointA.X + pointB.X) / 2.0;
	pointO.Y = (pointA.Y + pointC.Y) / 2.0;
	pointO.Z = (pointA.Z + pointB.Z + pointC.Z + pointD.Z) / 4.0 + h * r;

	return pointO;
}

/* �����е�E��F��G��H */
bool SetFourPoint(Node* pA, Node* pB, Node* pC, Node* pD, double h, bool tflag, bool lflag) {
	double r = (double(rand() % 200) - 67) / 100;	/* ����� [-0.67, 1.33) */
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

	if (tflag)										/* �ϱ��Ѳ����е� */
		AddRightMidPoint(pA, E);
	if (lflag)										/* ����Ѳ����е� */
		AddBottomMidPoint(pA, F);
	AddRightMidPoint(pC, G);
	if (!(AddBottomMidPoint(pB, H)))
		return false;

	return true;
}

/* �������ĵ�O */
bool SetCentre(_3DPointList* plist, _3DPoint point) {
	/* �õ�E��F��G��H�ĸ��е� */
	Node* nodeE = (*plist)->right;
	Node* nodeF = (*plist)->bottom;
	Node* nodeG = (*plist)->bottom->bottom->right;
	Node* nodeH = (*plist)->right->right->bottom;

	Node* nodeO = (Node*)malloc(sizeof(Node));

	if (nodeO == NULL)
		return false;

	/* �������ĵ�O */
	nodeO->point = point;
	nodeE->bottom = nodeO;
	nodeF->right = nodeO;
	nodeO->right = nodeH;
	nodeO->bottom = nodeG;

	return true;
}

/* ����3D����ɽ�� */
bool IterMountain3D(_3DPointList* plist, double h, double b, int n) {
	if (ListIsEmpty(plist))
		return false;								/* ���󷵻� */

	Node* bottomNode;
	Node* rightNode;
	_3DPoint pointO;
	Node* nodeA;
	Node* nodeB;
	Node* nodeC;
	Node* nodeD;

	srand((unsigned)time(NULL));					/* ������������� */

	for (int count = 0; count < n; count++) {		/* ������� */
		bottomNode = *plist;						/* ��ʼ���׶˼�����ʼ�� */
		nodeA = bottomNode;							/* ��ʼ��A��B��C��D�Ķ���λ�� */
		nodeB = nodeA->right;
		nodeC = nodeA->bottom;
		nodeD = nodeC->right;
		bool topFlag = 1, leftFlag = 1;				/* ��ʼ����� */

		while (bottomNode->bottom) {				/* �����׶� */
			rightNode = bottomNode;					/* ��ʼ���Ҷ˼�����ʼ�� */
			while (rightNode->right) {				/* �����Ҷ� */
				pointO = GetCentre(&rightNode, h, topFlag, leftFlag);
				if (!(SetFourPoint(nodeA, nodeB, nodeC, nodeD, h, topFlag, leftFlag)))
					return false;
				leftFlag = 0;						/* ���±�� */
				if (!(SetCentre(&rightNode, pointO)))
					return false;
				if (nodeB->right) {					/* ���鲢����A��B��C��D�Ķ��� */
					nodeA = nodeB;
					nodeC = nodeD;
					if (topFlag)
						nodeB = nodeB->right;
					else
						nodeB = nodeB->right->right;
					nodeD = nodeD->right;
				}
				if (rightNode->right->right)		/* �����Ƿ��ܼ��������Ҷ� */
					rightNode = rightNode->right->right;
				else
					rightNode = rightNode->right;
			}
			topFlag = 0;							/* ���±�� */
			leftFlag = 1;
			if (bottomNode->bottom->bottom)			/* �����Ƿ��ܼ��������׶� */
				bottomNode = bottomNode->bottom->bottom;
			else
				bottomNode = bottomNode->bottom;
			if (bottomNode->bottom)					/* ���鲢����A��B��C��D�Ķ��� */
			{
				nodeA = bottomNode;
				nodeB = nodeA->right->right;
				nodeC = nodeA->bottom;
				nodeD = nodeC->right;
			}
		}
		h = h / b;									/* ���¸߶����� */
	}

	return true;
}

/* ����3D����ɽ�� */
void DrawMountain3D(const _3DPointList* plist) {
	if (ListIsEmpty(plist))
		return;

	Node* rightNode = *plist;
	Node* bottomNode = *plist;
	double bias = 0.5;								/* ƫ�� */
	while (bottomNode) {							/* �����׶� */
		while (rightNode) {							/* �����Ҷ� */
			if (rightNode->right)					/* ���� */
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

/* �ֲ��������� */
static void LogPoint(_3DPoint point) {
	printf("X = %.0lf, Y = %.0lf, Z = %.0lf\n",
		point.X, point.Y, point.Z);
}