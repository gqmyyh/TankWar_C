#pragma once
#include "Draw.h"

/*
	此文件：
		1. 声明游戏的主体逻辑
*/

enum ScenceDlg          //游戏场景（处于哪个界面）
{
	GameDlg=1,          //游戏运行界面
	EditDlg,            //编辑地图界面
	HelpDlg,            //游戏帮助界面
	ExitDlg             //退出游戏界面
};

int init(char * name, int width, int high);

int run();