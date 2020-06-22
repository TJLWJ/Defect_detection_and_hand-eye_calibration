#pragma once
#include "stdafx.h"
#include "Doc.h"
#include <map>
#include <deque>
# include "myStruct.h"
# include "ParamUtil.h"

#include "../include/dmc1380.h"
#pragma comment(lib,"../lib/x64/Dmc1380.lib")


#define PULSE_TRIGER_CAMERA1_MIN 900 //��������,Triger�����һ
#define PULSE_TRIGER_CAMERA1_MAX 1200//��������
#define PULSE_CAMERA1_CAMERA2 6176//��������
#define PULSE_CAMERA2_GASS1 7861//��������
#define PULSE_GASS1_GASS2 3307//��������
#define PULSE_GASS2_GASS3 3588//��������



#define PULSE_TRIGER_CAMERA1 (PULSE_TRIGER_CAMERA1_MIN+PULSE_TRIGER_CAMERA1_MAX)*0.5
#define PULSE_TRIGER_GassingOne (PULSE_TRIGER_CAMERA1_MAX+PULSE_CAMERA1_CAMERA2+PULSE_CAMERA2_GASS1)
#define PULSE_TRIGER_GassingTwo (PULSE_TRIGER_GassingOne+PULSE_GASS1_GASS2)




//#define CAMERA1_NG_PULSE PULSE_CAMERA1_CAMERA2+PULSE_CAMERA2_GASS1
//#define CAMERA1_OK_PULSE CAMERA1_NG_PULSE+PULSE_GASS1_GASS2



class dmc1380Util
{
public:
	dmc1380Util();
	~dmc1380Util();
	void Move();
	//����ֹͣ
	void emergentStop();
	//ֹͣ
	void generalStop();

	//λ������
	void setCurrentPositionZero();


	//��������Ŀ���� 
	// 1��2�Ŵ����
	// 2��1�Ŵ�����
	// 3����������Դ
	// 4�����̵�Դ
	// 5��ת�̵�Դ
	void enpowerEngine(bool enpower);//ת�̵��ʹ��
	void enableGassing(bool enpower);//����ʹ��
	void gassing_no1(bool gassing);//1�Ŵ���
	void gassing_no2(bool gassing);//2�Ŵ���
	void enableVibrationPlate(bool enable);//����
	bool isItemsComing();//�Ƿ������Ϲ���

    int getCurrentPulse();//���ת�̵�������

   //�˶�����
	int nStart; //��ʼ�ٶ�
	int nMSpeed;//max speed
	double nTAcc;//acc time
	int nPulse;//��������
	int nPos;//����λ��


	bool moveMode_T; //T���˶�
	int  moveModeFixPosFixDisSpeed; //�˶�ģʽ 0 ���ض��㣬1 ���� 2 �����˶�
	
	void dealTrigerDeque();
	void dealGass1Deque();
	void dealGass2Deque();

	void clearDeques();
	bool runThread;

	void resetCount();

public:
	deque<InfoUnit> Camera1Deque;
	deque<InfoUnit> Gass1Deque;//ng
	deque<InfoUnit> Gass2Deque;//ok
	deque<int> resultQue;//ok

public:
	HWND hWnd;//��ʾ��ʼ���忨ʧ���õ�
	int BoardInit();

	


	void Stop(bool isEmerge);


	int	 m_nAxis; //�˶���ѡ�� 0-3
	int boardsNum;
	bool successInit;//��ʼ���ɹ�

	CString getDequesSize();

	int lasePulseTriger;

	

	

	void setResult(InfoUnit & info, bool ng, bool cameraOneDown);

public:
	int m_count_camera;
	int m_count_trigger;
	int m_count_ok;
	int m_count_ng;
	int m_count_gassing1;
	int m_count_gassing2;
	
};

