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
    if(l >= r)
        return;

    int start = l;
    int end = r;
    int pivot_idx = (l+r)/2;
    int pivot = A[pivot_idx];
    while(l < r)
    {
        while(A[l] < pivot && l < end)
            l++;
        while(A[r] > pivot && r > start)
            r--;        
        swap(A, l, r);                
        l++;
        r--;
    }

    quick_sort(A, start, l-1);
    quick_sort(A, l, end);
}


void sort(int A[], int N)
{
    int start = 0;
    int end = N;
    
    quick_sort(A, start, end-1);
}

int main(void)
{
    int A[5] = {1,1,1,1,1};
    int N = sizeof(A)/sizeof(int);
    sort(A, N);    

    return 0;
}