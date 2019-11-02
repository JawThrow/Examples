// Doodle.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>

#define LEN  5
void swap_pij(int*arr, int i, int j);
void qsort_pij(int* arr, int left, int right);

int main()
{
	int arr[LEN] = { 2, 3, 4,2 ,3};
	for (int idx = 0; idx < LEN; idx++)
		printf("%d ", arr[idx]);
	printf("\n");
	qsort_pij(arr, 0,LEN-1);
	for (int idx = 0; idx < LEN; idx++)
		printf("%d ", arr[idx]);
	printf("\n");
}


void swap_pij(int*arr, int i, int j)
{
	int temp = 0;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void qsort_pij(int* arr, int left, int right)
{
	if (left >= right)
		return;

	int pivot = left;
	int i = left + 1;
	int j = right;

	while(i<=j)
	{
		while (i <= right && arr[i] <= arr[pivot])
			i++;
		while (j > left && arr[j] >= arr[pivot])
			j--;

		if (i > j)			
			swap_pij(arr, pivot, j);
		else
			swap_pij(arr, i, j);
	}

	qsort_pij(arr, left, j - 1);
	qsort_pij(arr, j + 1, right);
	

	/*if (left > right)
		return;

	int pivot = left;
	int i = left + 1;
	int j = right;

	while (i <= j && arr[i] <= arr[pivot])
		i++;
	while (j >= i && arr[j] >= arr[pivot])
		j--;

	if (i <= j)
		swap_pij(arr, i, j);
	else
		swap_pij(arr, pivot, j);

	qsort_pij(arr, left, j - 1);
	qsort_pij(arr, j + 1, right);*/
	return;
}
