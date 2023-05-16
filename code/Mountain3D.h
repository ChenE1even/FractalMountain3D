#ifndef _MOUNTAIN3D_H_
#define _MOUNTAIN3D_H_
#include "_3DPointList.h"

/* ����ԭ�� */

/* ��������������������ӡ�������ã�				*/
/* ǰ��������plistָ��һ���ѳ�ʼ��������				*/
/* ������������ӡ��������ά��������Ϣ				*/
void PrintList(const _3DPointList* plist);

/* ������������ʼ��3D����ɽ������					*/
/* ǰ��������plistָ��	һ������						*/
/*			pointָ���СΪ4�ĳ�ʼ���ӵ�����		*/
/* ������������ʼ���ɹ�������true�����򷵻�false		*/
bool InitMountain3D(_3DPointList* plist, const _3DPoint* point);

/* ������������ȡ��plistΪͷ�ڵ�������ĸ�������ĵ�O����ά������Ϣ		*/
/* ǰ��������plistָ��	һ���ѳ�ʼ����3D����ɽ������					*/
/*			hΪ�߶����ӣ�tflag��lflagΪѰ����						*/
/* ���������������е�O����ά�����									*/
_3DPoint GetCentre(const _3DPointList* plist, double h, bool tflag, bool lflag);

/* ���������������A��B��C��D��ɵ������ߵ��е����ά������Ϣ������		*/
/* ǰ��������A��B��C��D��ʾ�ĸ����ڵĶ˵�							*/
/*			hΪ�߶����ӣ�tflag��lflagΪѰ����						*/
/* ������������ӳɹ�������true�����򷵻�false						*/
bool SetFourPoint(Node* pA, Node* pB, Node* pC, Node* pD, double h, bool tflag, bool lflag);

/* ���������������ĵ�O��ά������Ϣ����3D����ɽ������	*/
/* ǰ��������plistָ��	һ���ѳ�ʼ����3D����ɽ������	*/
/*			pointΪ���ĵ�O����ά������Ϣ			*/
/* ������������ӳɹ�������true�����򷵻�false		*/
bool SetCentre(_3DPointList* plist, _3DPoint point);

/* ��������������3D����ɽ���Ľڵ�					*/
/* ǰ��������plistָ��	һ���ѳ�ʼ����3D����ɽ������	*/
/*			hΪ�߶����ӣ�bΪ�������ӣ�nΪ��������	*/
/* ���������������ɹ�������true�����򷵻�false		*/
bool IterMountain3D(_3DPointList* plist, double h, const double b, const int n);

/* ��������������3D����ɽ������Ľڵ�����				*/
/* ǰ��������plistָ��	һ���ѳ�ʼ����3D����ɽ������	*/
/* �������������Ƴ�3D����ɽ��						*/
void DrawMountain3D(const _3DPointList* plist);

#endif
