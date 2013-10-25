//#include <Windows.h>
//#include "resource.h"
//#include <stdio.h>
//#include <tchar.h>
//#include <Tlhelp32.h>
//#include <locale.h>
//#include <conio.h>
//
//RECT wind;
//HWND hList, hEdit, hUpdate, hKill, hCreate;
//HINSTANCE hInst;
//BOOL CALLBACK DialogMessages(HWND, UINT, WPARAM, LPARAM);
//int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR CmndList, int nCmdShow)
//{
//	hInst = hInstance;
//	return DialogBox(hInstance, MAKEINTRESOURCE (IDD_DIALOG1), NULL, DialogMessages);
//}
//
//void ProcessList(HWND hwnd, INT base [])
//{
//	int count = 0;
//	TCHAR procName[40];
//	hList = GetDlgItem(hwnd, IDC_LIST1);
//
//	HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//
//	PROCESSENTRY32 pe32;
//	memset(&pe32, 0, sizeof(PROCESSENTRY32));
//	pe32.dwSize=sizeof(PROCESSENTRY32);
//	if(Process32First(hSnapShot, &pe32))
//	{
//		base [0] = pe32.th32ProcessID;
//		wsprintf(procName, TEXT("%s"),pe32.szExeFile);
//		SendMessage(hList, LB_ADDSTRING, 0, LPARAM(procName));
//		while(Process32Next(hSnapShot, &pe32))
//		{
//			count ++;
//			base [count] = pe32.th32ProcessID;
//			wsprintf(procName, TEXT("%s  %d"),pe32.szExeFile, pe32.th32ProcessID);
//			SendMessage(hList, LB_ADDSTRING, 0, LPARAM(procName));		
//		}
//	}
//}
//
//BOOL CALLBACK DialogMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	
//	INT base[256];
//	switch(message)
//	{
//	case WM_INITDIALOG:
//	wchar_t *tmp = new wchar_t[128];
//	hUpdate = GetDlgItem(hWnd, IDC_UPDATE);
//	ProcessList(hWnd, base);
//	return true;
//
//	case WM_COMMAND:
//	if(LOWORD(wParam) ==  IDC_UPDATE)
//	{
//		SendMessage(hList, LB_RESETCONTENT, 0, 0);
//		ProcessList(hWnd, base);
//	}
//	if(LOWORD(wParam) == IDC_LIST1 && message == LBN_SELCHANGE)
//	{
//		int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
//		if(index != LB_ERR);
//		{
//			TerminateProcess(OpenProcess(PROCESS_TERMINATE, false, base[index]), 0);
//		}
//	}
//	return TRUE;
//	case WM_CLOSE:
//		
//		EndDialog(hWnd, 0);
//		return true;
//
//
//	}
//	return false;
//}

#include "Proc.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	ProcDlg dlg;
	MSG msg;
	HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, ProcDlg::DlgProc);
	HACCEL hAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR1)); 
	ShowWindow(hDialog, nCmdShow);
	while(GetMessage(&msg, 0, 0, 0))
	{
		if(!TranslateAccelerator(hDialog, hAccel, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}