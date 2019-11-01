#include "pch.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(void)
{
	map<string, int> m1;
	m1.insert(pair<string, int>("park", 10));
	m1.insert(pair<string, int>("im", 20));
	m1.insert(pair<string, int>("jae", 30));

	map<string, int>::iterator iter;
	for (iter = m1.begin(); iter != m1.end(); iter++)
		cout << "[" << iter->first << ", " << iter->second << "]" << " ";
	cout << endl;
	return 0;
}