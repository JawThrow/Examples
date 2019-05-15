#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0. };
	STARTUPINFO si2 = { 0, };
	si.cb = sizeof(si);
	si2.cb = sizeof(si2);

	PROCESS_INFORMATION pi;
	PROCESS_INFORMATION pi2;
	DWORD return_val1;
	DWORD return_val2;
	TCHAR command[50] = _T("PartAdder.exe 1 5");
	TCHAR command2[50] = _T("PartAdder.exe 6 10");
	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);
	GetExitCodeProcess(pi.hProcess, &return_val1);
	if (return_val1 == -1)
	{
		_fputts(_T("PartAdder return -1!\n"), stdout);
		return 1;
	}
	
	CreateProcess(NULL, command2, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);
	GetExitCodeProcess(pi.hProcess, &return_val2);
	if (return_val2 == -1)
	{
		_fputts(_T("PartAdder return -1!\n"), stdout);
		return 1;
	}
	
	DWORD sum = return_val1 + return_val2;

	_tprintf(_T("sum : %d\n"), sum);


	return 0;
	
	
	
}