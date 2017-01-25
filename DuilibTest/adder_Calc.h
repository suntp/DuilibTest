#pragma once

#include "stdAfx.h"
#include"math.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

class CAdderCalc : public CWindowWnd, public INotifyUI
{
public:
	CAdderCalc();
	~CAdderCalc();

	void Init();
	void OnPrepare();
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(unsigned int uMsg, WPARAM wParam, LPARAM lParam);

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LPCTSTR  GetWindowClassName()const//虚函数用内联函数方式实现	
	{ 
		return _T("UIMainFrame");//窗口的类名，用SPY++能看到的
	};

private:
	CPaintManagerUI m_pm;//与控件绘制和消息处理关联起来

	CButtonUI* m_pBtnClose;//关闭 
	CButtonUI* m_pBtnMax;//最大化 
	CButtonUI* m_pBtnMin;//最小化 
	CButtonUI* m_pBtnCalc;//计算按钮 
	CEditUI* m_pEditSource1;//加数 
	CEditUI* m_pEditSource2;//被加数 
	CEditUI* m_pEditResult;//加数和
};