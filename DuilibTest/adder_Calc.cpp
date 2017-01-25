#include "adder_Calc.h"

CAdderCalc::CAdderCalc(void)
{
}

CAdderCalc::~CAdderCalc(void)
{
}

void CAdderCalc::Init()
{
	//��ʼ����ť�ؼ���Ӧ��ָ�� 
	m_pBtnClose = static_cast<CButtonUI*>(m_pm.FindControl(_T("BtnClose"))); 

	//�ҵ���xml�ļ��е��������صĶ�Ӧ��ť 
	m_pBtnMax = static_cast<CButtonUI*>(m_pm.FindControl(_T("BtnMax"))); 
	m_pBtnMin = static_cast<CButtonUI*>(m_pm.FindControl(_T("BtnMin"))); 
	m_pBtnCalc=static_cast<CButtonUI*>(m_pm.FindControl(_T("BtnCalc"))); 
	
	//��ʼ���༭��ؼ���Ӧ��ָ�� 
	m_pEditSource1=static_cast<CEditUI*>(m_pm.FindControl(_T("EditSource1"))); 
	m_pEditSource2=static_cast<CEditUI*>(m_pm.FindControl(_T("EditSource2")));
	m_pEditResult=static_cast<CEditUI*>(m_pm.FindControl(_T("EditResult")));
}

void CAdderCalc::OnPrepare() 
{
}

LRESULT CAdderCalc::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE); 
	styleValue &= ~WS_CAPTION; 
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	//���������봰�ھ������ 
	m_pm.Init(m_hWnd); 
	CDialogBuilder builder; 
	CControlUI* pRoot = builder.Create(_T("calcUISkin.xml"), (UINT)0, NULL, &m_pm); //����XML����̬�����������أ��벼�ֽ���Ԫ�أ����ĺ����������� //ע�⣺CDialogBuilder ������һ���Ի����� 
	ASSERT(pRoot && "Failed to parse XML"); 
	
	if (NULL==pRoot) //����Ҳ���Ƥ���ļ����˳� 
	{ 
		MessageBox(NULL,TEXT("Cant not Find the skin!"),NULL,MB_ICONHAND); 
		return 0; 
	} 
	
	m_pm.AttachDialog(pRoot); //���ӿؼ����ݵ�HASH���� 
	m_pm.AddNotifier(this); //����֪ͨ���� 
	Init(); //Ӧ�ó���������ʼ�� 
	return 0;
}

void CAdderCalc::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("windowinit") ) 
		OnPrepare(); 
	else if( msg.sType == _T("click") ) //�������°�ť�ؼ���Ϣ 
	{ 
		if( msg.pSender == m_pBtnClose ) //�رհ�ť���£������˳� 
		{ 
			//PostQuitMessage(0); 
			Close();
			return; 
		} 
		else if( msg.pSender == m_pBtnMin ) //��С����ť���£�����ϵͳ������Ϣ��������С�� 
		{ 
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); 
			return; 
		} 
		else if( msg.pSender == m_pBtnMax) //��󻯰�ť���£�����ϵͳ������Ϣ���������
		{ 
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); 
			return; 
		} 
		else if (msg.pSender == m_pBtnCalc)//���㰴ť���� 
		{ //�ӱ༭�ؼ��л�ȡ�������� //�ж������CStdString�������Ƿ�Ϊ�գ�ʵ���ϻ�Ӧ�ö������������������Ƶ� 
			if ((m_pEditSource1->GetText()).IsEmpty()||(m_pEditSource2->GetText()).IsEmpty()) 
			{ 
				MessageBox(NULL,TEXT("Please input two interger number first!"),NULL,MB_ICONHAND); 
				return; 
			} 
			//�������ַ���ת��Ϊ������ 
			# ifdef _UNICODE 
				int add1=_wtof((m_pEditSource1->GetText()).GetData()); 
				int add2=_wtof((m_pEditSource2->GetText()).GetData()); 
			#else 
				int add1=atof((m_pEditSource1->GetText()).GetData()); 
				int add2=atof((m_pEditSource2->GetText()).GetData()); 
			# endif 
			int add12=add1+add2; 
			//�������������ת��Ϊ�ַ���,����ʾ���� 
			TCHAR temp1[2*sizeof((m_pEditSource1->GetText()).GetData())] = {_T('\0')}; 

			# ifdef _UNICODE 
				_itow(add12,temp1,10);
				m_pEditResult->SetText((LPCTSTR)temp1); 
			#else 
				m_pEditResult->SetText(_itoa(add12,temp1,10)); 
			# endif 
		} 
	}
}

LRESULT CAdderCalc::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//���ٴ���
{
	::PostQuitMessage(0L);//֪ͨϵͳ�߳��˳�

	bHandled = FALSE;//����ҪӦ�ó������д���
	return 0;
}
LRESULT CAdderCalc::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//���ķǿͻ���״̬
{
	if( ::IsIconic(*this) )//determines whether the specified window is minimized 
		bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;//��ҪӦ�ó������д���������Ϣ�ж�
}

LRESULT CAdderCalc::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//���¼���ͻ�����С
{
	return 0;
}

LRESULT CAdderCalc::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//�ػ�ǿͻ���
{
	return 0;
}
LRESULT CAdderCalc::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//��������ƶ�ʱö�������������
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	RECT rcCaption = m_pm.GetCaptionRect();
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom )
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 )
			return HTCAPTION;//�����ڱ�������
	}

	return HTCLIENT;//��������ڿͻ�����
}

LRESULT CAdderCalc::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if( !::IsIconic(*this) //��������С��
		&& (szRoundCorner.cx != 0 
		|| szRoundCorner.cy != 0) ) 
	{
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right,//����Բ�Ǿ�����
			rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	bHandled = FALSE;//����ҪӦ�ó������д���
	return 0;
}

LRESULT CAdderCalc::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//�رմ���
{
	bHandled = FALSE;//����ҪӦ�ó������д���
	return 0;
}

LRESULT CAdderCalc::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//��ô��ڵ������С�ߴ���Ϣ
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);//�����ʾ����Ϣ
	CDuiRect rcWork = oMonitor.rcWork;//������Ļ�����µ���ʾ������
	rcWork.Offset(-rcWork.left, -rcWork.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;//���LPMINMAXINFO�ṹ
	lpMMI->ptMaxPosition.x	= rcWork.left;
	lpMMI->ptMaxPosition.y	= rcWork.top;
	lpMMI->ptMaxSize.x		= rcWork.right;
	lpMMI->ptMaxSize.y		= rcWork.bottom;

	bHandled = FALSE;//����ҪӦ�ó������д���
	return 0;
}

LRESULT CAdderCalc::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
	if( wParam == SC_CLOSE ) 
	{
		::PostQuitMessage(0L);
		bHandled = TRUE;//��ҪӦ�ó������д���
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);//determines whether a window is maximized
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if( ::IsZoomed(*this) != bZoomed ) 
	{
		if( !bZoomed ) //���岻�������
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("BtnMax")));
			if( pControl ) 
				pControl->SetVisible(false);//��󻯰�ť��Ϊ���ɼ�
		}
		else //�����������
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("BtnMax")));
			if( pControl ) 
				pControl->SetVisible(true);//��󻯰�ť��Ϊ�ɼ�
		}
	}
	return lRes;
}

LRESULT CAdderCalc::HandleMessage(unsigned int uMsg, WPARAM wParam, LPARAM lParam)//Ӧ����Ҫ�������Ϣ��������
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;//��ҪӦ�ó������д���
	switch( uMsg ) ////Ӧ����Ҫ�������Ϣ
	{
	case WM_CREATE:   //��������    
		lRes = OnCreate(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_CLOSE:        //�رմ���
		lRes = OnClose(uMsg, wParam, lParam, bHandled);
		break;
	case WM_DESTROY:      //���ٴ���
		lRes = OnDestroy(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCACTIVATE:   //����ǿͻ���
		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCCALCSIZE:  //���¼���ͻ����ߴ�
		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCPAINT:    //�ػ�ǿͻ���
		lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_NCHITTEST:   //ö�������������
		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled);
		break;
	case WM_SIZE:         //�ı䴰�ڳߴ�
		lRes = OnSize(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_GETMINMAXINFO: //�����ʾ���ڵ������С�ߴ���Ϣ
		lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_SYSCOMMAND:    //����ϵͳ��������˵���������С����ť����
		lRes = OnSysCommand(uMsg, wParam, lParam, bHandled);
		break;
	default:
		bHandled = FALSE;//����ҪӦ�ó������д���
	}
	if( bHandled ) 
		return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) //DUILIB ��ﴦ�����Ϣ����صĴ�����
		return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);//Ӧ�ò��DUILIB�����������Ϣ����ϵͳĬ�ϴ���
}