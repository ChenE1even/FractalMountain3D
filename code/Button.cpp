#include "Button.h"
#include <graphics.h>

/* �������� */

/* �ı䴰�ڱ��� */
void ChangeWindowText(const wchar_t* text_) {
	HWND hwnd = GetHWnd();					/* ��ȡ���ھ�� */
	SetWindowText(hwnd, text_);

	/* ���� */
	/*
	wchar_t title[] = L"";
	wchar_t text[] = L"\t��ӭʹ����ά����ɽ��ģ����\t";

	int isOK = MessageBox(hwnd, text, title, MB_OKCANCEL);
	if (isOK == IDOK)
		printf("[INFO] �������\n");
	else if (isOK == IDCANCEL) {
		printf("[INFO] �˳����\n");
		closegraph();
	}
	*/
}

/* �����ı� */
void SetText(int x, int y, int width, int height, const wchar_t* text_) {
	setbkmode(TRANSPARENT);					/* ���ñ���ģʽ͸�� */
	//setfillcolor(MATCHA_GREEN);			/* (���Է�Χ��) */
	//fillrectangle(x, y, x + width, y + height);
		
	settextstyle(height, 0, L"����");		/* �����ı���С���ַ� */
	settextcolor(OFF_WHITE);				/* �����ı���ɫ */

	int text_X = x + (width - textwidth(text_)) / 2;
	int text_Y = y + (height - textheight(text_)) / 2;

	outtextxy(text_X, text_Y, text_);		/* ������ʾ�ı� */
}

/* �����ı��� */
void SetTextRectangle(int x, int y, int width, int height, const wchar_t* text_) {
	setbkmode(TRANSPARENT);
	setfillcolor(OFF_WHITE);
	solidroundrect(x, y, x + width, y + height, 10, 10);		/* Բ�Ǿ��ο� */

	settextstyle(height - 5, 0, L"����");
	settextcolor(MATCHA_GREEN);
	
	int text_X = x + (width - textwidth(text_)) / 2;
	int text_Y = y + (height - textheight(text_)) / 2;

	outtextxy(text_X, text_Y, text_);
}

/* ���ð�ť */
void SetButton(int x, int y, int width, int height, const wchar_t* text_) {
	setbkmode(TRANSPARENT);
	setfillcolor(OFF_WHITE);
	solidroundrect(x, y, x + width, y + height, 10, 10);

	settextstyle(height / 2, 0, L"����");
	settextcolor(MATCHA_GREEN);

	int text_X = x + (width - textwidth(text_)) / 2;
	int text_Y = y + (height - textheight(text_)) / 2;

	outtextxy(text_X, text_Y, text_);
}