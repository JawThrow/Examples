#include "pch.h"
#include <iostream>
#include <vector>


using namespace std;

int N;
void powerset(int k, vector<bool>& flags, vector<char>& s)
{
	if (k == N)
	{
		for (int i = 0; i < N; i++)
			if (flags[i])
				cout << s[i];
		cout << endl;
		return;
	}

	flags[k] = false;
	powerset(k + 1, flags, s);
	flags[k] = true;
	powerset(k + 1, flags, s);

}

int main(void)
{
	
	N = 4;
	vector<bool> flags(N, 0);
	vector<char> s = { 'a', 'b', 'c', 'd' };
	powerset(0, flags, s);

	return 0;	
}