#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <stdbool.h>

/* ��ɫ���� */
#define OFF_WHITE		0xF4F8FA		/* �װ� */
#define MATCHA_GREEN	0x56AF8B		/* Ĩ���� */

/* ����ԭ�� */

/* �����������ı䵱ǰ���ڱ���						*/
/* ǰ��������text_ָ��һ�����ַ���					*/
/* �����������ı䵱ǰ���ڱ���Ϊtext_					*/
void ChangeWindowText(const wchar_t* text_);

/* �����������ڴ��ڷ���һ���ı�(�װ�)				*/
/* ǰ��������x, yָ�����λ��						*/
/*			width��heightָ���ı���ʾ�Ĵ�С		*/
/*			text_ָ��Ҫ��ʾ�Ŀ��ַ���				*/
/* �������������趨��λ�÷���һ���ı�				*/
void SetText(int x, int y, int width, int height, const wchar_t* text_);

/* �����������ڴ��ڷ���һ���ı���(�׵ף�����)			*/
/* ǰ��������x, yָ�����λ��						*/
/*			width��heightָ���ı���Ĵ�С			*/
/*			text_ָ��Ҫ��ʾ�Ŀ��ַ���				*/
/* �������������趨��λ�÷���һ���ı��򣬲���ʾ�ı�		*/
void SetTextRectangle(int x, int y, int width, int height,const wchar_t* text_);

/* �����������ڴ��ڷ���һ����ť(�׵ף�����)			*/
/* ǰ��������x, yָ�����λ��						*/
/*			width��heightָ��ť�Ĵ�С			*/
/*			text_ָ��Ҫ��ʾ�Ŀ��ַ���				*/
/* �������������趨��λ�÷���һ����ť������ʾ�ı�		*/
void SetButton(int x, int y, int width, int height, const wchar_t* text_);

#endif