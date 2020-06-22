#pragma once

#include <map>
#include <atltypes.h>
# include "HalconCpp.h"
# include "HDevThread.h"
#include <string>
# include "Doc.h"
#include <list>
# include "HalconUtil.h"
# include <vector>

using std::list;
using std::array;
using std::map;
using std::string;

using namespace HalconCpp;

class HalconTemplateUtil
{
public:
	HalconTemplateUtil();
	~HalconTemplateUtil();


	void setTemplate(HObject &imageROI);
	void setSearchImage(HObject &image);
	
	void setParam_createTemplate(bool fromPicture,string path);
	void setParam_findTarget(bool fromPicture, string path);
	void createTemplate();


	void findTarget();
    void showXld(vector<HObject>* xlds);





public:
	//�����Ǵ���ģ����Ҫ�õ�������
	HObject ho_Template;//ģ��ͼƬ

	HObject ho_Model;
	HTuple hv_ModelID;
	HTuple hv_AngleStart_create,hv_AngleExtent_create,hv_AngleStep_create;//�Ƕ�
	HTuple hv_Optimization;//�Ż�
	HTuple hv_Metric;
	HTuple hv_NumLevels;//���

	HTuple hv_Contrast, hv_MinContrast;//�Աȶ�
	HTuple hv_ScaleMin,hv_ScaleMax,hv_ScaleStep;//����
	HTuple hv_Level;

	//�����ǲ��Ҷ�ʱ����Ҫ�õ�������
	HObject ho_SearchImage;//ͼƬ
	HTuple hv_AngleStart_find,hv_AngleExtent_find; //�Ƕ�
	HTuple hv_MinScore;
	HTuple hv_NumMatches;
	HTuple hv_MaxOverlap;
	HTuple hv_SubPixel;
	HTuple hv_NumLevels_find;
	HTuple hv_Greediness;

	//�����ǲ��ҽ��
	HTuple out_hv_Row, out_hv_Column, out_hv_Angle, out_hv_Scale, out_hv_Score;

	//��ʾxld
	HObject ho_ModelTrans;
	HTuple hv_HomMat2DIdentity, hv_HomMat2DTranslate, hv_HomMat2DRotate, hv_HomMat2DScale;
	HObject ho_UnionContours;
};

