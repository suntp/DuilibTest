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

	LPCTSTR  GetWindowClassName()const//�麯��������������ʽʵ��	
	{ 
		return _T("UIMainFrame");//���ڵ���������SPY++�ܿ�����
	};

private:
	CPaintManagerUI m_pm;//��ؼ����ƺ���Ϣ�����������

	CButtonUI* m_pBtnClose;//�ر� 
	CButtonUI* m_pBtnMax;//��� 
	CButtonUI* m_pBtnMin;//��С�� 
	CButtonUI* m_pBtnCalc;//���㰴ť 
	CEditUI* m_pEditSource1;//���� 
	CEditUI* m_pEditSource2;//������ 
	CEditUI* m_pEditResult;//������
};