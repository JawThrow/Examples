#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>


unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam);

typedef struct _SyncString
{
	TCHAR string[100];
	HANDLE hEvent;
	HANDLE hMutex;
} SyncString;

SyncString gSyncString;

int _tmain(int argc, TCHAR *argv[])
{
	HANDLE hThreads[2];
	DWORD dwThreadIDs[2];

	gSyncString.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	gSyncString.hMutex = CreateMutex(NULL, FALSE, NULL);

	if (gSyncString.hEvent == NULL || gSyncString.hMutex == NULL)
	{
		_fputts(_T("kernel object creation error! \n"), stdout);
		return -1;
	}

	hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, OutputThreadFunction, NULL, 0, (unsigned*)&dwThreadIDs[0]);
	hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, CountThreadFunction, NULL, 0, (unsigned*)&dwThreadIDs[1]);

	if (hThreads[0] == 0 || hThreads[1] == 0)
	{
		_fputts(_T("Thread creation error!\n"), stdout);
		return -1;
	}


	_fputts(_T("Insert string: "), stdout);
	_fgetts(gSyncString.string, 30, stdin);

	SetEvent(gSyncString.hEvent);

	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);
	CloseHandle(gSyncString.hEvent);
	CloseHandle(gSyncString.hMutex);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(gSyncString.hEvent, INFINITE);
	WaitForSingleObject(gSyncString.hMutex, INFINITE);
	_fputts(_T("Output string: "), stdout);
	_fputts(gSyncString.string, stdout);

	ReleaseMutex(gSyncString.hMutex);

	return 0;
}

unsigned int WINAPI CountThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(gSyncString.hEvent, INFINITE);
	WaitForSingleObject(gSyncString.hMutex, INFINITE);

	_tprintf(_T("output string length : %d \n"), _tcslen(gSyncString.string) - 1);

	ReleaseMutex(gSyncString.hMutex);
	return 0;
}