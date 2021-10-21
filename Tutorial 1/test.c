#include <stdio.h>
void changeStr(char *str1)
{
    int i = 0;
    char *temp;
    while (*temp != '\0')
    {
        *temp = *str1;
        temp++;
        str1++;
        i++;
    }
    temp -= 1;
    for (int j = 0; j < i; j++)
    {
        *str1 = *temp;
        str1++;
        temp--;
    }
}
int main(void)
{
    char str[] = "test";
    changeStr(str);
    printf("%s", str);
}