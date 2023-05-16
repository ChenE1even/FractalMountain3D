#include "Mountain3D.h"
#include "Button.h"
#include <stdio.h>
#include <graphics.h>
#include <conio.h>

#define WINDOW_L	1080					/* ���ڳ��� */
#define WINDOW_H	720						/* ���ڸ߶� */

/* �ֲ�����ԭ�� */
static void InitWindow(int length, int height);

int main(void) {
	InitWindow(WINDOW_L, WINDOW_H);			/* ��ʼ�����ڴ�С�����عرռ� */
	ChangeWindowText(L"����ɽģ�����");		/* �ı䴰�ڱ��� */
	printf("[INFO] �������\n");

	/* �������������ű������߶����ӡ������α߳� */
	int iterNumber = 0;
	double scaleFactor = 0;					/* 1.76 - 2.60 */
	double heightFactor = 0;
	double squareLength = 0;

	/* �ĸ������ʼ�߶�ֵ */
	double aHeight = 0;
	double bHeight = 0;
	double cHeight = 0;
	double dHeight = 0;

	/* �ı�������ı� */
	wchar_t nString[10] = L"";
	wchar_t bString[10] = L"";
	wchar_t hString[10] = L"";
	wchar_t squareString[10] = L"";
	wchar_t _aString[10] = L"";
	wchar_t _bString[10] = L"";
	wchar_t _cString[10] = L"";
	wchar_t _dString[10] = L"";

	/* �Ƿ������ж� */
	bool isOK = 0;

	while (1) {
		BeginBatchDraw();						/* ��ʼ������ͼ��ȡ����ͼ���� */

		/* �ֿ� */
		setbkmode(TRANSPARENT);
		setfillcolor(MATCHA_GREEN);
		solidroundrect(0, 0, 360, 720, 10, 10);
		/* ��һ�� */
		SetText(70, 40, 220, 30, L"��ά����������");
		/* �ڶ��� */
		SetText(20, 110, 150, 25, L"��������(n)");
		SetTextRectangle(190, 110, 150, 25, nString);
		/* ������ */
		SetText(20, 155, 150, 25, L"���ű���(b)");
		SetTextRectangle(190, 155, 150, 25, bString);
		/* ������ */
		SetText(20, 200, 150, 25, L"�߶�����(h)");
		SetTextRectangle(190, 200, 150, 25, hString);
		/* ������ */
		SetText(20, 245, 150, 25, L"�����α߳�");
		SetTextRectangle(190, 245, 150, 25, squareString);
		/* ������ */
		SetText(50, 290, 260, 25, L"�������Ķ���߶�ֵ");
		/* ������ */
		SetTextRectangle(21, 335, 72, 25, _aString);
		SetTextRectangle(103, 335, 72, 25, _bString);
		SetTextRectangle(185, 335, 72, 25, _cString);
		SetTextRectangle(267, 335, 72, 25, _dString);
		/* �ڰ��� */
		SetButton(90, 400, 180, 60, L"����");
		/* �ھ��� */
		SetButton(90, 500, 180, 60, L"�˳�");
		/* ˮӡ */
		SetTextRectangle(990, 700, 80, 20, L"-ChenE1even-");

		EndBatchDraw();							/* ����������ͼ */

		if (MouseHit()) {						/* �������� */
			MOUSEMSG msg = GetMouseMsg();		/* ��������� */
			if (msg.uMsg == WM_LBUTTONDOWN) {	/* �Ƿ�����������Ч����� */
				/* ǰ���� */
				if (msg.x > 190 && msg.x < 340) {
					/* ����������� */
					if (msg.y > 110 && msg.y < 135) {
						printf("[INFO] ���������������\n");
						isOK = InputBox(nString, 10, L"\n\t\t���������������n) <1-9>", 0, 0, 0, 100, 0);			/* ��������Ի������� */
						if (isOK) {																				/* �ж��Ƿ����� */
							while ((iterNumber = _wtoi(nString)) < 1 || iterNumber > 9) {						/* �洢ת��������룬���������Ϸ��� */
								printf("\a[ERROR] ����Ƿ�\n");
								InputBox(nString, 10, L"\t\t\t���Ƿ����롿\n\t\t��������������Σ�n) <1-9>", 0, 0, 0, 100);
							}
							SetTextRectangle(190, 110, 150, 25, nString);										/* ����������ı���ʾ */
							printf("[INFO] ���µ���������%d\n", iterNumber);
						}
						else 
							printf("[WARNING] δ���µ�������\n");
					}
					/* �������ű��� */
					if (msg.y > 155 && msg.y < 180) {
						printf("[INFO] ������������\n");
						isOK = InputBox(bString, 10, L"\n\t\t�������������ӣ�b) <1.00-4.00>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((scaleFactor = _wtof(bString)) < 1 || scaleFactor > 4) {
								printf("\a[ERROR] ����Ƿ�\n");
								InputBox(bString, 10, L"\t\t\t���Ƿ����롿\n\t\t�������������ӣ�b) <1.00-4.00>", 0, 0, 0, 100);
							}
							SetTextRectangle(190, 155, 150, 25, bString);
							printf("[INFO] �����������ӣ�%0.2lf\n", scaleFactor);
						}
						else
							printf("[WARNING] δ������������\n");
					}
					/* ����߶����� */
					if (msg.y > 200 && msg.y < 225) {
						printf("[INFO] ��������߶�����\n");
						isOK = InputBox(hString, 10, L"\n\t\t������߶�����(h)<1-256>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((heightFactor = _wtof(hString)) < 1 || heightFactor > 256) {
								printf("\a[ERROR] ����Ƿ�\n");
								InputBox(hString, 10, L"\t\t\t���Ƿ����롿\n\t\t������߶�����(h)<1-256>", 0, 0, 0, 100);
							}
							SetTextRectangle(190, 200, 150, 25, hString);
							printf("[INFO] ���¸߶����ӣ�%0.0lf\n", heightFactor);
						}
						else
							printf("[WARNING] δ���¸߶�����\n");
						
					}
					/* ���������α߳� */
					if (msg.y > 245 && msg.y < 270) {
						printf("[INFO] �������������α߳�\n");
						isOK = InputBox(squareString, 10, L"\n\t\t�����������α䳤<256-460>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((squareLength = _wtof(squareString)) < 256 || squareLength > 460) {
								printf("\a[ERROR] ����Ƿ�\n");
								InputBox(squareString, 10, L"\t\t\t���Ƿ����롿\n\t\t�����������α䳤<256-460>", 0, 0, 0, 100);
							}
							SetTextRectangle(190, 245, 150, 25, squareString);
							printf("[INFO] ���������α߳���%0.0f\n", squareLength);
						}
						else
							printf("[WARNING] δ���������α߳�\n");
					}
				}
				/* �Ķ���߶�ֵ */
				if (msg.y > 335 && msg.y < 360) {
					/* A���� */
					if (msg.x > 21 && msg.x < 93) {
						printf("[INFO] ���������һ������ĸ߶�\n");
						isOK = InputBox(_aString, 10, L"\n\t\t�������һ������ĸ߶�<0-256>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((aHeight = _wtof(_aString)) < 0 || aHeight > 256) {
								printf("\a[ERROR] ����Ƿ�\n");
								InputBox(_aString, 10, L"\t\t\t���Ƿ����롿\n\t\t�������һ������߶�<0-256>", 0, 0, 0, 100);
							}
							SetTextRectangle(21, 335, 72, 25, _aString);
							printf("[INFO] ���µ�һ������ĸ߶ȣ�%0.0f\n", aHeight);
						}
						else
							printf("[WARNING] δ���µ�һ������ĸ߶�\n");
					}
					/* B���� */
					if (msg.x > 103 && msg.x < 175) {
						printf("[INFO] ��������ڶ�������ĸ߶�\n");
						isOK = InputBox(_bString, 10, L"\n\t\t������ڶ�������ĸ߶�<0-256>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((bHeight = _wtof(_bString)) < 0 || bHeight > 256) {
								printf("\a[ERROR] ����Ƿ�\n");
								InputBox(_bString, 10, L"\t\t\t���Ƿ����롿\n\t\t������ڶ�������߶�<0-256>", 0, 0, 0, 100);
							}
							SetTextRectangle(103, 335, 72, 25, _bString);
							printf("[INFO] ���µڶ�������ĸ߶ȣ�%0.0f\n", bHeight);
						}
						else 
							printf("[WARNING] δ���µڶ�������ĸ߶�\n");
					}
					/* C���� */
					if (msg.x > 185 && msg.x < 257) {
						printf("[INFO] �����������������ĸ߶�\n");
						isOK = InputBox(_cString, 10, L"\n\t\t���������������ĸ߶�<0-256>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((cHeight = _wtof(_cString)) < 0 || cHeight > 256) {
								printf("\a[ERROR] ����Ƿ�\n");
								InputBox(_cString, 10, L"\t\t\t���Ƿ����롿\n\t\t���������������߶�<0-256>", 0, 0, 0, 100);
							}
							SetTextRectangle(185, 335, 72, 25, _cString);
							printf("[INFO] ���µ���������ĸ߶ȣ�%0.0f\n", cHeight);
						}
						else
							printf("[WARNING] δ���µ���������ĸ߶�\n");
					}
					/* D���� */
					if (msg.x > 267 && msg.x < 339) {
						printf("[INFO] ����������ĸ�����ĸ߶�\n");
						isOK = InputBox(_dString, 10, L"\n\t\t��������ĸ�����ĸ߶�<0-256>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((dHeight = _wtof(_dString)) < 0 || dHeight > 256) {
								printf("\a[ERROR] ����Ƿ�\n");
								InputBox(_dString, 10, L"\t\t\t���Ƿ����롿\n\t\t��������ĸ�����߶�<0-256>", 0, 0, 0, 100);
							}
							SetTextRectangle(267, 335, 72, 25, _dString);
							printf("[INFO] ���µ��ĸ�����ĸ߶ȣ�%0.0f\n", dHeight);
						}
						else
							printf("[WARNING] δ���µ��ĸ�����ĸ߶�\n");
					}
				}
				/* ����ģ�� */
				if (msg.x > 90 && msg.x < 270 && msg.y > 400 && msg.y < 460)
				{
					/* �жϲ����Ƿ��ʼ�� */
					if (iterNumber && scaleFactor && heightFactor && squareLength) {
						BeginBatchDraw();				/* ��ʼ������ͼ */
						cleardevice();					/* ������һ��ɽ��ģ�� */

						double seedX = WINDOW_H - squareLength - 128;
						double seedY = WINDOW_H / 2 + squareLength / 4;
						_3DPointList mountainList;
						_3DPoint seedPoint[4] = {		/* �ĸ����ӵ� */
							{ seedX, seedY, aHeight },
							{ seedX + squareLength, seedY, bHeight },
							{ seedX, seedY + squareLength, cHeight },
							{ seedX + squareLength, seedY + squareLength, dHeight }
						};

						InitList(&mountainList);												/* ��ʼ������ */
						printf("[INFO] ��������ɽ��.\n");
						InitMountain3D(&mountainList, seedPoint);								/* ��ʼ��ɽ�� */
						printf("[INFO] ��������ɽ��..\n");
						IterMountain3D(&mountainList, heightFactor, scaleFactor, iterNumber);	/* ����ɽ�� */
						printf("[INFO] ��������ɽ��...\n");
						
						setlinecolor(MATCHA_GREEN);						/* ����ɽ����ɫ */
						DrawMountain3D(&mountainList);					/* ����ɽ�� */
						
						printf("[INFO] �ɹ�����ɽ��\n");
						EmptyTheList(&mountainList);					/* ���ɽ���ͷ��ڴ� */
						EndBatchDraw();									/* ����������ͼ */
						
					} 
					else {							/* ����δ��ʼ�� */
						printf("'\a'[ERROR] �в���δ��ʼ����\n");
						HWND hwnd = GetHWnd();		/* ��þ�� */
						/* ���� */
						MessageBox(hwnd, L"�в���δ��ʼ����", L"����", MB_OK);
					}
				}
				/* �˳���� */
				if (msg.x > 90 && msg.x < 270 && msg.y > 500 && msg.y < 560)
				{
					closegraph();
					printf("[INFO] �˳����\n");
					exit(0);
				}
			}
		}
	}

	_getch();
	closegraph();

	return 0;
}

/* �ֲ��������� */
static void InitWindow(int length, int height) {
	initgraph(length, height, EW_NOCLOSE) ;		/* ��������û�йرհ�ť */
	setbkcolor(OFF_WHITE);
	cleardevice();
}