#pragma once
/*
	���ļ���
		1. ������������
		2. ����ȫ�ֱ���
*/

#pragma region ����������ɫ����

// ������ʾ���
#define REVERSE    COMMON_LVB_REVERSE_VIDEO	 // ��ɫ
#define UNDER_SCORE COMMON_LVB_UNDERSCORE    // �»���

// ����ǰ��ɫ
#define F_BLUE     FOREGROUND_BLUE      // ����
#define F_H_BLUE   0x0001|0x0008        // ����
#define F_GREEN    0x0002               // ����
#define F_H_GREEN  0x0002|0x0008        // ����
#define F_RED      0x0004               // ���
#define F_H_RED    0x0004|0x0008        // ����
#define F_YELLOW   0x0002|0x0004        // ���
#define F_H_YELLOW 0x0002|0x0004|0x0008 // ����
#define F_PURPLE   0x0001|0x0004        // ����
#define F_H_PURPLE 0x0001|0x0004|0x0008 // ����
#define F_CYAN     0x0002|0x0004        // ����
#define F_H_CYAN   0x0002|0x0004|0x0008 // ����
#define F_WHITE    0x0004|0x0002|0x0001
#define F_H_WHITE  0x0004|0x0002|0x0001|0x0008

// ���ֱ���ɫ
#define B_BLUE     BACKGROUND_BLUE      // ����
#define B_H_BLUE   0x0010|0x0080        // ����
#define B_GREEN    0x0020               // ����
#define B_H_GREEN  0x0020|0x0080        // ����
#define B_RED      0x0040               // ���
#define B_H_RED    0x0040|0x0080        // ����
#define B_YELLOW   0x0020|0x0040        // ���
#define B_H_YELLOW 0x0020|0x0040|0x0080 // ����
#define B_PURPLE   0x0010|0x0040        // ����
#define B_H_PURPLE 0x0010|0x0040|0x0080 // ����
#define B_CYAN     0x0020|0x0040        // ����
#define B_H_CYAN   0x0020|0x0040|0x0080 // ����
#define B_WHITE    0x0010|0x0020|0x0040
#define B_H_WHITE  0x0010|0x0020|0x0040|0x0080

#pragma endregion

#pragma region ����ͼ��

#define WALL__      0x00  // "  " �յ��������ƻ���  ��ͨ����				
#define WALL_A      0x01  // "��" ��ǽ��  ���ƻ�������ͨ����		
#define WALL_B      0x02  // "�d" ��ǽ��  ���ƻ�, ����ͨ������ǽ���ƻ���̬��
#define WALL_C      0x03  // "��" ��ǽ (�����ƻ�, ����ͨ��)
#define WALL_D      0x04  // "��" �����������ƻ�,   �ӵ���ͨ����̹�˲���ͨ����
#define WALL_E      0x05  // "��" ���֣������ƻ���  ��ͨ������������	
#define WALL_G      0x06  // "��" ���ӣ������ƻ���  ��ʰȡ�������ԣ�
#define WALL_H      0x07  // "��" ���أ�  ���ƻ�������ͨ��)

#define TANK_A      0x00  //  "  "
#define TANK_B      0x01  //  "��"
#define TANK_C      0x02  //  "��"
#define TANK_D      0x03  //  "��"
#define TANK_E      0x04  //  "��"

#define BLOOD_0     0x0   //  "  "
#define BLOOD_1     0x1	  //  "��"
#define BLOOD_2     0x2   //  "��"
#define BLOOD_3     0x3   //  "��"
#define BLOOD_4     0x4   //  "��"
#define BLOOD_5     0x5   //  "��"
#define BLOOD_6     0x6   //  "��"
#define BLOOD_7     0x7	  //  "��"
#define BLOOD_8     0x8   //  "��"
#define BLOOD_9     0x9   //  "��"

#define MISSIL_0    0x0	  //  "  "
#define MISSIL_1    0x1	  //  "��"
#define MISSIL_2    0x2   //  "��"
#define MISSIL_3    0x3   //  "��"
#define MISSIL_4    0x4   //  "��"
#define MISSIL_5    0x5   //  "��"
#define MISSIL_6    0x6   //  "��"
#define MISSIL_7    0x7	  //  "��"
#define MISSIL_8    0x8   //  "��"
#define MISSIL_9    0x9   //  "��"
#pragma endregion

#pragma region ȫ�ֲ�������

//���ڴ�С
#define WINDOWS_WIDTH 50
#define WINDOWS_HIGH  40

//��ͼ��С
#define MAP_WIDTH 40					//��ͼ��
#define MAP_HIGH  40					//��ͼ��

//Ĭ�ϴ��ڱ���
#define AUTO_CONSOLE_TITLE "TankWar_C"

//����
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

#pragma endregion

//���������Ϣ
typedef struct _PLAYERINFO
{
	char name[20];
	int  score;
	char note[20];
}PLAYERINFO,*PPLAYERINFO;
//����̹�˽ṹ��
typedef struct _TANK 
{
	int tankID;             //̹�˱��
	int posX;               //���ڵ�ͼx���꣨ˮƽ�ᣩ
	int posY;               //���ڵ�ͼx���꣨��ֱ�ᣩ
	int orientation;        //����
	int blood;              //Ѫ��
	int level;              //�����ȼ�
	int style;              //̹����ʽ
	bool isValid;           //�Ƿ���Ч
	int color;
}TANK,*PTANK;
//�����ӵ��ṹ��
typedef struct _MISSILE
{
	int missileID;          //�������
	int posX;				//���ڵ�ͼx���꣨ˮƽ�ᣩ
	int posY;				//���ڵ�ͼx���꣨��ֱ�ᣩ
	int orientation;		//����
	int level;				//Ѫ��
	int style;              //�ӵ���ʽ
	bool isValid;           //�Ƿ���Ч

	int tankID;				//̹�˱�ţ���¼��ŵ�����˭����ģ�

}MISSILE, *PMISSILE;

//�������ʽ����ɫ ǽ��ͼƬ�Լ���ɫ����
extern char * wall_pic[];             //ǽ���ͼƬ��
extern int  wall_color[];             //ǽ�����ɫ��
extern int tank_style[][4][3][3];     //̹�˵���ʽ��(����)(ÿ����ʽ��̹�������������ĸ����ͣ�ÿ��������Ҫ9��������)
extern char * tank_pic[];             //̹�˵�ͼƬ��
extern char * blood_pic[];            //Ѫ����ͼƬ��
extern char * missile_pic[];          //�ӵ���ͼƬ��

//���������Ϣ
extern PLAYERINFO g_player_Info[2];
//�����Ҿ�̹������
extern TANK g_Player_Tanks[2];
//�����о�̹������
extern TANK g_NPC_Tanks[100];
//�����ӵ�����
extern MISSILE g_Missile[300];
//������ͼ����
extern int g_sysMap00[MAP_HIGH][MAP_WIDTH]; //��ͼ����������Դ�λ�νṹ��
extern int g_sysMap01[MAP_HIGH][MAP_WIDTH];