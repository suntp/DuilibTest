#include "adder_Calc.h"
#include "chat_dialog.hpp"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	HRESULT Hr = ::CoInitialize(NULL);//��ʼ��COM��, Ϊ����COM���ṩ֧��
	if( FAILED(Hr) ) 
		return 0;

	CPaintManagerUI::SetInstance(hInstance);//���ó���ʵ��

	//ʵ���������Ⱦ�����,���Ƥ���ļ�Ŀ¼������Ƥ���ļ���OnCreate֮�У�
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin\\adderCalc"));
	//CAdderCalc* pAppCalc = new CAdderCalc();//����Ӧ�ó��򴰿������
	//if( pAppCalc == NULL ) 
	//	return 0;
	//pAppCalc->Create(NULL, _T("AdderCalc"), UI_WNDSTYLE_DIALOG, 0);
	//pAppCalc->CenterWindow();//�����ڷŵ���������
	//pAppCalc->ShowWindow(true);//��ʾ����

	FriendListItemInfo myselft_info;
	myselft_info.folder = true;
	myselft_info.empty = true;
	myselft_info.nick_name = _T("111");
	myselft_info.id = _T("222");
	myselft_info.description = _T("3333");

	FriendListItemInfo friend_info;
	friend_info.folder = true;
	friend_info.empty = true;
	friend_info.nick_name = _T("111");
	friend_info.id = _T("222");
	friend_info.description = _T("3333");

	ChatDialog* pChatDlg = new ChatDialog(_T("bg0.png"), 0x00000000, myselft_info, friend_info);//����Ӧ�ó��򴰿������
	if( pChatDlg == NULL ) 
		return 0;
	pChatDlg->Create(NULL, _T("ChatDialog"), UI_WNDSTYLE_DIALOG, 0);
	pChatDlg->CenterWindow();//�����ڷŵ���������
	//pChatDlg->ShowWindow(true);//��ʾ����
	////delete pChatDlg;

	CPaintManagerUI::MessageLoop();//������Ϣѭ��
	

	::CoUninitialize();//�˳������ͷ�COM��
	return 0;
}