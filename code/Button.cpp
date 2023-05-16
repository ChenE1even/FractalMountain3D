#include "Button.h"
#include <graphics.h>

/* 函数定义 */

/* 改变窗口标题 */
void ChangeWindowText(const wchar_t* text_) {
	HWND hwnd = GetHWnd();					/* 获取窗口句柄 */
	SetWindowText(hwnd, text_);

	/* 弹窗 */
	/*
	wchar_t title[] = L"";
	wchar_t text[] = L"\t欢迎使用三维分形山脉模拟器\t";

	int isOK = MessageBox(hwnd, text, title, MB_OKCANCEL);
	if (isOK == IDOK)
		printf("[INFO] 进入软件\n");
	else if (isOK == IDCANCEL) {
		printf("[INFO] 退出软件\n");
		closegraph();
	}
	*/
}

/* 放置文本 */
void SetText(int x, int y, int width, int height, const wchar_t* text_) {
	setbkmode(TRANSPARENT);					/* 设置背景模式透明 */
	//setfillcolor(MATCHA_GREEN);			/* (测试范围用) */
	//fillrectangle(x, y, x + width, y + height);
		
	settextstyle(height, 0, L"楷体");		/* 设置文本大小，字符 */
	settextcolor(OFF_WHITE);				/* 设置文本颜色 */

	int text_X = x + (width - textwidth(text_)) / 2;
	int text_Y = y + (height - textheight(text_)) / 2;

	outtextxy(text_X, text_Y, text_);		/* 居中显示文本 */
}

/* 放置文本框 */
void SetTextRectangle(int x, int y, int width, int height, const wchar_t* text_) {
	setbkmode(TRANSPARENT);
	setfillcolor(OFF_WHITE);
	solidroundrect(x, y, x + width, y + height, 10, 10);		/* 圆角矩形框 */

	settextstyle(height - 5, 0, L"楷体");
	settextcolor(MATCHA_GREEN);
	
	int text_X = x + (width - textwidth(text_)) / 2;
	int text_Y = y + (height - textheight(text_)) / 2;

	outtextxy(text_X, text_Y, text_);
}

/* 放置按钮 */
void SetButton(int x, int y, int width, int height, const wchar_t* text_) {
	setbkmode(TRANSPARENT);
	setfillcolor(OFF_WHITE);
	solidroundrect(x, y, x + width, y + height, 10, 10);

	settextstyle(height / 2, 0, L"楷体");
	settextcolor(MATCHA_GREEN);

	int text_X = x + (width - textwidth(text_)) / 2;
	int text_Y = y + (height - textheight(text_)) / 2;

	outtextxy(text_X, text_Y, text_);
}