/*this source from https://blog.encrypted.gg/732?category=773649 */
#include "pch.h"
#include <iostream>
using namespace std;

int n, m;
void func(int* arr, int k) 
{ // 현재 k개까지 수를 택했음.
	if (k == m) 
	{ // m개를 모두 택했으면
		for (int i = 0; i < m; i++) cout << arr[i] + 1 << ' '; // arr에 기록해둔 수를 출력.(0부터 m-1까지가 아니라 1부터 m까지이므로 +1을 해줌)
		cout << '\n';
		return;
	}
	int st = 0;
	if (k != 0) 
		st = arr[k - 1];
	for (int i = st; i < n; i++) 
	{ // 1부터 n까지의 수에 대해
		arr[k] = i; // k번째 수를 i로 정함
		func(arr, k + 1); // 다음 수를 정하러 한 단계 더 들어감      
	}
}
int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	int arr[m] = {};
	func(arr, 0);
}