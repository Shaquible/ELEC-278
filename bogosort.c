#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool is_sorted(int *a, int n)
{
    while (--n >= 1)
    {
        if (a[n] < a[n - 1])
            return false;
    }
    return true;
}

void shuffle(int *a, int n)
{
    int i, t, r;
    for (i = 0; i < n; i++)
    {
        t = a[i];
        r = rand() % n;
        a[i] = a[r];
        a[r] = t;
    }
}

int bogosort(int *a, int n)
{
    int i = 0;
    while (!is_sorted(a, n))
    {
        shuffle(a, n);
        i++;
    }
    return i;
}

int main()
{
    srand(time(0));
    int numbers[] = {1, 10, 9, 7, 3};
    int i;
    int j;
    j = bogosort(numbers, 5);
    for (i = 0; i < 6; i++)
        printf("%d ", numbers[i]);
    printf("\n");
    printf("took %i sorts \n", j);
}