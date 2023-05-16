#include "_3DPointList.h"
#include <stdlib.h>

/* �ֲ�����ԭ�� */

static void CopyToPoint(Node* pnode, _3DPoint point);

/* �������� */

/* ��ʼ�� */
void InitList(_3DPointList* plist) {
	*plist = NULL;
}

/* �п� */
bool ListIsEmpty(const _3DPointList* plist) {
	if (*plist == NULL)
		return true;
	else
		return false;
}

/* ���� */
bool ListIsFull(const _3DPointList* plist) {
	_3DPointList* pt;
	bool full;

	pt = (_3DPointList*)malloc(sizeof(_3DPointList));
	if (pt == NULL)
		full = true;
	else
		full = false;

	return full;
}

/* �Ҷ�ĩβ���� */
bool AddRightEndPoint(_3DPointList* plist, _3DPoint point) {
	Node* tempNode = *plist;
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return false;

	CopyToPoint(newNode, point);			/* ����ά��������ڵ� */
	newNode->right = NULL;
	newNode->bottom = NULL;
	if (tempNode == NULL)
		*plist = newNode;
	else {
		while (tempNode->right)				/* �ҵ��Ҷ�ĩβ */
			tempNode = tempNode->right;
		tempNode->right = newNode;
	}

	return true;
}

/* �׶�ĩβ���� */
bool AddBottomEndPoint(_3DPointList* plist, const _3DPoint point) {
	Node* tempNode = *plist;
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return false;

	CopyToPoint(newNode, point);			/* ����ά��������ڵ� */
	newNode->right = NULL;
	newNode->bottom = NULL;
	if (tempNode == NULL)
		*plist = newNode;
	else {
		while (tempNode->bottom)			/* �ҵ��׶�ĩβ */
			tempNode = tempNode->bottom;
		tempNode->bottom = newNode;
	}

	return true;
}

/* �Ҷ����ڽڵ��м���� */
bool AddRightMidPoint(Node* node, _3DPoint point) {
	Node* tempNode = node;
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return false;

	CopyToPoint(newNode, point);			/* ����ά��������ڵ� */
	newNode->bottom = NULL;
	newNode->right = tempNode->right;
	tempNode->right = newNode;

	return true;
}

/* �׶����ڽڵ��м���� */
bool AddBottomMidPoint(Node* node, _3DPoint point) {
	Node* tempNode = node;
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return false;

	CopyToPoint(newNode, point);			/* ����ά��������ڵ� */
	newNode->right = NULL;
	newNode->bottom = tempNode->bottom;
	tempNode->bottom = newNode;

	return true;
}

/* ������� */
void EmptyTheList(_3DPointList* plist) {
	Node* rightNode = *plist;
	Node* bottomNode = *plist;
	Node* temp;
	while (bottomNode) {					/* �����׶� */
		rightNode = rightNode->right;
		while (rightNode) {					/* �����Ҷ� */
			temp = rightNode->right;
			free(rightNode);
			rightNode = temp;
		}
		temp = bottomNode->bottom;
		free(bottomNode);
		bottomNode = temp;
		rightNode = bottomNode;
	}
}

/* �ֲ��������� */
static void CopyToPoint(Node* pnode, _3DPoint point) {
	pnode->point = point;					/* ��ά������Ϣ���� */
}