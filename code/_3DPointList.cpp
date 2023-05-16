#include "_3DPointList.h"
#include <stdlib.h>

/* 局部函数原型 */

static void CopyToPoint(Node* pnode, _3DPoint point);

/* 函数定义 */

/* 初始化 */
void InitList(_3DPointList* plist) {
	*plist = NULL;
}

/* 判空 */
bool ListIsEmpty(const _3DPointList* plist) {
	if (*plist == NULL)
		return true;
	else
		return false;
}

/* 判满 */
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

/* 右端末尾插入 */
bool AddRightEndPoint(_3DPointList* plist, _3DPoint point) {
	Node* tempNode = *plist;
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return false;

	CopyToPoint(newNode, point);			/* 将三维坐标点存入节点 */
	newNode->right = NULL;
	newNode->bottom = NULL;
	if (tempNode == NULL)
		*plist = newNode;
	else {
		while (tempNode->right)				/* 找到右端末尾 */
			tempNode = tempNode->right;
		tempNode->right = newNode;
	}

	return true;
}

/* 底端末尾插入 */
bool AddBottomEndPoint(_3DPointList* plist, const _3DPoint point) {
	Node* tempNode = *plist;
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return false;

	CopyToPoint(newNode, point);			/* 将三维坐标点存入节点 */
	newNode->right = NULL;
	newNode->bottom = NULL;
	if (tempNode == NULL)
		*plist = newNode;
	else {
		while (tempNode->bottom)			/* 找到底端末尾 */
			tempNode = tempNode->bottom;
		tempNode->bottom = newNode;
	}

	return true;
}

/* 右端相邻节点中间插入 */
bool AddRightMidPoint(Node* node, _3DPoint point) {
	Node* tempNode = node;
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return false;

	CopyToPoint(newNode, point);			/* 将三维坐标点存入节点 */
	newNode->bottom = NULL;
	newNode->right = tempNode->right;
	tempNode->right = newNode;

	return true;
}

/* 底端相邻节点中间插入 */
bool AddBottomMidPoint(Node* node, _3DPoint point) {
	Node* tempNode = node;
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return false;

	CopyToPoint(newNode, point);			/* 将三维坐标点存入节点 */
	newNode->right = NULL;
	newNode->bottom = tempNode->bottom;
	tempNode->bottom = newNode;

	return true;
}

/* 清空链表 */
void EmptyTheList(_3DPointList* plist) {
	Node* rightNode = *plist;
	Node* bottomNode = *plist;
	Node* temp;
	while (bottomNode) {					/* 检索底端 */
		rightNode = rightNode->right;
		while (rightNode) {					/* 检索右端 */
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

/* 局部函数声明 */
static void CopyToPoint(Node* pnode, _3DPoint point) {
	pnode->point = point;					/* 三维坐标信息存入 */
}