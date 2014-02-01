/* this works because the sum of any number n and n/x must still be */
/* divisible by x. this is because the result is just (n + nx)/x. */
/* for this reason we can calculate the answer in reverse. */
#include <stdio.h>
#include <math.h>
int main (int argc, const char *argv [])
{
    int n, cost;
    if (argc != 2)
    {
        puts ("please enter an input file argument.");
        return 1;
    }
    FILE *fin = fopen (argv [1], "r");
    fscanf (fin, "%d", &n);
    fclose (fin);
    cost = 0;
    while (n > 1)
    {
        int fact;
        for (fact = 2; fact <= n && n % fact != 0; fact++) ;
        if (fact < n && n % fact == 0)
        {
            int x = n / fact;
            n -= x;
            cost += n / x;
        }
        else
        {
            n--;
            cost += n;
        }
    }
    printf ("%d\n", cost);
    return 0;
}
