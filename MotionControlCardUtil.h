#pragma once
#include "stdafx.h"
#include "Doc.h"
#include <map>
# include "myStruct.h"

#include "../include/DMC2410.h"
#pragma comment(lib,"../lib/x64/DMC2410.lib")

#define _MotionControlCardUtil_HighSpeed 3200
#define _MotionControlCardUtil_LowSpeed 1600

#define _UP_PULSE_STD  60010              
#define _DOWN_PULSE_STD  3730 

#define _X_ZERO_POINT 21243       //X ��ԭ�� 9�۱궨
#define _Y_ZERO_POINT 39991       //Y ��ԭ�� 9�۱궨

#define _Z_ZERO_POINT 60010       //Z ��ԭ�� 9�۱궨
#define _Z_INHALE_POINT -6392       //Z ��������


#define _U_PULSE_START 63895 
#define _U_PULSE_END 70525
#define _U_ZERO_POINT ((_U_PULSE_START+_U_PULSE_END)/2)  //U ��ԭ��


using std::map;
class MotionControlCardUtil
{
public:
	MotionControlCardUtil();
	~MotionControlCardUtil();
    //λ������
	void setCurrentPositionZero();

	//����ָ��λ��
	void moveToPoint(CPoint cp);
	void moveToPoint(int axis, int pulse);


	//�ƶ�->����->����->̧��->�ƶ�->����->����
	void grabToLocation(CPoint cp1, CPoint cp2, int angle);
  
	void inHole();//����
	void gassing();//����

	//�����˶�
	void moveContinue(char axis,bool positiveDirection);
	void stopContinueMove(char axis);

	//��ԭ��
	void moveToBasePoint(int axis);//not work��
	void moveToBaseCPoint();//�������
	void moveToBaseCPointAll();//�������
	void moveToBasePointCS();//�ص���ԭ�㣿
	void moveToBaesZ();//z�����
	void moveToInHolePoint();//z�ᵽ����λ��


	//����ֹͣ
	void emergentStop();

	//�趨���㷽ʽ
	void setHomeMode_Speed(bool highSpeed);
	void setHomeMode_Side(bool positive);
	//check ���㷽ʽ
	bool isHomeMode_HighSpeed();
	bool isHomeMode_PositiveSide();

	//�趨�˶���ʽ
	void setMovingMode_S();//����
	void setMovingMode_T();//���� ��������ٶ�=��ʼ�ٶȣ��������ٶ�=2*��ʼ�ٶ�
	
	//�趨�˶��ٶ�
	void setHighSpeed();
	void setLowSpeed();



	//ȡ�õ�ǰλ��״̬
	CPoint getCurrentPosition();
	CPoint getBasePosition();
	int getCurrentPulse(char aixs);
	bool isHighSpeedMode();
	bool isMoveMode_S();
	bool isStop(char axis);
	bool isAllStop();
	bool isSymmetry();
	CString getStatus(bool allAxis,char axis);
    double readCurrentSpeed(int m_nAxis);
    double readCurrentSpeedMax();
	int readSpeedStart();
	int readSpeedMax();
	double readAccl();//����ʱ��


	HWND hWnd;//��ʾ��ʼ���忨ʧ���õ�

	//CPoint *nextTarget;

	int angleDegreeToPulse(double degree);//�Ƕ�ת������


private:

	void up(bool zeroUAxis);
	void down(bool inhole, bool gassing, bool inhole2, bool gassing2);


	void Move();//���˻��㣬�����˶���Ҫ���������������ֱ�ӵ��ó����ṩ�Ľӿ�
	void OnCheckSymmetry(bool isSymmetry);
	void moveToAxisPoint(int axis, int pulse);//�����˶�

	//ֹͣ��ͨ�ýӿ�
	void Stop(bool isEmerge, bool oneAxis, int axis);



	int BoardInit();
	void OnDestroy();
	
	int boardsNum;
	BOOL	m_bLogic;//�߼����� ��/��
	BOOL	m_bSymmetry;//�Գ�

	double	m_fAccel;//����ʱ��
	double	m_fDecel;//����ʱ��
    double	m_nTSacc;//S��ʱ��
	
	long	m_nPulse;//�ƶ��ĵ�λ����
	
	
	long	m_nStopVel;// ֹͣ�ٶ�
	long	m_nSpeedmax;//�����ٶ�
	long	m_nSpeedst;//��ʼ�ٶ�

	int		m_nActionst;// 0 �㶯, 1 �����˶�

	int		m_nCmove;//����

	int	 m_nAxis; //�˶���ѡ�� 0-3

	
	int		m_nHome;//���㷽ʽ
	int		m_nEzno;//���㷽ʽ
	bool m_HomeMode_HighSpeed;//�������
	bool m_HomeMode_Positive;//���� ����

	bool moveMode_S; //S���˶���ƽ�����٣�
	bool highSpeedMode;//�����˶�

	bool successInit;//��ʼ���ɹ�
	int direction;//�˶���������Ϊ1 ����Ϊ0

	
};

