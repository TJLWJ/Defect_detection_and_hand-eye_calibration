#pragma once
#include <map>
#include <atltypes.h>
# include "HalconCpp.h"
# include "HDevThread.h"
#include <string>
# include "Doc.h"
#include <list>

//mlp


using std::list;
using std::map;
using std::string;
using std::string;
#define _MLP_DEFAULT_EXAMPLE_FILE_PATH "D:/tmp/mlp/example/defaultExample"
#define _MLP_NEW_EXAMPLE_FILE_PATH "D:/tmp/mlp/example/new"
#define _MLP_GMC_FILE_PATH "D:/tmp/mlp/example/detection.gmc"
#define _MLP_GMC_FILE_PATH_READONLY "D:/tmp/mlp/example/detectionReadonly.gmc"

#define pi 3.1415926535898
#define Leishine360DegreePuluse 10000
using namespace HalconCpp;

class HalconUtil 
{
public:
	HalconUtil();
	~HalconUtil();
	void resetStatus();
	

	HObject calibrationImage;
	HObject calibrationImage_projectFour_CameraOne;
	HObject calibrationImage_projectFour_CameraTwo;


	int takePointsNum;//ȡ�ö����� project 1
	int takePointsNum_Project4_C1;//ȡ�ö����� project 4
	int takePointsNum_Project4_C2;//ȡ�ö����� project 4
	bool doTakeNinePointsCenter(HTuple hv_Row, HTuple hv_Column, Doc * doc);
	bool doTakeNinePointsCenter_Project4(HTuple hv_Row, HTuple hv_Column, Doc * doc,int CameraNum);
							
	//��������//����
	//bool mVectorToHomMat2d(map<int,CPoint> map1,map<int,CPoint> map2);
	bool mVectorToHomMat2d(HTuple * hv_HomMat2D, map<int, CPoint> map1, map<int, CPoint> map2);

	
	
	HTuple savedHomMat2D;//�궨����ݴ��ļ�
	//HTuple savedHomMat2DInvert;//�궨����ݴ��ļ�
	bool isHomMat2D_Valid;//׼���ÿ���ת��

	//project 4
	HTuple savedHomMat2D_P4C1;//�궨����ݴ��ļ�
	HTuple savedHomMat2D_P4C2;//�궨����ݴ��ļ�
	
	static bool getImageFromFilePath(HObject &ho_Image, string path);
	
	 
	//����
	//HTuple hv_HomMat2D;
	//HTuple hv_HomMat2DInvert;

	//��λ����
	//HTuple  hv_Area, hv_Row, hv_Column;


	//Basic 
	void createHomMat2d(HTuple *hv_HomMat2D,double pixX[], double pixY[], double worldX[], double worldY[]);//��������
	void createInvertHomMat2d(HTuple *hv_HomMat2D, HTuple * hv_HomMat2DInvert);//����������
	bool writeHomMat2D(HTuple *hv_HomMat2D,string filePath);//�������
	bool readHomMat2D(HTuple *hv_HomMat2D, string filePath);
	void worldToPix_motionCardAtBase(HTuple * hv_HomMat2D, double& worldX, double& worldY, double& pixX, double& pixY);
	void pixToWorld(HTuple rowY, HTuple columnX, CPoint & worldCP,CPoint &currentPosition,CPoint &basePosition);
	
	
	




	//�������Լ��ڲ�ʹ��
	void pixToWorld_motionCardAtBase(HTuple *hv_HomMat2D, double &pixX, double &pixY, double& worldX, double& worldY);
	     


	//HTupleת��
	static HString HTupleToHString(HTuple htuple);
	static string HTupleToString(HTuple htuple);
	static double HTupleToDouble(HTuple htuple);
	static int HTupleToInt(HTuple htuple);

	static void HTupleToList(HTuple htuple, list<double> *doubleList);

	

	static void stringToHTuple(HTuple& htuple, string str);
	//static void CStringToHTuple(HTuple & htuple, CString str);
	static void doubleToHTuple(HTuple& htuple, double value);
	static void intToHTuple(HTuple& htuple, int value);
    static double radToDegree(double rad);
    static int radToPulse(double rad);

	HTuple getMlpExampleFilePath(int i);
	//backup
//	bool blobForAreaCenter(string filePath);//���վ������


	HTuple  hv_MLPHandle;//mlp


	HTuple hv_RowTmp;
	HTuple hv_ColumnTmp;


//https://blog.csdn.net/weixin_42112458/article/details/80542130



private:
	//����public�ˣ��������pixToWorld
	void pixToWorld_motionCardAtBase(HTuple rowY, HTuple columnX, CPoint & worldCP);
};
