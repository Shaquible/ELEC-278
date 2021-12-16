#include <stdio.h>
#include <stdlib.h>
int find_duplicates(int *pa, int k, int m)
{
    int num_dups = 0;
    int *arr = (int *)(malloc(sizeof(int) * m));
    for (int i = 0; i < m; i++)
    {
        arr[i] = 1;
    }
    for (int i = 0; i < k; i++)
    {
        if (arr[pa[i]] >= 0)
            arr[i] = -1;
        else
            num_dups++;
    }
    return num_dups;
}

int main(void)
{
    int arr[] = {0, 1, 2, 2, 4, 4, 5, 5, 6};
    printf("%i", find_duplicates(arr, 9, 7));
}