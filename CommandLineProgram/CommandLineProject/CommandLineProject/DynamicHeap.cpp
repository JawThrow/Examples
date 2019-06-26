#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[])
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	UINT pageSize = si.dwPageSize;

	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, pageSize * 10, pageSize * 100);
	
	int *p = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 10);

	for (int i = 0; i < 10; i++)
		p[i] = i;

	HeapFree(hHeap, 0, p);

	HeapDestroy(hHeap);

	HANDLE hDefaultHeap = GetProcessHeap();
	TCHAR* pDefault = (TCHAR*)HeapAlloc(hDefaultHeap, HEAP_NO_SERIALIZE, sizeof(TCHAR) * 30);
	_tcscpy(pDefault, _T("Default Heap!\n"));
	_tprintf(_T("%s \n"), pDefault);
	HeapFree(hDefaultHeap, HEAP_NO_SERIALIZE, pDefault);

	return 0;

}