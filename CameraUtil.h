#pragma once

#include "../include/mindversion/CameraApi.h"

class CameraUtil
	//Mvs
{
public:
	CameraUtil();
	~CameraUtil();

	bool showAmendedPic;
	int amendMode;//0:blob 1:template 2:xld

#if 0

private:
	int init_SDK();

	
	
	//����ģʽ
	void set_trigger_hardware();//Ӳ����
	void set_trigger_software();//����
	void set_trigger_collect();//�����ɼ�
	void trigger_once();//�������һ��

	//�ع�����  


	//����Ŀ��

	//��Ƶ��

	//����

	//�ع�ʱ��

	//ISPͼ����


	//������
	

	//���ӳ��任

	//ISP��ɫ����



	//һ����ƽ��
    void AWB_once();

	//ץ������




	
	bool   exposure_time_lineedit_status;

#endif
};


typedef struct _WIDTH_HEIGHT {
	int     display_width;
	int     display_height;
	int     xOffsetFOV;
	int     yOffsetFOV;
	int     sensor_width;
	int     sensor_height;
	int     buffer_size;
}Width_Height;

