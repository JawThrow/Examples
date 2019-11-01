// Doodle.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>

void swap_pij(int*arr, int i, int j);
void qsort_pij(int* arr, int left, int right);

int main()
{
	int arr[10] = { 10, 6, 7, 9, 3, 4, 2, 1, 5, 8 };
	for (int idx = 0; idx < 10; idx++)
		printf("%d ", arr[idx]);
	printf("\n");
	qsort_pij(arr, 0, 9);
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
	if (left > right)
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
	
	for (int idx = 0; idx < 10; idx++)
		printf("%d ", arr[idx]);
	printf("\n");
	
	qsort_pij(arr, left, j - 1);
	qsort_pij(arr, j + 1, right);
	return;
}
