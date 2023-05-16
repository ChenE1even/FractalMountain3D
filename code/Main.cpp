#include "Mountain3D.h"
#include "Button.h"
#include <stdio.h>
#include <graphics.h>
#include <conio.h>

#define WINDOW_L	1080					/* 窗口长度 */
#define WINDOW_H	720						/* 窗口高度 */

/* 局部函数原型 */
static void InitWindow(int length, int height);

int main(void) {
	InitWindow(WINDOW_L, WINDOW_H);			/* 初始化窗口大小，隐藏关闭键 */
	ChangeWindowText(L"分形山模拟软件");		/* 改变窗口标题 */
	printf("[INFO] 进入软件\n");

	/* 迭代次数、缩放倍数、高度因子、正方形边长 */
	int iterNumber = 0;
	double scaleFactor = 0;					/* 1.76 - 2.60 */
	double heightFactor = 0;
	double squareLength = 0;

	/* 四个顶点初始高度值 */
	double aHeight = 0;
	double bHeight = 0;
	double cHeight = 0;
	double dHeight = 0;

	/* 文本框接受文本 */
	wchar_t nString[10] = L"";
	wchar_t bString[10] = L"";
	wchar_t hString[10] = L"";
	wchar_t squareString[10] = L"";
	wchar_t _aString[10] = L"";
	wchar_t _bString[10] = L"";
	wchar_t _cString[10] = L"";
	wchar_t _dString[10] = L"";

	/* 是否输入判断 */
	bool isOK = 0;

	while (1) {
		BeginBatchDraw();						/* 开始批量绘图，取消绘图卡顿 */

		/* 分块 */
		setbkmode(TRANSPARENT);
		setfillcolor(MATCHA_GREEN);
		solidroundrect(0, 0, 360, 720, 10, 10);
		/* 第一行 */
		SetText(70, 40, 220, 30, L"三维地形生成器");
		/* 第二行 */
		SetText(20, 110, 150, 25, L"迭代次数(n)");
		SetTextRectangle(190, 110, 150, 25, nString);
		/* 第三行 */
		SetText(20, 155, 150, 25, L"缩放倍数(b)");
		SetTextRectangle(190, 155, 150, 25, bString);
		/* 第四行 */
		SetText(20, 200, 150, 25, L"高度因子(h)");
		SetTextRectangle(190, 200, 150, 25, hString);
		/* 第五行 */
		SetText(20, 245, 150, 25, L"正方形边长");
		SetTextRectangle(190, 245, 150, 25, squareString);
		/* 第六行 */
		SetText(50, 290, 260, 25, L"正方形四顶点高度值");
		/* 第七行 */
		SetTextRectangle(21, 335, 72, 25, _aString);
		SetTextRectangle(103, 335, 72, 25, _bString);
		SetTextRectangle(185, 335, 72, 25, _cString);
		SetTextRectangle(267, 335, 72, 25, _dString);
		/* 第八行 */
		SetButton(90, 400, 180, 60, L"生成");
		/* 第九行 */
		SetButton(90, 500, 180, 60, L"退出");
		/* 水印 */
		SetTextRectangle(990, 700, 80, 20, L"-ChenE1even-");

		EndBatchDraw();							/* 结束批量绘图 */

		if (MouseHit()) {						/* 检测鼠标点击 */
			MOUSEMSG msg = GetMouseMsg();		/* 获得鼠标参数 */
			if (msg.uMsg == WM_LBUTTONDOWN) {	/* 是否左键点击（有效点击） */
				/* 前四行 */
				if (msg.x > 190 && msg.x < 340) {
					/* 输入迭代次数 */
					if (msg.y > 110 && msg.y < 135) {
						printf("[INFO] 正在输入迭代次数\n");
						isOK = InputBox(nString, 10, L"\n\t\t请输入迭代次数（n) <1-9>", 0, 0, 0, 100, 0);			/* 弹出输入对话框输入 */
						if (isOK) {																				/* 判断是否输入 */
							while ((iterNumber = _wtoi(nString)) < 1 || iterNumber > 9) {						/* 存储转换后的输入，并检测输入合法性 */
								printf("\a[ERROR] 输入非法\n");
								InputBox(nString, 10, L"\t\t\t【非法输入】\n\t\t请重新输入迭代次（n) <1-9>", 0, 0, 0, 100);
							}
							SetTextRectangle(190, 110, 150, 25, nString);										/* 更新输入框文本显示 */
							printf("[INFO] 更新迭代次数：%d\n", iterNumber);
						}
						else 
							printf("[WARNING] 未更新迭代次数\n");
					}
					/* 输入缩放倍数 */
					if (msg.y > 155 && msg.y < 180) {
						printf("[INFO] 正在输入缩放\n");
						isOK = InputBox(bString, 10, L"\n\t\t请输入缩放因子（b) <1.00-4.00>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((scaleFactor = _wtof(bString)) < 1 || scaleFactor > 4) {
								printf("\a[ERROR] 输入非法\n");
								InputBox(bString, 10, L"\t\t\t【非法输入】\n\t\t请输入缩放因子（b) <1.00-4.00>", 0, 0, 0, 100);
							}
							SetTextRectangle(190, 155, 150, 25, bString);
							printf("[INFO] 更新缩放因子：%0.2lf\n", scaleFactor);
						}
						else
							printf("[WARNING] 未更新缩放因子\n");
					}
					/* 输入高度因子 */
					if (msg.y > 200 && msg.y < 225) {
						printf("[INFO] 正在输入高度因子\n");
						isOK = InputBox(hString, 10, L"\n\t\t请输入高度因子(h)<1-256>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((heightFactor = _wtof(hString)) < 1 || heightFactor > 256) {
								printf("\a[ERROR] 输入非法\n");
								InputBox(hString, 10, L"\t\t\t【非法输入】\n\t\t请输入高度因子(h)<1-256>", 0, 0, 0, 100);
							}
							SetTextRectangle(190, 200, 150, 25, hString);
							printf("[INFO] 更新高度因子：%0.0lf\n", heightFactor);
						}
						else
							printf("[WARNING] 未更新高度因子\n");
						
					}
					/* 输入正方形边长 */
					if (msg.y > 245 && msg.y < 270) {
						printf("[INFO] 正在输入正方形边长\n");
						isOK = InputBox(squareString, 10, L"\n\t\t请输入正方形变长<256-460>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((squareLength = _wtof(squareString)) < 256 || squareLength > 460) {
								printf("\a[ERROR] 输入非法\n");
								InputBox(squareString, 10, L"\t\t\t【非法输入】\n\t\t请输入正方形变长<256-460>", 0, 0, 0, 100);
							}
							SetTextRectangle(190, 245, 150, 25, squareString);
							printf("[INFO] 更新正方形边长：%0.0f\n", squareLength);
						}
						else
							printf("[WARNING] 未更新正方形边长\n");
					}
				}
				/* 四顶点高度值 */
				if (msg.y > 335 && msg.y < 360) {
					/* A顶点 */
					if (msg.x > 21 && msg.x < 93) {
						printf("[INFO] 正在输入第一个顶点的高度\n");
						isOK = InputBox(_aString, 10, L"\n\t\t请输入第一个顶点的高度<0-256>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((aHeight = _wtof(_aString)) < 0 || aHeight > 256) {
								printf("\a[ERROR] 输入非法\n");
								InputBox(_aString, 10, L"\t\t\t【非法输入】\n\t\t请输入第一个顶点高度<0-256>", 0, 0, 0, 100);
							}
							SetTextRectangle(21, 335, 72, 25, _aString);
							printf("[INFO] 更新第一个顶点的高度：%0.0f\n", aHeight);
						}
						else
							printf("[WARNING] 未更新第一个顶点的高度\n");
					}
					/* B顶点 */
					if (msg.x > 103 && msg.x < 175) {
						printf("[INFO] 正在输入第二个顶点的高度\n");
						isOK = InputBox(_bString, 10, L"\n\t\t请输入第二个顶点的高度<0-256>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((bHeight = _wtof(_bString)) < 0 || bHeight > 256) {
								printf("\a[ERROR] 输入非法\n");
								InputBox(_bString, 10, L"\t\t\t【非法输入】\n\t\t请输入第二个顶点高度<0-256>", 0, 0, 0, 100);
							}
							SetTextRectangle(103, 335, 72, 25, _bString);
							printf("[INFO] 更新第二个顶点的高度：%0.0f\n", bHeight);
						}
						else 
							printf("[WARNING] 未更新第二个顶点的高度\n");
					}
					/* C顶点 */
					if (msg.x > 185 && msg.x < 257) {
						printf("[INFO] 正在输入第三个顶点的高度\n");
						isOK = InputBox(_cString, 10, L"\n\t\t请输入第三个顶点的高度<0-256>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((cHeight = _wtof(_cString)) < 0 || cHeight > 256) {
								printf("\a[ERROR] 输入非法\n");
								InputBox(_cString, 10, L"\t\t\t【非法输入】\n\t\t请输入第三个顶点高度<0-256>", 0, 0, 0, 100);
							}
							SetTextRectangle(185, 335, 72, 25, _cString);
							printf("[INFO] 更新第三个顶点的高度：%0.0f\n", cHeight);
						}
						else
							printf("[WARNING] 未更新第三个顶点的高度\n");
					}
					/* D顶点 */
					if (msg.x > 267 && msg.x < 339) {
						printf("[INFO] 正在输入第四个顶点的高度\n");
						isOK = InputBox(_dString, 10, L"\n\t\t请输入第四个顶点的高度<0-256>", 0, 0, 0, 100, 0);
						if (isOK) {
							while ((dHeight = _wtof(_dString)) < 0 || dHeight > 256) {
								printf("\a[ERROR] 输入非法\n");
								InputBox(_dString, 10, L"\t\t\t【非法输入】\n\t\t请输入第四个顶点高度<0-256>", 0, 0, 0, 100);
							}
							SetTextRectangle(267, 335, 72, 25, _dString);
							printf("[INFO] 更新第四个顶点的高度：%0.0f\n", dHeight);
						}
						else
							printf("[WARNING] 未更新第四个顶点的高度\n");
					}
				}
				/* 生成模型 */
				if (msg.x > 90 && msg.x < 270 && msg.y > 400 && msg.y < 460)
				{
					/* 判断参数是否初始化 */
					if (iterNumber && scaleFactor && heightFactor && squareLength) {
						BeginBatchDraw();				/* 开始批量绘图 */
						cleardevice();					/* 清理上一个山脉模型 */

						double seedX = WINDOW_H - squareLength - 128;
						double seedY = WINDOW_H / 2 + squareLength / 4;
						_3DPointList mountainList;
						_3DPoint seedPoint[4] = {		/* 四个种子点 */
							{ seedX, seedY, aHeight },
							{ seedX + squareLength, seedY, bHeight },
							{ seedX, seedY + squareLength, cHeight },
							{ seedX + squareLength, seedY + squareLength, dHeight }
						};

						InitList(&mountainList);												/* 初始化链表 */
						printf("[INFO] 正在生成山脉.\n");
						InitMountain3D(&mountainList, seedPoint);								/* 初始化山脉 */
						printf("[INFO] 正在生成山脉..\n");
						IterMountain3D(&mountainList, heightFactor, scaleFactor, iterNumber);	/* 迭代山脉 */
						printf("[INFO] 正在生成山脉...\n");
						
						setlinecolor(MATCHA_GREEN);						/* 设置山脉颜色 */
						DrawMountain3D(&mountainList);					/* 绘制山脉 */
						
						printf("[INFO] 成功生成山脉\n");
						EmptyTheList(&mountainList);					/* 清空山脉释放内存 */
						EndBatchDraw();									/* 结束批量绘图 */
						
					} 
					else {							/* 参数未初始化 */
						printf("'\a'[ERROR] 有参数未初始化！\n");
						HWND hwnd = GetHWnd();		/* 获得句柄 */
						/* 弹窗 */
						MessageBox(hwnd, L"有参数未初始化！", L"错误", MB_OK);
					}
				}
				/* 退出软件 */
				if (msg.x > 90 && msg.x < 270 && msg.y > 500 && msg.y < 560)
				{
					closegraph();
					printf("[INFO] 退出软件\n");
					exit(0);
				}
			}
		}
	}

	_getch();
	closegraph();

	return 0;
}

/* 局部函数定义 */
static void InitWindow(int length, int height) {
	initgraph(length, height, EW_NOCLOSE) ;		/* 创建窗口没有关闭按钮 */
	setbkcolor(OFF_WHITE);
	cleardevice();
}