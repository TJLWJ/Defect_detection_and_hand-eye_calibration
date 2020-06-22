#pragma once
#include "MotionControlCardUtil.h"
#include "CameraUtil.h"
#include "MyRealButton.h"
#include "HalconUtil.h"
#include "MfcUtil.h"
# include "myStruct.h"
#include "HalconMotionCardUnion.h"
#include <vector>

#define _ResizeWindow_Fixed

#define WM_UPDATEDATA 123

#define FIXED_MAINWINDOW_HIGH 820  //��ʾ�����
#define FIXED_MAINWINDOW_WIDE 1400  //��

#define Z_AXIS_DOWN_PULSE -24719 //z���½���������λ��
#define Z_AXIS_UP_PULSE 0 //z��̧���������λ��


#define EPSON_IP "192.168.0.12"
#define EPSON_PORT "3000"


//���ڶ�����ж�״̬����

class ParamUtil
{
public:
	ParamUtil();
	~ParamUtil();

	string getPreviousFilePath();

	HTuple getNewFilePath_HTuple();

	HTuple getPreviousFilePath_HTuple();

	HTuple getCalibrationFilePath_HTuple();

	HTuple getTargetFilePath_HTuple();

	HTuple getFilePath_SysErr_Write();

	HTuple getFilePath_NG_Write();

	CString getCStringFilePath_NG_Read(int num);

	CString getCStringFilePath_OK_Read(int num);

	HTuple getFilePath_NG_Read();

	HTuple getFilePath_OK_Write();

	HTuple getFilePath_NG_Blank_Write();

	HTuple getFilePath_OK_Blank_Write();

	HTuple getFilePath_OK_Read();

	HTuple getCalibration_Test_HTuple(int id);

	string getNewFilePath();

	//����Я����ַ��������
	/*MotionControlCardUtil *motionCard;
	Doc *doc;
	CameraUtil *cameraUtil;
	HalconUtil *halconUtil;
	int mfcUtilAddress;*/
	int showModeSynWithMainWin;

	int cameraMode;//1�ڽ� 2 ��Ŀһ 3 ��Ŀ�� 4��Ŀ�� Halcon  5 ��Ŀ�� SDK
	int cameraModeSecond;//1��Ŀ�� 2 ��Ŀ�� 3 �����

	bool completeCalibration;//��ɱ궨

	bool rotate180; //��һ̨�����ת
	bool rotate180Second;//��2̨�����ת
	

	int minGray;
	int maxGray;

	int selectShapMaxArea;
	int selectShapMinArea;

	int fileNameCount;
	int fileNameCount_NG;
	int fileNameCount_OK;
	int fileNameCount_SysErr;

	//int upPulse;//��Ŀ�Ĺ̶��߶�
	//int downPulse;//��Ŀ�Ĺ̶��߶�
	
	bool showGrayImg;

	bool isTakeCalibrationPic;
	bool generateRectengle;
	bool generateCircle;
	bool gotTemplate;
	bool gotROI;
	bool picTarget;

	std::string minContrast;//��С�Աȶ�
	double minScore;//ƥ���
	int numMatches;//��������
	int areaPintsMin;//XLD�������������
	int areaPintsMax;//XLD�������������
	double circularityMin;//XLD������Բ��
	double circularityMax;//XLD������Բ��

	//mlp
	int mlp_minGray;
	int mlp_maxGray;
	bool mlp_useDefaultSamplePics;
	bool mlp_takeSample1;
	bool mlp_takeSample2;
	bool mlp_takeSample3;
	bool mlp_takeSample4;
	bool mlp_startTrain;
	bool mlp_completeTrain;
	bool mlp_startDetect;
	bool mlp_gotSample1;
	bool mlp_gotSample2;
	bool mlp_gotSample3;
	bool mlp_gotSample4;
	double mlp_openingCircleRadius;

	int dlg3ThreadMode;//1 blob 2 multi template 3xld 4����
	bool locked;//���߳���

	bool openIOcheck;


	//case 4
	bool caseFourCalibration_CameraOne;
	bool caseFourCalibration_CameraTwo;

	//case 5
	bool conveyorTakeNine;
	bool conveyorTakeNineSuccess;


	//case 6
	int caseSixMode;//1 mlp 2 Ƶ��

	bool isClearQue;

	HObject tmpImg;


	bool GoOriginal;

	bool isGrabbing;
private:


};

