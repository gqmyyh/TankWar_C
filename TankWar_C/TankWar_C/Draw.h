#pragma once
#include "Data.h"
#include <windows.h>

/*
	���ļ���
		1. ����ͼ����Ƶĺ���
*/
//���̼��
#define KEY_DOWN(key) GetAsyncKeyState(key)&0x8000  ?1:0	  

 //��ȡ��׼������
extern HANDLE g_hStdOut ;   

// ������������Ҫ������ַ�������ɫ
void writeChar(int row, int col, const char* pszChar, WORD wArr);

void cls();


int DrawMap(int map[MAP_HIGH][MAP_WIDTH]);
int ClsTank(TANK tank);
int DrawTank(TANK tank);
int ClsMissile(MISSILE missile);
int DrawMissile(MISSILE missile);

