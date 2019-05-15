#include <stdio.h>
#include <tchar.h>
#include <windows.h>


int _tmain(int argc, TCHAR* argv[])
{
	if (argc != 3)
		return -1;

	DWORD num1 = _ttoi(argv[1]);
	DWORD num2 = _ttoi(argv[2]);

	//DWORD sum = (num1 + num2) * ((num2-num1)/ 2);
	DWORD sum = 0;
	for (DWORD i = num1; i <= num2; i++)
		sum += i;

	
	return sum;
}