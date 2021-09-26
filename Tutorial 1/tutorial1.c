#include <stdio.h>
int find_and_replace(int *p, int len, int find, int replacewith)
{
    for (int i = 0; i < len; i++)
    {
        if (*p == find)
        {
            *p = replacewith;
        }
        p++;
    }
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    int *p = arr;
    int len = 5;
    find_and_replace(p, len, 3, 8);
    for (int i = 0; i < len; i++)
    {
        printf("%i\n", arr[i]);
    }
}