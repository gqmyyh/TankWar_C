#pragma once
#include "Data.h"
#include <windows.h>

/*
	此文件：
		1. 声明图像绘制的函数
*/
//键盘检测
#define KEY_DOWN(key) GetAsyncKeyState(key)&0x8000  ?1:0	  

 //获取标准输出句柄
extern HANDLE g_hStdOut ;   

// 行数，列数，要输出的字符串，颜色
void writeChar(int row, int col, const char* pszChar, WORD wArr);

void cls();


int DrawMap(int map[MAP_HIGH][MAP_WIDTH]);
int ClsTank(TANK tank);
int DrawTank(TANK tank);
int ClsMissile(MISSILE missile);
int DrawMissile(MISSILE missile);

