#pragma once
#include "Draw.h"

/*
	���ļ���
		1. ������Ϸ�������߼�
*/

enum ScenceDlg          //��Ϸ�����������ĸ����棩
{
	GameDlg=1,          //��Ϸ���н���
	EditDlg,            //�༭��ͼ����
	HelpDlg,            //��Ϸ��������
	ExitDlg             //�˳���Ϸ����
};

int init(char * name, int width, int high);

int run();