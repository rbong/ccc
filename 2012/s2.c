#include <stdio.h>
#include <ctype.h>
int main (int argc, const char *argv [])
{
    char s [21];
    int i;
    int total, n1, n2, r1, r2;
    int m ['X' - 'A' + 1];
    if (argc != 2)
    {
        puts ("please enter an input file argument.");
        return 1;
    }
    FILE *fin = fopen (argv [1], "r");
    fscanf (fin, "%s", s);
    fclose (fin);
    m ['I' - 'A'] =  1; m ['V' - 'A'] =   5; m ['X' - 'A'] =   10;
    m ['L' - 'A'] = 50; m ['C' - 'A'] = 100; m ['D' - 'A'] =  500; 
    m ['M' - 'A'] = 1000;
    i = total = n1 = n2 = r1 = r2 = 0;
    while (isalnum (s [i]))
    {
        n1 = s [i++] - '0';
        n1 *= (r1 = m [s [i++] - 'A']);
        if (r2 < r1)
            n2 *= -1;
        total += n2;
        r2 = r1;
        n2 = n1;
    }
    total += n2;
    printf ("%d\n", total);
    return 0;
}
