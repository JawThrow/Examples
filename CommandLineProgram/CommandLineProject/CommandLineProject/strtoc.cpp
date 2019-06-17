#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR string[] = _T("Hey, get a life!")
		_T("You done't even have two pennies to rub together!");

	TCHAR seps[] = _T(" ,.!");

	TCHAR * token = _tcstok(string, seps);

	while (token != NULL)
	{
		_tprintf(_T(" %s\n"), token);
		token = _tcstok(NULL, seps);
	}

	return 0;
}