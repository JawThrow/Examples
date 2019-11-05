/* https://www.hackerrank.com/challenges/minimum-absolute-difference-in-an-array/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=greedy-algorithms 
Problem: Minimum Absolute Difference in an Array
Type: Greedy Algorithms
*/

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

int comp(const void* a, const void* b)
{
	int num1 = *(int*)a;
	int num2 = *(int*)b;

	if (num1 < num2)
		return -1;
	if (num1 > num2)
		return 1;
	return 0;
}

// Complete the minimumAbsoluteDifference function below.
int minimumAbsoluteDifference(int arr_count, int* arr) {

	int diff = 0;
	int mindiff = 2000000000;
	int num = 1000000000;
	int idx = 0;
	qsort(arr, arr_count, sizeof(int), comp);

	for (int i = 0; i < arr_count - 1; i++)
	{
		diff = abs(arr[i] - arr[i + 1]);
		if (diff < mindiff)
			mindiff = diff;
	}

	return mindiff;
}

int main()
{
	FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

	char* n_endptr;
	char* n_str = readline();
	int n = strtol(n_str, &n_endptr, 10);

	if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

	char** arr_temp = split_string(readline());

	int* arr = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		char* arr_item_endptr;
		char* arr_item_str = *(arr_temp + i);
		int arr_item = strtol(arr_item_str, &arr_item_endptr, 10);

		if (arr_item_endptr == arr_item_str || *arr_item_endptr != '\0') { exit(EXIT_FAILURE); }

		*(arr + i) = arr_item;
	}

	int arr_count = n;

	int result = minimumAbsoluteDifference(arr_count, arr);

	fprintf(fptr, "%d\n", result);

	fclose(fptr);

	return 0;
}

char* readline() {
	size_t alloc_length = 1024;
	size_t data_length = 0;
	char* data = (char*)malloc(alloc_length);

	while (true) {
		char* cursor = data + data_length;
		char* line = fgets(cursor, alloc_length - data_length, stdin);

		if (!line) {
			break;
		}

		data_length += strlen(cursor);

		if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
			break;
		}

		alloc_length <<= 1;

		data = (char*)realloc(data, alloc_length);

		if (!line) {
			break;
		}
	}

	if (data[data_length - 1] == '\n') {
		data[data_length - 1] = '\0';

		data = (char*)realloc(data, data_length);
	}
	else {
		data = (char*)realloc(data, data_length + 1);

		data[data_length] = '\0';
	}

	return data;
}

char** split_string(char* str) {
	char** splits = NULL;
	char* token = strtok(str, " ");

	int spaces = 0;

	while (token) {
		splits = (char**)realloc(splits, sizeof(char*) * ++spaces);

		if (!splits) {
			return splits;
		}

		splits[spaces - 1] = token;

		token = strtok(NULL, " ");
	}

	return splits;
}
