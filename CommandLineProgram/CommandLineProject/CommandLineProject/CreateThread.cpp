#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define MAX_THREADS (1024*10)

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	DWORD threadNum = (DWORD)lpParam;

	while (1)

	{
		_tprintf(_T("tread num: %d\n"), threadNum);
		Sleep(1000);
	}

	return 0;
}

DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	while (1)
	{
		hThread[cntOfThread] = CreateThread(NULL, 0, ThreadProc, (LPVOID)cntOfThread, 1024*1024*1024, &dwThreadID[cntOfThread]);

		if (hThread[cntOfThread] == NULL)
		{
			_tprintf(_T("MAXIMUM THREAD NUMBER: %d\n"), cntOfThread);
			break;
		}
		cntOfThread++;
	}

	for (DWORD i = 0; i < cntOfThread; i++)
	{
		CloseHandle(hThread[i]);
	}

	_tprintf(_T("MAXIMUM THREAD NUMBER: %d\n"), cntOfThread);
	return 0;
}