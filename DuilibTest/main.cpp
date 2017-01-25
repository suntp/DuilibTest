#include "adder_Calc.h"
#include "chat_dialog.hpp"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	HRESULT Hr = ::CoInitialize(NULL);//初始化COM库, 为加载COM库提供支持
	if( FAILED(Hr) ) 
		return 0;

	CPaintManagerUI::SetInstance(hInstance);//设置程序实例

	//实例句柄与渲染类关联,获得皮肤文件目录（加载皮肤文件在OnCreate之中）
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin\\adderCalc"));
	//CAdderCalc* pAppCalc = new CAdderCalc();//创建应用程序窗口类对象
	//if( pAppCalc == NULL ) 
	//	return 0;
	//pAppCalc->Create(NULL, _T("AdderCalc"), UI_WNDSTYLE_DIALOG, 0);
	//pAppCalc->CenterWindow();//将窗口放到桌面中央
	//pAppCalc->ShowWindow(true);//显示窗口

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

	ChatDialog* pChatDlg = new ChatDialog(_T("bg0.png"), 0x00000000, myselft_info, friend_info);//创建应用程序窗口类对象
	if( pChatDlg == NULL ) 
		return 0;
	pChatDlg->Create(NULL, _T("ChatDialog"), UI_WNDSTYLE_DIALOG, 0);
	pChatDlg->CenterWindow();//将窗口放到桌面中央
	//pChatDlg->ShowWindow(true);//显示窗口
	////delete pChatDlg;

	CPaintManagerUI::MessageLoop();//进入消息循环
	

	::CoUninitialize();//退出程序并释放COM库
	return 0;
}