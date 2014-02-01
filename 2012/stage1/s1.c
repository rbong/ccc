#include <stdio.h>
int main (int argc, const char *argv [])
{
    int i, j, k;
    int scorer, comb;
    if (argc != 2)
    {
        puts ("please enter an input file argument.");
        return 1;
    }
    FILE *fin = fopen (argv [1], "r");
    fscanf (fin, "%d", &scorer);
    fclose (fin);
    for (comb = 0, i = 1; i < scorer; i++)
        for (j = i + 1; j < scorer; j++)
            for (k = j + 1; k < scorer; k++)
                comb++;
    printf ("%d\n", comb);
    return 0;
}
