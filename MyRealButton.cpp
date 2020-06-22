#include "MyRealButton.h"



MyRealButton::MyRealButton(string button_id):button_id(button_id)
{
}


MyRealButton::~MyRealButton()
{
}


BOOL MyRealButton::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// �������������º��ɿ�״̬���ϱ�������
	//_In_ HWND hWnd,  Ŀ�괰��
	//_In_ UINT Msg,   message=9999
	//_Pre_maybenull_ _Post_valid_ WPARAM wParam, ��һ��param ������0��ʾ���£�1��̧��
	//_Pre_maybenull_ _Post_valid_ LPARAM lParam); �ڶ���param �������ʾ��ť
	// 0 m_xUp
	// 1 m_xDown
	// 2 m_yUp
	// 3 m_yDown
	// 4 m_zUp
	// 5 m_zDown
	// 6 m_uClock
	// 7 m_uUnclock

	switch (message)
	{
	case WM_LBUTTONDOWN:
		if (button_id == "m_xUp") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 0, 0);
		}
		else if (button_id == "m_xDown") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 0, 1);
		}
		else if (button_id == "m_yUp") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 0, 2);
		}
		else if (button_id == "m_yDown") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 0, 3);
		}
		else if (button_id == "m_zUp") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 0, 4);
		}
		else if (button_id == "m_zDown") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 0, 5);
		}
		else if (button_id == "m_uClock") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 0, 6);
		}
		else if (button_id == "m_uUnclock") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 0, 7);
		}
		break;
	case WM_LBUTTONUP:
		if (button_id == "m_xUp") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 1, 0);
		}
		else if (button_id == "m_xDown") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 1, 1);
		}
		if (button_id == "m_yUp") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 1, 2);
		}
		else if (button_id == "m_yDown") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 1, 3);
		}
		if (button_id == "m_zUp") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 1, 4);
		}
		else if (button_id == "m_zDown") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 1, 5);
		}
		if (button_id == "m_uClock") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 1, 6);
		}
		else if (button_id == "m_uUnclock") {
			::SendMessage(this->GetParent()->m_hWnd, 9999, 1, 7);
		}
		break;
	default:
		break;
	}
	return CButton::OnWndMsg(message, wParam, lParam, pResult);
}
