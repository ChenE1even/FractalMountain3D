#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <stdbool.h>

/* 颜色定义 */
#define OFF_WHITE		0xF4F8FA		/* 米白 */
#define MATCHA_GREEN	0x56AF8B		/* 抹茶绿 */

/* 函数原型 */

/* 函数操作：改变当前窗口标题						*/
/* 前提条件：text_指向一个宽字符串					*/
/* 后置条件：改变当前窗口标题为text_					*/
void ChangeWindowText(const wchar_t* text_);

/* 函数操作：在窗口放置一个文本(米白)				*/
/* 前提条件：x, y指向放置位置						*/
/*			width，height指向文本显示的大小		*/
/*			text_指向要显示的宽字符串				*/
/* 后置条件：在设定的位置放置一个文本				*/
void SetText(int x, int y, int width, int height, const wchar_t* text_);

/* 函数操作：在窗口放置一个文本框(白底，绿字)			*/
/* 前提条件：x, y指向放置位置						*/
/*			width，height指向文本框的大小			*/
/*			text_指向要显示的宽字符串				*/
/* 后置条件：在设定的位置放置一个文本框，并显示文本		*/
void SetTextRectangle(int x, int y, int width, int height,const wchar_t* text_);

/* 函数操作：在窗口放置一个按钮(白底，绿字)			*/
/* 前提条件：x, y指向放置位置						*/
/*			width，height指向按钮的大小			*/
/*			text_指向要显示的宽字符串				*/
/* 后置条件：在设定的位置放置一个按钮，并显示文本		*/
void SetButton(int x, int y, int width, int height, const wchar_t* text_);

#endif