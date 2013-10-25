#pragma once
#include "header.h"

class ProcDlg
{
public:
	ProcDlg(void);
public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static ProcDlg* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void ProcessList();
	void ThreadList(int index2);
	RECT wind;
	HWND hDialog, hList, hThread, hEdit, hUpdate, hKill, hCreate;
	HINSTANCE hInst;
	vector<int> base;
	TCHAR* strNewProcessName;
};