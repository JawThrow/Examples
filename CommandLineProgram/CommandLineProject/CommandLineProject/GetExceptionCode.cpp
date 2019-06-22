#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR *argv[])
{
	int *p = NULL;
	int sel = 0;

	while (1)
	{
		_tprintf(_T("1 for memory access exception\n"));
		_tprintf(_T("2 for divide by 0 exception\n"));
		_tprintf(_T("select exception type(3 for exit)\n"));

		_tscanf(_T("%d"), &sel);

		if (sel == 3)
			break;

		__try
		{
			if(sel == 1)
			{
				*p = 100;
				_tprintf(_T("value : %d \n"), *p);
			}
			else
			{
				int n = 0;
				n = 7 / n;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			DWORD exptType = GetExceptionCode();
			switch (exptType)
			{
			case EXCEPTION_ACCESS_VIOLATION:
				_tprintf(_T("Access violation \n\n"));
				break;
			case EXCEPTION_INT_DIVIDE_BY_ZERO:
				_tprintf(_T("Divide by zero\n\n"));
				break;
			}
		}
	}

	return 0;
}