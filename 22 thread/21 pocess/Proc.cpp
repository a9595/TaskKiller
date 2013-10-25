#include "Proc.h"

ProcDlg* ProcDlg::ptr = NULL;

ProcDlg::ProcDlg(void)
{
	ptr = this;
}

void ProcDlg::Cls_OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
	PostQuitMessage(0);
}

BOOL ProcDlg::Cls_OnInitDialog(HWND hWnd, HWND hwndFocus, LPARAM lParam) 
{
	hDialog = hWnd;
	hUpdate = GetDlgItem(hDialog, IDC_UPDATE);
	hEdit = GetDlgItem(hDialog, IDC_EDIT1);
	hList = GetDlgItem(hDialog, IDC_LIST1);
	hThread = GetDlgItem(hDialog, IDC_LIST2);
	ProcessList();
	return TRUE;
}
void ProcDlg::ThreadList(int index2)
{
	TCHAR threadName[40];
	HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

	PROCESSENTRY32 pe32;
	THREADENTRY32 th32;
	memset(&pe32, 0, sizeof(PROCESSENTRY32));
	memset(&th32, 0, sizeof(THREADENTRY32));
	pe32.dwSize=sizeof(PROCESSENTRY32);
	th32.dwSize=sizeof(THREADENTRY32);
	SendMessage(hThread, LB_RESETCONTENT, 0, 0);
	//if(Process32First(hSnapShot, &pe32))
	//{
	//	if(base[index2] == pe32.th32ProcessID)
	//	{
	//		Thread32First(hSnapShot, &th32);
	//		{
	//			wsprintf(threadName, TEXT("%d"),th32.th32ThreadID);
	//			SendMessage(hThread, LB_ADDSTRING, 0, LPARAM(threadName));
	//		}
	//		while(Thread32Next(hSnapShot, &th32) )
	//		{
	//			wsprintf(threadName, TEXT("%d"),th32.th32ThreadID);
	//			SendMessage(hThread, LB_ADDSTRING, 0, LPARAM(threadName));	
	//		}
	//	}

	//	while(Process32Next(hSnapShot, &pe32))
	//	{
	//		if(base[index2] != pe32.th32ProcessID)
	//			continue;

			BOOL success = Thread32First(hSnapShot, &th32);
			/*wsprintf(threadName, TEXT("%d"),th32.th32ThreadID);
			SendMessage(hThread, LB_ADDSTRING, 0, LPARAM(threadName));*/

			while(success)
			{
				if (th32.th32OwnerProcessID == base[index2])
				{
					wsprintf(threadName, TEXT("%d"),th32.th32ThreadID);
					SendMessage(hThread, LB_ADDSTRING, 0, LPARAM(threadName));	
				}
				success = Thread32Next(hSnapShot, &th32);
			}	
	//	}
	//}
}
void ProcDlg::ProcessList()
{
	TCHAR procName[40];
	HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe32;
	memset(&pe32, 0, sizeof(PROCESSENTRY32));
	pe32.dwSize=sizeof(PROCESSENTRY32);
	base.clear();
	if(Process32First(hSnapShot, &pe32))
	{
		base.push_back(pe32.th32ProcessID);
		wsprintf(procName, TEXT("%s"),pe32.szExeFile);
		SendMessage(hList, LB_ADDSTRING, 0, LPARAM(procName));
		while(Process32Next(hSnapShot, &pe32))
		{
			base.push_back(pe32.th32ProcessID);
			wsprintf(procName, TEXT("%s  %d"),pe32.szExeFile, pe32.th32ProcessID);
			SendMessage(hList, LB_ADDSTRING, 0, LPARAM(procName));		
		}
	}
}
void ProcDlg::Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	int index;
	if(id ==  IDC_UPDATE || id == ID_UPDATE)
	{
		SendMessage(hList, LB_RESETCONTENT, 0, 0);
		ProcessList();
	}
	if(id == IDC_KILL || id == ID_KILL)
	{
		index = SendMessage(hList, LB_GETCURSEL, 0, 0);
		if(index != LB_ERR)
		{
			TerminateProcess(OpenProcess(PROCESS_TERMINATE, false, base[index]), 0);
		}
		SendMessage(hList, LB_RESETCONTENT, 0, 0);
		ProcessList();
	}
	if(id == IDC_LIST1 && codeNotify == LBN_SELCHANGE)
	{
		index = SendMessage(hList, LB_GETCURSEL, 0, 0);
		ThreadList(index);
	}

	/*if(id == IDC_LIST1 && codeNotify == LBN_SELCHANGE)
	{
	MessageBox(hWnd, TEXT("good"), 0, MB_OK | MB_ICONWARNING);
	}*/

	/// ==
	/*if(LOWORD(wParam) == IDC_LIST1 && message == LBN_SELCHANGE)
	{
	MessageBox(hWnd, TEXT("good"), 0, MB_OK | MB_ICONWARNING);
	}*/
	if(id == IDC_CREATE || id == ID_CREATE)
	{
		STARTUPINFO sui;   
		PROCESS_INFORMATION pi; 
		memset(&sui, 0, sizeof(STARTUPINFO));
		sui.cb=sizeof(STARTUPINFO);

		TCHAR* strNewProcessName = new TCHAR [256];
		GetWindowText(hEdit, strNewProcessName, 256);

		BOOL bOk=CreateProcess(NULL, strNewProcessName,  NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &sui, &pi);
		if(!bOk)
		{
			MessageBox(hWnd, TEXT("Вкажіть правильний шлях до процесса"), TEXT("Помилка створення процесса"), MB_OK | MB_ICONWARNING);
		}
		SendMessage(hList, LB_RESETCONTENT, 0, 0);
		ProcessList();
		delete [] strNewProcessName;
	}
}

BOOL CALLBACK ProcDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}