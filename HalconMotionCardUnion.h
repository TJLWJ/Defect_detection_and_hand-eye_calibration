#pragma once
#include "MotionControlCardUtil.h"
#include "HalconUtil.h"
#include "Doc.h"
#include "mystruct.h"
#include <vector>

using namespace HalconCpp;




class HalconMotionCardUnion
{
public:
	HalconMotionCardUnion();
	~HalconMotionCardUnion();

	//step 1 ȡ��ץȡ����������״
	void step_1_resetTargetData();
	bool step_3_addTargetDataWorld(CPoint cp, int mode, double radian);
	//bool step_3_addTargetDataWorld(double row_Y, double column_X, int mode, double radian);
	bool step_2_status_startGotFromData;//��ʼȡ��Ŀ��������
	//bool step_3_addTargetData(HTuple row,HTuple column,int mode,double angle);
	bool step_4_status_endGotFromData;//ȡ��Ŀ�������
	//step 2 ȡ��Ŀ��λ��and ִ��
	void step_5_doAction(Doc &doc);

	//��λ
	bool startCollectContourPoint;
	bool CompleteCollectContourPoint;
	void cleanConTourList();
	void initContourListMap(int num);
	void addContourList(int num, CPoint cp);
	void getContourList(int num, vector<CPoint> &list);
	int contourListSize(int num);

	int contourMapSize();
private:
	
	
	vector<CPoint> fromCPoints;
	vector<int> shapesVector; //0 ��ʾԲ�Σ�1��ʾ����,2��ʾ������
	vector<double> radianVector; //radian
	vector<HalconPointDataInt> pointDataVector; //360��
	
	
	vector<CPoint> toCPoints;
	int getAvailableWarehouse(int mode);
	CPoint takeAndUpdateWareHouse(int warehoseNo, Doc &doc);
	bool addToPoint(Doc &doc);
	void assembleHalconPointData();

	


	int radianToPulse(double radian);;


	bool endMoving;//����˶�


	map<int, bool> warehoseStatus;//11-14 Circle 21-24 ����

    MotionControlCardUtil motionCard;

	vector<CPoint> contourList;
	map<int, vector<CPoint>> contourListMap;
};

