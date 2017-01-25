#include "adder_Calc.h"

CAdderCalc::CAdderCalc(void)
{
}

CAdderCalc::~CAdderCalc(void)
{
}

void CAdderCalc::Init()
{
	//初始化按钮控件对应的指针 
	m_pBtnClose = static_cast<CButtonUI*>(m_pm.FindControl(_T("BtnClose"))); 

	//找到从xml文件中的命名加载的对应按钮 
	m_pBtnMax = static_cast<CButtonUI*>(m_pm.FindControl(_T("BtnMax"))); 
	m_pBtnMin = static_cast<CButtonUI*>(m_pm.FindControl(_T("BtnMin"))); 
	m_pBtnCalc=static_cast<CButtonUI*>(m_pm.FindControl(_T("BtnCalc"))); 
	
	//初始化编辑框控件对应的指针 
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

	//主窗口类与窗口句柄关联 
	m_pm.Init(m_hWnd); 
	CDialogBuilder builder; 
	CControlUI* pRoot = builder.Create(_T("calcUISkin.xml"), (UINT)0, NULL, &m_pm); //加载XML并动态创建界面无素，与布局界面元素，核心函数单独分析 //注意：CDialogBuilder 并不是一个对话框类 
	ASSERT(pRoot && "Failed to parse XML"); 
	
	if (NULL==pRoot) //如果找不到皮肤文件则退出 
	{ 
		MessageBox(NULL,TEXT("Cant not Find the skin!"),NULL,MB_ICONHAND); 
		return 0; 
	} 
	
	m_pm.AttachDialog(pRoot); //附加控件数据到HASH表中 
	m_pm.AddNotifier(this); //增加通知处理 
	Init(); //应用程序其他初始化 
	return 0;
}

void CAdderCalc::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("windowinit") ) 
		OnPrepare(); 
	else if( msg.sType == _T("click") ) //鼠标键按下按钮控件消息 
	{ 
		if( msg.pSender == m_pBtnClose ) //关闭按钮按下，程序退出 
		{ 
			//PostQuitMessage(0); 
			Close();
			return; 
		} 
		else if( msg.pSender == m_pBtnMin ) //最小化按钮按下，发送系统命令消息将窗口最小化 
		{ 
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); 
			return; 
		} 
		else if( msg.pSender == m_pBtnMax) //最大化按钮按下，发送系统命令消息将窗口最大化
		{ 
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); 
			return; 
		} 
		else if (msg.pSender == m_pBtnCalc)//计算按钮按下 
		{ //从编辑控件中获取两个加数 //判断输入的CStdString的内容是否为空，实际上还应该对输入数据类型做限制的 
			if ((m_pEditSource1->GetText()).IsEmpty()||(m_pEditSource2->GetText()).IsEmpty()) 
			{ 
				MessageBox(NULL,TEXT("Please input two interger number first!"),NULL,MB_ICONHAND); 
				return; 
			} 
			//将输入字符串转化为整型数 
			# ifdef _UNICODE 
				int add1=_wtof((m_pEditSource1->GetText()).GetData()); 
				int add2=_wtof((m_pEditSource2->GetText()).GetData()); 
			#else 
				int add1=atof((m_pEditSource1->GetText()).GetData()); 
				int add2=atof((m_pEditSource2->GetText()).GetData()); 
			# endif 
			int add12=add1+add2; 
			//将计算和整型数转化为字符串,并显示出来 
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

LRESULT CAdderCalc::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//销毁窗口
{
	::PostQuitMessage(0L);//通知系统线程退出

	bHandled = FALSE;//不需要应用程序自行处理
	return 0;
}
LRESULT CAdderCalc::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//更改非客户区状态
{
	if( ::IsIconic(*this) )//determines whether the specified window is minimized 
		bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;//需要应用程序自行处理？根据消息判断
}

LRESULT CAdderCalc::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//重新计算客户区大小
{
	return 0;
}

LRESULT CAdderCalc::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//重绘非客户区
{
	return 0;
}
LRESULT CAdderCalc::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//处理鼠标移动时枚举鼠标所在区域
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
			return HTCAPTION;//返回在标题栏里
	}

	return HTCLIENT;//返回鼠标在客户区里
}

LRESULT CAdderCalc::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if( !::IsIconic(*this) //不允许最小化
		&& (szRoundCorner.cx != 0 
		|| szRoundCorner.cy != 0) ) 
	{
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right,//创建圆角矩形域
			rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	bHandled = FALSE;//不需要应用程序自行处理
	return 0;
}

LRESULT CAdderCalc::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//关闭窗口
{
	bHandled = FALSE;//不需要应用程序自行处理
	return 0;
}

LRESULT CAdderCalc::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)//获得窗口的最大最小尺寸信息
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);//获得显示器信息
	CDuiRect rcWork = oMonitor.rcWork;//虚拟屏幕坐标下的显示矩形域
	rcWork.Offset(-rcWork.left, -rcWork.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;//填充LPMINMAXINFO结构
	lpMMI->ptMaxPosition.x	= rcWork.left;
	lpMMI->ptMaxPosition.y	= rcWork.top;
	lpMMI->ptMaxSize.x		= rcWork.right;
	lpMMI->ptMaxSize.y		= rcWork.bottom;

	bHandled = FALSE;//不需要应用程序自行处理
	return 0;
}

LRESULT CAdderCalc::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
	if( wParam == SC_CLOSE ) 
	{
		::PostQuitMessage(0L);
		bHandled = TRUE;//需要应用程序自行处理
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);//determines whether a window is maximized
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if( ::IsZoomed(*this) != bZoomed ) 
	{
		if( !bZoomed ) //窗体不允许最大化
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("BtnMax")));
			if( pControl ) 
				pControl->SetVisible(false);//最大化按钮设为不可见
		}
		else //窗体允许最大化
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("BtnMax")));
			if( pControl ) 
				pControl->SetVisible(true);//最大化按钮设为可见
		}
	}
	return lRes;
}

LRESULT CAdderCalc::HandleMessage(unsigned int uMsg, WPARAM wParam, LPARAM lParam)//应用需要处理的消息及处理函数
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;//需要应用程序自行处理
	switch( uMsg ) ////应用需要处理的消息
	{
	case WM_CREATE:   //创建窗口    
		lRes = OnCreate(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_CLOSE:        //关闭窗口
		lRes = OnClose(uMsg, wParam, lParam, bHandled);
		break;
	case WM_DESTROY:      //销毁窗口
		lRes = OnDestroy(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCACTIVATE:   //激活非客户区
		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCCALCSIZE:  //重新计算客户区尺寸
		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled);
		break;
	case WM_NCPAINT:    //重绘非客户区
		lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_NCHITTEST:   //枚举鼠标所在区域
		lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled);
		break;
	case WM_SIZE:         //改变窗口尺寸
		lRes = OnSize(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_GETMINMAXINFO: //获得显示窗口的最大最小尺寸信息
		lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_SYSCOMMAND:    //处理系统命令，包括菜单命令，最大最小化按钮按下
		lRes = OnSysCommand(uMsg, wParam, lParam, bHandled);
		break;
	default:
		bHandled = FALSE;//不需要应用程序自行处理
	}
	if( bHandled ) 
		return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) //DUILIB 库帮处理的消息及相关的处理函数
		return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);//应用层和DUILIB都不处理的消息交由系统默认处理
}