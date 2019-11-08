#include "pch.h"
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(void)
{
	multiset<int> a;
	vector<int> arr = { 2, 3, 4, 2, 3, 6, 8, 4, 5 };
	for(int i=0; i<arr.size(); i++)
		a.insert(arr[i]);
	multiset<int>::iterator iter;
	for (iter = a.begin(); iter != a.end(); iter++)
		cout << *iter << " ";
	cout << endl;

	int n = 0;
	int idx = 0;
	for (iter = a.begin(), idx = 0; idx <= arr.size() / 2; iter++, idx++)
		;		
	n = *iter;
	cout << n << endl;
	return 0;
}


