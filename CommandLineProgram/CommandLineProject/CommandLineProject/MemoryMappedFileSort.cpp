#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void SortIntData(int* pSortArr, int num);

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hFile = CreateFile(_T("data.dat"), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		_tprintf(_T("Could not open file\n"));

	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 1024 * 10, NULL);
	if (hMapFile == NULL)
		_tprintf(_T("Could not create map of file\n"));

	int *pWrite = (int*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pWrite == NULL)
		_tprintf(_T("Could not map view of file.\n"));

	pWrite[0] = 'a';
	pWrite[1] = 'h';
	pWrite[2] = 'b';
	pWrite[3] = 'd';
	pWrite[4] = 'c';
	pWrite[5] = 'f';
	pWrite[6] = 'g';
	pWrite[7] = 'h';
	pWrite[8] = 'i';

	SortIntData(pWrite, 9);

	_tprintf(_T("%d %d %d \n"), pWrite[0], pWrite[1], pWrite[2]);
	_tprintf(_T("%d %d %d \n"), pWrite[3], pWrite[4], pWrite[5]);
	_tprintf(_T("%d %d %d \n"), pWrite[6], pWrite[7], pWrite[8]);

	UnmapViewOfFile(pWrite);
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	_tprintf(_T("End of process\n"));

	return 0;
}

void SortIntData(int* pSortArr, int num)
{
	int temp;

	for(int i=0; i<num-1; i++)
	{
		for (int j = 1; j < num; j++)
		{
			if (pSortArr[j - 1] > pSortArr[j])
			{
				temp = pSortArr[j];
				pSortArr[j] = pSortArr[j - 1];
				pSortArr[j - 1] = temp;
			}
		}
	}
}