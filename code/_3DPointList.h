#ifndef _3DPOINTLIST_H_
#define _3DPOINTLIST_H_
#include <stdbool.h>

/* ���Ͷ��� */
typedef struct {
	double X;
	double Y;
	double Z;
} _3DPoint;					/* ��ά����� */

typedef struct node {
	_3DPoint point;
	struct node* right;		/* �Ҷ˽ڵ� */
	struct node* bottom;	/* �׶˽ڵ� */
} Node;

typedef Node* _3DPointList;

/* ����ԭ�� */

/* ������������ʼ��һ������							*/
/* ǰ��������plistָ��һ������						*/
/* ����������plist��ʼ��Ϊ��						*/
void InitList(_3DPointList* plist);

/* �����������ж�һ�������Ƿ�Ϊ��					*/
/* ǰ��������plistָ��һ���ѳ�ʼ��������				*/
/* ����������plistΪ�գ�����true�����򷵻�false		*/
bool ListIsEmpty(const _3DPointList* plist);

/* �����������ж�һ�������Ƿ�Ϊ��					*/
/* ǰ��������plistָ��һ���ѳ�ʼ��������				*/
/* ����������plistΪ��������true�����򷵻�false		*/
bool ListIsFull(const _3DPointList* plist);

/* �����������������Ҷ˵�ĩβ�����				*/
/* ǰ��������plistָ��һ���ѳ�ʼ��������				*/
/*		    point��һ����������������ά�����		*/
/* ������������ӳɹ�������true�����򷵻�false		*/
bool AddRightEndPoint(_3DPointList* plist, _3DPoint point);

/* ����������������׶˵�ĩβ�����				*/
/* ǰ��������plistָ��һ���ѳ�ʼ��������				*/
/*		    point��һ����������������ά�����		*/
/* ������������ӳɹ�������true�����򷵻�false		*/
bool AddBottomEndPoint(_3DPointList* plist, _3DPoint point);

/* �����������������Ҷ����ڽڵ��м�����				*/
/* ǰ��������plistָ��һ���ѳ�ʼ��������				*/
/*		    point��һ����������������ά�����		*/
/* ������������ӳɹ�������true�����򷵻�false		*/
bool AddRightMidPoint(Node* node, _3DPoint point);

/* ����������������׶����ڽڵ��м�����				*/
/* ǰ��������plistָ��һ���ѳ�ʼ��������				*/
/*		    point��һ����������������ά�����		*/
/* ������������ӳɹ�������true�����򷵻�false		*/
bool AddBottomMidPoint(Node* node, _3DPoint point);

/* ��������������������ͷ��ѷ�����ڴ�				*/
/* ǰ��������plistָ��һ���ѳ�ʼ��������				*/
/* �����������ͷ���Ϊ�������������ڴ棬��������Ϊ��	*/
void EmptyTheList(_3DPointList* plist);

#endif
