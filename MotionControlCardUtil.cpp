#include "stdafx.h"
#include "MotionControlCardUtil.h"


MotionControlCardUtil::MotionControlCardUtil()

{
	hWnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();
	m_bLogic = TRUE;
	m_bSymmetry = FALSE;
	m_fAccel = 0.1;
	m_fDecel = 0.1;
	m_nPulse = 6400;
	m_nTSacc = 0.01;
	m_nStopVel = 10000;
	m_nSpeedmax = 32000;
	m_nSpeedst = 16000;
	m_nActionst = 0;
	m_nAxis = 0;
	m_nHome = 2;//?
	m_nEzno = 0;//?

	highSpeedMode = true;
	moveMode_S = false;
	m_HomeMode_HighSpeed=true;
	m_HomeMode_Positive=true;
	m_nActionst = 0;//�㶯
	direction = true;
	boardsNum=BoardInit();
	if (boardsNum > 0) {
		successInit = true;
	}
	

	
	
}



MotionControlCardUtil::~MotionControlCardUtil()
{
	OnDestroy();
}

int MotionControlCardUtil::BoardInit()
{
	int i = d2410_board_init();
	if (i <= 0)//���ƿ��ĳ�ʼ������
	{
		MessageBox(hWnd,TEXT("��ʼ��DMC2480��ʧ�ܣ�"), TEXT("����"),NULL);
		return 0;
	}
	return i;;
}



void MotionControlCardUtil::moveToPoint(CPoint cp)
{
    int pulseX = cp.x - d2410_get_position(0);
    int pulseY = cp.y - d2410_get_position(1);
	moveToAxisPoint(0, pulseX);
	moveToAxisPoint(1, pulseY);
}

void MotionControlCardUtil::moveToPoint(int axis, int pulse)
{
	int pulseToMove;
	switch (axis)
	{
	case 0:
		pulseToMove = pulse - d2410_get_position(0);
		break;
	case 1:
		pulseToMove = pulse - d2410_get_position(1);
		break;
	case 2:
		pulseToMove = pulse - d2410_get_position(2);
		break;
#ifndef _NotUAXIX
	case 3:
		pulseToMove = pulse - d2410_get_position(3);
		break;
#endif

	}
	moveToAxisPoint(axis, pulseToMove);

}

void MotionControlCardUtil::setCurrentPositionZero()
{
	for (int i = 0; i < 4; i++)
	{
		d2410_set_position(i, 0);
	}
}


void MotionControlCardUtil::Move()
{
	if (!successInit)
		return;

	int logic = 1;

	if ((d2410_check_done(m_nAxis)) == 0) //�Ѿ����˶���
		return;
	//�趨����ģʽ���߼����򣨴˴�����ģʽ�̶�ΪP+D��������+����	
	d2410_set_pulse_outmode(m_nAxis, m_bLogic ? 1 : 3);
	//�趨S�ν��������
	d2410_set_st_profile(m_nAxis, m_nSpeedst, m_nSpeedmax, m_fAccel, m_fDecel, m_nTSacc, m_nStopVel);
	//�趨T�ν��������
	d2410_set_profile(m_nAxis, m_nSpeedst, m_nSpeedmax, m_fAccel, m_fDecel);

	if (m_nActionst == 0) {//�㶯(λ��ģʽ)
		//��ʹ������˶�����������Ҫ���ԣ��滻��Ժ���Ϊ���Ժ������ɣ������ɲ���
		m_nSpeedst == 2 ?//S������
			d2410_s_pmove(m_nAxis, m_nPulse*logic, 0) :
			d2410_ex_t_pmove(m_nAxis, m_nPulse*logic, 0);
		//T�μ��٣�����ʼ�ٶ����˶��ٶ����ʱ����Ϊ����
	}
	else {//��������(�ٶ�ģʽ)
		//int	dir = (-m_nPulse * logic > 0) ? 0 : 1;//�Ե㶯���ȣ������˶�����
		
		m_nSpeedst == 2 ?//S������
			d2410_s_vmove(m_nAxis, direction) :
			d2410_t_vmove(m_nAxis, direction);
		//T�μ��٣�����ʼ�ٶ����˶��ٶ����ʱ����Ϊ����
	}


}




void MotionControlCardUtil::OnCheckSymmetry(bool isSymmetry)
{
	//�Գƣ������ʱ�估����ʱ�����
	//�ǶԳƣ��Զ��趨����ʱ��Ϊ����ʱ������
	if (isSymmetry) {
		m_fDecel = m_fAccel;
	}
	else {
		m_fDecel = m_fAccel*2;
	}
}

void MotionControlCardUtil::moveToAxisPoint(int axis, int pulse)//�����˶�
{
	m_nAxis = axis;
	m_nActionst = 0;//���˶�
	m_nPulse = pulse;
	Move();
}



void MotionControlCardUtil::moveContinue(char axis, bool positiveDirection)
{

	positiveDirection == true ? direction = 1 : direction = 0; //����Ϊ1����Ϊ0
	
	m_nAxis =0;
	if (axis == 'y')
		m_nAxis = 1;
	else if (axis == 'z')
		m_nAxis = 2;
#ifndef _NotUAXIX
	else if (axis == 'u')
		m_nAxis = 3;
#endif
	//��ǿ�ʼ�˶�

	m_nActionst = 1;
	Move();
}

void MotionControlCardUtil::stopContinueMove(char axis)
{

	m_nAxis = 0;
	if (axis == 'y')
		m_nAxis = 1;
	else if (axis == 'z')
		m_nAxis = 2;
	else if (axis == 'u')
		m_nAxis = 3; 
	
	Stop(false,true, m_nAxis);


}

//void MotionControlCardUtil::moveToBasePoint(int axis)
//{
//
//	m_nAxis = axis;
//	d2410_set_profile(m_nAxis, m_nSpeedst, m_nSpeedmax, m_fAccel, m_fAccel);//�����ٶ�����
//	d2410_config_EZ_PIN(m_nAxis, 0, 0);//����EZ���÷�ʽ
//	d2410_config_home_mode(m_nAxis, m_nHome, m_nEzno);//���û��㷽ʽ
//	int side;
//	int speed;
//	if (m_HomeMode_HighSpeed) {
//		speed = 1;
//	}
//	else {
//		speed = 0;
//	}
//
//	if (m_HomeMode_Positive) {
//		side = 1;
//	}
//	else {
//		side = 2;
//	}
//	d2410_home_move(m_nAxis, speed, side);//���㶯��
//}

void MotionControlCardUtil::moveToBasePoint(int axis)
{
	switch (axis)
	{
	case 0:
		moveToPoint(0, _X_ZERO_POINT);
		break;
	case 1:
		moveToPoint(1, _Y_ZERO_POINT);
		break;
	case 2:
		moveToPoint(2, _Z_ZERO_POINT);
		break;
#ifndef _NotUAXIX
	case 3:
		moveToPoint(3, _U_ZERO_POINT);
		break;
#endif
	}
}

void MotionControlCardUtil::moveToBaseCPoint()
{
	moveToPoint(1, _Y_ZERO_POINT);
	moveToPoint(0, _X_ZERO_POINT);
}

void MotionControlCardUtil::moveToBaseCPointAll()
{
#ifndef _NotUAXIX
	moveToPoint(3, _U_ZERO_POINT);
#endif
	moveToPoint(2, _Z_ZERO_POINT);
	moveToPoint(1, _Y_ZERO_POINT);
	moveToPoint(0, _X_ZERO_POINT);
}

void MotionControlCardUtil::moveToBasePointCS()
{
	//
	d2410_set_HOME_pin_logic(0, 0, 1); //����ԭ���ź�Ϊ�͵�ƽ��Ч�������ź��˲�
	d2410_set_HOME_pin_logic(1, 0, 1); //����ԭ���ź�Ϊ�͵�ƽ��Ч�������ź��˲�
	d2410_set_HOME_pin_logic(2, 0, 1);
	d2410_set_profile(0, m_nSpeedst, m_nSpeedmax, m_fAccel, m_fAccel);
	d2410_set_profile(1, m_nSpeedst, m_nSpeedmax, m_fAccel, m_fAccel);
	d2410_set_profile(2, m_nSpeedst, m_nSpeedmax, m_fAccel, m_fAccel);

	d2410_home_move(0, 2, 1);
	d2410_home_move(1, 2, 1);
	d2410_home_move(2, 2, 1);

}

void MotionControlCardUtil::moveToBaesZ()
{
	moveToPoint(2, _Z_ZERO_POINT);
}

void MotionControlCardUtil::moveToInHolePoint()
{
	moveToPoint(2, _Z_INHALE_POINT);
}

void MotionControlCardUtil::emergentStop()
{
	Stop(true, false,0);
}

void MotionControlCardUtil::grabToLocation(CPoint cp1, CPoint cp2,int angle)
{
	bool upDown = true;
#ifdef _TestNotUpDown
	upDown = false;
#endif
	//�����ƶ�->����->����->̧��->�ƶ�->����->����->̧�����
#ifndef _NotUAXIX
	moveToBasePoint(3);//z u����㣬����
	while (!isAllStop());
	moveToPoint(3, 0);
#endif
	moveToBaesZ();
	while (!isAllStop());
	

    moveToPoint(cp1);//�ƶ�
	while (!isAllStop());

	if (upDown) {
		moveToInHolePoint();
		while (!isAllStop());
		inHole();
		Sleep(500);
		while (!isAllStop());
		moveToBaesZ();



	}
	
#ifndef _NotUAXIX
	moveToPoint(3, 0);// U ����
	while (!isAllStop());
	int uPulse = angleDegreeToPulse(angle);
	moveToPoint(3, uPulse);
#endif
	while (!isAllStop());
	moveToPoint(cp2);//�ƶ�

	while (!isAllStop());
	if (upDown) {

		moveToInHolePoint();
		while (!isAllStop());
		gassing();
		while (!isAllStop());
		moveToBaesZ();
		
	}

}

void MotionControlCardUtil::inHole()
{
	d2410_write_outbit(0, 2, 0);
}

void MotionControlCardUtil::gassing()
{
	d2410_write_outbit(0, 2, 1);
}






int MotionControlCardUtil::angleDegreeToPulse(double degree)
{
	return (int)10000/degree;
}

void MotionControlCardUtil::up(bool zeroUAxis)
{

	d2410_t_pmove(2, _UP_PULSE_STD, 1);
#ifndef _NotUAXIX
	if (zeroUAxis) {
		moveToBasePoint(3);
	}
#endif
}
void MotionControlCardUtil::down(bool inhole, bool gassing, bool inhole2, bool gassing2)
{
	if (inhole)
	{
		d2410_write_outbit(0, 2, 0);//��ȡ
		Sleep(10);
	}

	if (gassing)
		d2410_write_outbit(0, 2, 1);//����


	d2410_t_pmove(2, _DOWN_PULSE_STD, 1);

	if (inhole2)
	{
		d2410_write_outbit(0, 2, 0);//��ȡ
		Sleep(10);
	}

	if (gassing2)
		d2410_write_outbit(0, 2, 1);//����

}
void MotionControlCardUtil::Stop(bool isEmerge, bool oneAxis,int axis)
{
	if (isEmerge) {
		d2410_emg_stop();
	}
	else {
		if (oneAxis) {
			d2410_imd_stop(axis);
		}
		else {
			for (int i = 0; i < 4; i++) {
				d2410_imd_stop(m_nAxis);
			}
		}
	}

}


void MotionControlCardUtil::setMovingMode_S()
{
	moveMode_S = true;
	m_nSpeedmax = m_nSpeedst;//�ٶ����
}


void MotionControlCardUtil::setMovingMode_T()
{
	//T���ٶ�
	moveMode_S = false;
	if (m_nSpeedmax == m_nSpeedst) {//�Զ�������ͬ�ٶ�
		m_nSpeedmax = m_nSpeedst + m_nSpeedmax;
	}
}

void MotionControlCardUtil::setHighSpeed()
{
	m_nSpeedmax = 0;
	m_nSpeedst = _MotionControlCardUtil_HighSpeed;
	moveMode_S == true ? setMovingMode_S() : setMovingMode_T();
}

void MotionControlCardUtil::setLowSpeed()
{
	m_nSpeedmax = 0;
	m_nSpeedst = _MotionControlCardUtil_LowSpeed;
	moveMode_S == true ? setMovingMode_S() : setMovingMode_T();
}

void MotionControlCardUtil::setHomeMode_Speed(bool highSpeed)
{
	m_HomeMode_HighSpeed = highSpeed;
	
}

void MotionControlCardUtil::setHomeMode_Side(bool positive)
{
	m_HomeMode_Positive= positive;
}

bool MotionControlCardUtil::isHomeMode_HighSpeed()
{
	return m_HomeMode_HighSpeed;
}

bool MotionControlCardUtil::isHomeMode_PositiveSide()
{
	return m_HomeMode_Positive;
}

double MotionControlCardUtil::readCurrentSpeed(int m_nAxis)
{
	return d2410_read_current_speed(m_nAxis);
	
}

double MotionControlCardUtil::readCurrentSpeedMax()
{
	double max = readCurrentSpeed(0);
	if (readCurrentSpeed(1) > max) {
		max = readCurrentSpeed(1);
	}
	if (readCurrentSpeed(2) > max) {
		max = readCurrentSpeed(2);
	}
	if (readCurrentSpeed(3) > max) {
		max = readCurrentSpeed(3);
	}

	return max;
}

int MotionControlCardUtil::readSpeedStart()
{
	return m_nSpeedst;
}

int MotionControlCardUtil::readSpeedMax()
{
	return m_nSpeedmax;
}

double MotionControlCardUtil::readAccl()
{
	return m_fAccel;
}





void MotionControlCardUtil::OnDestroy()
{
	d2410_board_close();
}



CPoint MotionControlCardUtil::getCurrentPosition()
{	
	CPoint cp(d2410_get_position(0), d2410_get_position(1));
	return cp;
}

CPoint MotionControlCardUtil::getBasePosition()
{
	

	return CPoint(_X_ZERO_POINT, _Y_ZERO_POINT);
}

int MotionControlCardUtil::getCurrentPulse(char aixs)
{
	switch (aixs) {
		case 'x': return d2410_get_position(0);
		case 'y': return d2410_get_position(1);
		case 'z': return d2410_get_position(2);
		case 'u': return d2410_get_position(3);
	}
	return -1;
}

bool MotionControlCardUtil::isHighSpeedMode()
{
	return highSpeedMode;
}

bool MotionControlCardUtil::isMoveMode_S()
{
	return moveMode_S;
}

bool MotionControlCardUtil::isStop(char axis)
{
	if (successInit == false) {
		return true;
	}

	bool isStop=true;
	switch (axis) {
	case 'x': 
		if (d2410_check_done(0) == 0) {
			isStop = false;
		};
	case 'y':
		if (d2410_check_done(1) == 0) {
			isStop = false;
		};
	case 'z':
		if (d2410_check_done(2) == 0) {
			isStop = false;
		};
	case 'u':
		if (d2410_check_done(3) == 0) {
			isStop = false;
		};
	}
	return isStop;
}

bool MotionControlCardUtil::isAllStop()
{
	for (int i = 0; i < 4; i++) {
		if ((d2410_check_done(i)) == 0)//�˶���
			return false;
	}
	return true;
	
}

bool MotionControlCardUtil::isSymmetry()
{
	return m_bSymmetry;
}

CString MotionControlCardUtil::getStatus(bool allAxis, char axis)
{
	CString s;
	allAxis ?
		isAllStop() ? s = TEXT("��ֹ") : s = TEXT("�˶�") :
		isStop(axis) ? s = TEXT("��ֹ") : s = TEXT("�˶�");
	return s;
}









