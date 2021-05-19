#include <stdio.h>

void print_array(int A[], int N)
{
    for(int i=0; i<N; i++)
    {
        printf("%3d", A[i]);
    }
    printf("\n");
}

void swap(int A[], int l, int r)
{
    int temp = A[l];
    A[l] = A[r];
    A[r] = temp;
}

void quick_sort(int A[], int l, int r)
{
    if(start >= end)
        return;

    int pivot_idx = start;
    int pivot = A[pivot_idx];
    int l = start+1;
    int r = end;
    while(l <= r)
    {
        while(A[l] < pivot && l <= r)
            l++;
        while(A[r] > pivot && r >= l)
            r--;
        
        if (l < r)
        {
            swap(A, l, r);
            l++;
            r--;
        }
    }

    swap(A, pivot_idx, r);
    quick_sort(A, start, pivot_idx-1);
    quick_sort(A, pivot_idx+1, end);
}


void sort(int A[], int N)
{
    int start = 0;
    int end = N;
    
    quick_sort(A, start, end-1);
}

int main(void)
{
    int A[5] = {1,3,4,1,3};
    int N = sizeof(A)/sizeof(int);
    sort(A, N);    

    return 0;
}