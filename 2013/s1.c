#include <stdio.h>
int main ()
{
    int temp;
    int year;
    FILE *fin = fopen ("s1.15.in", "r");
    fscanf (fin, "%d", &year);
    if (year < 0 || 10000 < year)
        return 1;
    do
    {
        year++;
        int a [9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        temp = year;
        do
        {
            int digit = temp % 10;
            a [digit]++;
            if (a [digit] > 1)
                break;
        } while (temp /= 10);
        if (temp == 0)
            break;
    } while (temp != 0);
    printf ("%d\n", year);
    fclose (fin);
    return 0;
}
