#include "pch.h"
#include <vector>
#include <iostream>

using namespace std;

void vector_copy()
{
	vector<int> vec1 = { 1, 2, 3, 4, 5, 6, 7 };
	for (int i = 0; i < vec1.size(); i++)
	{
		vector<int> vec2;
		//copy(vec1.begin(), vec1.begin()+i, vec2);
		vec2.assign(vec1.begin(), vec1.begin() + vec1.size() - i);
		for (int j = 0; j < vec2.size(); j++)
			cout << vec2[j] << " ";
		cout << endl;
	}
}

int main(void)
{
	//vector_copy();
	int arr[5] = { 1,2,3,4,5 };
	int arr2[5] = { 0, };

	printf("%p\n", arr);
	printf("%p\n", &arr);
	printf("%p\n", &*arr);
	printf("%d\n", *&arr);
	printf("%p\n", &*(arr+0));

	memcpy(arr2, arr, sizeof(int) * 3);
	for (int i = 0; i < 5; i++)
		cout << arr2[i] << " ";
	cout << endl;
	memset(arr, 0, sizeof(int)*5);
	for (int i = 0; i < 5; i++)
		cout << arr[i] << " ";
	cout << endl;
	return 0;

}

