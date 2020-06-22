#include "MfcUtil.h"

MfcUtil::MfcUtil()
{
}


MfcUtil::~MfcUtil()
{
}

string MfcUtil::intToString(int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

string MfcUtil::doubleToString(double value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}


void MfcUtil::ShowPic(CString filePath, WORD mfcID)//�βο���Ϊ������ͼƬ�����ָ�룬����Ϊ��ͨ����ʡȥ���β�
{
	
	//��mfcID��ʾͼƬ��������Сά�ֱ���
	float cx, cy, dx, dy, k, t;//���ؼ��Ŀ�͸��Լ�ͼƬ��͸��йصĲ���
	CRect   rect;//���ڻ�ȡͼƬ�ؼ��Ŀ�͸�
	CImage q;//ΪcimageͼƬ�ഴ��һ������
	q.Load(filePath);//���캯�����β���������ͼƬ��·�� 
	cx = q.GetWidth();
	cy = q.GetHeight();//��ȡͼƬ�Ŀ� ��
	k = cy / cx;//���ͼƬ�Ŀ�߱�

	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(mfcID);//��ȡ�ؼ����
	pWnd->GetClientRect(&rect);//��ȡPicture Control�ؼ��Ŀͻ���
	dx = rect.Width();
	dy = rect.Height();//��ÿؼ��Ŀ�߱�
	t = dy / dx;//��ÿؼ��Ŀ�߱�
	if (k >= t)
	{

		rect.right = floor(rect.bottom / k);
		rect.left = (dx - rect.right) / 2;
		rect.right = floor(rect.bottom / k) + (dx - rect.right) / 2;
	}
	else
	{
		rect.bottom = floor(k*rect.right);
		rect.top = (dy - rect.bottom) / 2;
		rect.bottom = floor(k*rect.right) + (dy - rect.bottom) / 2;
	}
	//��صļ���Ϊ����ͼƬ�ڻ�ͼ�����а�������ʾ��ԭ��ܺö������ͼƬ�ܿ��ǲ��ߣ����������пհ��������ͼƬ�ܸ߶�������������пհ��������ұ������߿հ���һ����

	CDC *pDc = NULL;
	pDc = pWnd->GetDC();//��ȡpicture control��DC������ʲô������Ҳ��֪�����ٶȾ���
	int ModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//����ָ���豸�����е�λͼ����ģʽ

	GetDlgItem(mfcID)->ShowWindow(FALSE);
	GetDlgItem(mfcID)->ShowWindow(TRUE);
	q.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//��ʾ����
	SetStretchBltMode(pDc->m_hDC, ModeOld);
	//ReleaseDC(mfcID);//�ͷ�ָ��ռ�
}

//UTF8תUnicode
CString MfcUtil::UTF82WCS(const char* szU8)
{
	//Ԥת�����õ�����ռ�Ĵ�С;
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);

	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
	wchar_t* wszString = new wchar_t[wcsLen + 1];

	//ת��
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);

	//������'\0'
	wszString[wcsLen] = '\0';

	CString unicodeString(wszString);

	delete[] wszString;
	wszString = NULL;

	return unicodeString;
}

double MfcUtil::CStringToDouble(CString cstr)
{
	char * ch = CStringToChar(cstr);
	return atof(ch);
}

int MfcUtil::CStringToInt(CString str)
{
	return _ttoi(str);
}

int MfcUtil::stringToInt(string str)
{
	return atoi(str.c_str());
}

CString MfcUtil::charToCString(char * chString)
{
	return CString(chString);
}

LPWSTR MfcUtil::charToLPWSTR(char * ch)
{
	LPWSTR aaa = CA2W(ch);
	return aaa;
}

CString MfcUtil::DoubleToCString(double value,int digital)
{
	CString str;

	if (digital == 0) 
	{
		str.Format(_T("%.0lf"), value);//0λ��
	}
	else
	{
		str.Format(_T("%.2lf"), value);//2λ��
	}
	return str;
}


char * MfcUtil::CStringToChar(CString cstr)
{
	//������ʶ
	USES_CONVERSION;
	//����T2A��W2A��֧��ATL��MFC�е��ַ�
	//char * pFileName = T2A(cstr);
	char * pFileName = W2A(cstr); //Ҳ��ʵ��ת��
	return pFileName;
}

CString MfcUtil::CharToCString(char * pFileName)
{
	//����char *�����С�����ֽ�Ϊ��λ��һ������ռ�����ֽ�
	int charLen = strlen(pFileName);
	
	//������ֽ��ַ��Ĵ�С�����ַ����㡣
	int len = MultiByteToWideChar(CP_ACP, 0, pFileName, charLen, NULL, 0);

	//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ķ��ֽ��ַ���С
	TCHAR *buf = new TCHAR[len + 1];
	
	//���ֽڱ���ת���ɿ��ֽڱ���
	MultiByteToWideChar(CP_ACP, 0, pFileName, charLen, buf, len);
	
	buf[len] = '/0'; //����ַ�����β��ע�ⲻ��len+1
	
	//��TCHAR����ת��ΪCString
	CString pWideChar;
	pWideChar.Append(buf);
	
		//ɾ��������
	delete[]buf;
	return pWideChar;
}

string MfcUtil::CStringToString(CString str)
{
	char* c = CStringToChar(str);

	return c;
}

LPCTSTR MfcUtil::charToLPCTSTR(char * ch)
{
	//char ch[1024] = "wo shi ni baba";
	int num = MultiByteToWideChar(0, 0, ch, -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, ch, -1, wide, num);
	return wide;
}

char* MfcUtil::LPCTSTRToChar(LPCTSTR widestr)
{
	//wchar_t widestr[1024] = L"wo shi ni yeye";
	int num = WideCharToMultiByte(CP_OEMCP, NULL, widestr, -1, NULL, 0, NULL, FALSE);
	char *pchar = new char[num];
	WideCharToMultiByte(CP_OEMCP, NULL, widestr, -1, pchar, num, NULL, FALSE);
	return pchar;
}

string MfcUtil::IntToString(int value, int modeDigital)
{

	// value����ת�������ݡ�
		 // string��Ŀ���ַ����ĵ�ַ��
	// radix��ת����Ľ�������������10���ơ�16���Ƶȡ�
	 // ����ָ��string����ַ�����ָ��
	char * chr=new char[100];
	_itoa_s(value,chr,100,modeDigital);
	//string str = chr;
	return chr;

}


LPCTSTR MfcUtil::StringToLPCSTR(string value) {

	LPCWSTR  * unicodeLPCTSTR = nullptr;
	LPCSTR * unLPCTSTR=nullptr;
	StringToLPCSTR(value, unicodeLPCTSTR, unLPCTSTR);
#ifdef _UNICODE
	return *unicodeLPCTSTR;
#else
	return *unLPCTSTR;
#endif
}

LPCWSTR MfcUtil::charToLPCWSTR(char * cString)
{


	return CStringToLPCWSTR(CString(cString));
}

LPCWSTR MfcUtil::CStringToLPCWSTR(CString str)
{

	//USES_CONVERSION;
	//LPCWSTR wszClassName = new WCHAR[str.GetLength() + 1];
	//wcscpy((LPTSTR)wszClassName, T2W((LPTSTR)str.GetBuffer(NULL)));
	//str.ReleaseBuffer();
	//return str;



	USES_CONVERSION;
	rsize_t size = str.GetLength() + 1;
	LPCWSTR wszClassName = new WCHAR[str.GetLength() + 1];
	wcscpy_s((wchar_t*)wszClassName, size, str);
	return str;

}


LPCSTR MfcUtil::CStringToLPCSTR(CString cstr)
{
	char* chr = CStringToChar(cstr);
	return (LPCSTR)chr;
}

void MfcUtil::StringToLPCSTR(string value, LPCWSTR  * unicodeLPCTSTR, LPCSTR * unLPCTSTR)
{

#ifdef _UNICODE_hao
	size_t origsize = value.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(value.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, value.c_str(), _TRUNCATE);
	unicodeLPCTSTR = &wcstring;
#else

	LPCSTR str = value.c_str();
	unLPCTSTR = &str;
#endif

}

LPCWSTR MfcUtil::stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}


void MfcUtil::getStringFromDlg(HWND dlgID,int itemID)
{
	//CEdit* pBoxOne;
	//pBoxOne = (CEdit*)GetDlgItem(dlgID, itemID);
	////��ֵ
	////pBoxOne-> SetWindowText( _T("FOO ") );
	////ȡֵ
	//CString str;
	//pBoxOne->GetWindowText(str);
	//return str;
	
}

CString MfcUtil::concatCstring(char* c1, int i, char* c2)
{
	

	CString csi;
	csi.Format(_T("%d"),i);
	csi = CharToCString(c1) + csi + CharToCString(c2);
	return csi;
}

void MfcUtil::openFileBrowser(CString defaultPath, CWnd* pParentWnd, int mfcID)
{
	//��ѡ�񶯵���·����ʾ��ָ���ĶԻ�����

	LPCWSTR defaultPathW = CStringToLPCWSTR(defaultPath);

	//LPCWSTR defaultPath = defaultPath;

	SetCurrentDirectory(defaultPath);
	//static char BASED_CODE szFilter[] = "�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||";

	LPCTSTR lpszFilter = TEXT("*.mat|�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	
	lpszFilter = NULL;
	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpszFilter, pParentWnd,0,TRUE);

	//FileDlg.m_ofn.lpstrInitialDir = defaultPath;
	FileDlg.m_ofn.lpstrInitialDir = TEXT("D:\tmp");
	CString editParam;
	if (FileDlg.DoModal() == IDOK)
	{

		CString strFileName = FileDlg.GetFileName();
		CString strFileExt = FileDlg.GetFileExt();
		CString lpstrName = FileDlg.GetPathName();
		editParam = lpstrName;
		pParentWnd->GetDlgItem(mfcID)->SetWindowTextW(editParam);
	}


	//return editParam;
}

void MfcUtil::setPictureColorRed(CWnd *pWnd, int mfcId, CStatic& m_static)
{

	setPictureColor(pWnd, mfcId, m_static, 255, 0, 0);

}

void MfcUtil::setPictureColorGreen(CWnd *pWnd,int mfcId, CStatic& m_static)
{

	setPictureColor(pWnd, mfcId, m_static,0,255,0);

}



void MfcUtil::setPictureColor(CWnd *pWnd, int mfcId, CStatic& m_static,int red,int green,int blue)
{

	CRect rc;
	CWnd *iWnd = pWnd->GetDlgItem(mfcId);//����Ϊ�ؼ�ID
	iWnd->GetClientRect(&rc);//rcΪ�ؼ��Ĵ�С��
	int py = rc.Height();
	int px = rc.Width();

	FillRect(m_static.GetDC()->GetSafeHdc(), &rc, CBrush(RGB(red, green, blue)));

}

char*  MfcUtil::hexToCharIP(struct in_addr addrIP)
{  //in_addr
	char* ip;
	unsigned int intIP;
	memcpy(&intIP, &addrIP, sizeof(unsigned int));
	int a = (intIP >> 24) & 0xFF;
	int b = (intIP >> 16) & 0xFF;
	int c = (intIP >> 8) & 0xFF;
	int d = intIP & 0xFF;
	if ((ip = (char*)malloc(16 * sizeof(char))) == NULL)
	{
		return NULL;
	}
	sprintf(ip, "%d.%d.%d.%d", d, c, b, a);
	return ip;
}


void MfcUtil::Split(const string& src, const string& separator, vector<string>& dest)
{
	string str = src;
	string substring;
	string::size_type start = 0, index;
	dest.clear();
	index = str.find_first_of(separator, start);
	do
	{
		if (index != string::npos)
		{
			substring = str.substr(start, index - start);
			dest.push_back(substring);
			start = index + separator.size();
			index = str.find(separator, start);
			if (start == string::npos) break;
		}
	} while (index != string::npos);

	//the last part
	substring = str.substr(start);
	dest.push_back(substring);
}
