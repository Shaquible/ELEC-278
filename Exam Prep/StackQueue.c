#include <stdlib.h>
#include <stdio.h>

int Qisnotempty(void);

int Qstore(int val);

int Qfetch(int *pval);

int StackCount;

void StackInit(void)
{
    StackCount = 0;
}

int Stackisnotempty(void)
{
    return Qisnotempty();
}

int Stackpush(int val)
{
    if (Stackisnotempty() == 0)
    {
        Qstore(val);
        StackCount++;
        return 1;
    }

    Qstore(val);
    for (int i = 0; i < StackCount; i++)
    {
        int *pval;
        if (Qfetch(pval) == 0)
            return 0;
        if (Qstore(*pval) == 0)
            return 0;
    }
    StackCount++;
    return 1;
}

int StackPop(int *pval)
{
    return Qfetch(pval);
}