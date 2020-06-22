#include "stdafx.h"
#include "CameraUtil.h"

int                     g_hCamera = -1;     //�豸���
unsigned char           * g_pRawBuffer = NULL;     //raw����
unsigned char           * g_pRgbBuffer = NULL;     //��������ݻ�����
tSdkFrameHead           g_tFrameHead;       //ͼ��֡ͷ��Ϣ
tSdkCameraCapbility     g_tCapability;      //�豸������Ϣ

int                     g_SaveParameter_num = 0;    //���������
int                     g_SaveImage_type = 0;         //����ͼ���ʽ

Width_Height            g_W_H_INFO;         //��ʾ���嵽��С��ͼ���С
BYTE                    *g_readBuf = NULL;    //������ʾ������
int                     g_read_fps = 0;       //ͳ�ƶ�ȡ֡��
int                     g_disply_fps = 0;     //ͳ����ʾ֡��




CameraUtil::CameraUtil()
{
	showAmendedPic = true;
	amendMode = 0;
}


CameraUtil::~CameraUtil()
{
}

#if 0
int CameraUtil::init_SDK()
{

	int                     iCameraCounts = 4;
	int                     iStatus = -1;
	tSdkCameraDevInfo       tCameraEnumList[4];

	//sdk��ʼ��  0 English 1����
	CameraSdkInit(1);

	//ö���豸���������豸�б�
	CameraEnumerateDevice(tCameraEnumList, &iCameraCounts);

	//û�������豸
	if (iCameraCounts == 0) {
		return -1;
	}

	//�����ʼ������ʼ���ɹ��󣬲��ܵ����κ����������صĲ����ӿ�
	iStatus = CameraInit(&tCameraEnumList[0], -1, -1, &g_hCamera);

	//��ʼ��ʧ��
	if (iStatus != CAMERA_STATUS_SUCCESS) {
		return -1;
	}
	//�����������������ṹ�塣�ýṹ���а�������������õĸ��ֲ����ķ�Χ��Ϣ����������غ����Ĳ���
	CameraGetCapability(g_hCamera, &g_tCapability);

	g_pRgbBuffer = (unsigned char*)malloc(g_tCapability.sResolutionRange.iHeightMax*g_tCapability.sResolutionRange.iWidthMax * 3);
	g_readBuf = (unsigned char*)malloc(g_tCapability.sResolutionRange.iHeightMax*g_tCapability.sResolutionRange.iWidthMax * 3);

	/*��SDK���빤��ģʽ����ʼ��������������͵�ͼ��
	���ݡ������ǰ����Ǵ���ģʽ������Ҫ���յ�
	����֡�Ժ�Ż����ͼ��    */
	CameraPlay(g_hCamera);



	/*
		����ͼ����������ʽ����ɫ�ڰ׶�֧��RGB24λ
	*/
	if (g_tCapability.sIspCapacity.bMonoSensor) {
		CameraSetIspOutFormat(g_hCamera, CAMERA_MEDIA_TYPE_MONO8);
	}
	else {
		CameraSetIspOutFormat(g_hCamera, CAMERA_MEDIA_TYPE_RGB8);
	}
	return 0;
}




//��ƽ�ⰴť����
void CameraUtil::AWB_once()
{
	int RPos, GPos, BPos;

	CameraSetOnceWB(g_hCamera);

	CameraGetGain(g_hCamera, &RPos, &GPos, &BPos);




}

#endif