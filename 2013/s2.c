#include <stdio.h>
int main (int argc, const char *argv [])
{
    int W, N, T;
    int w [4] = { 0, 0, 0, 0 };
    if (argc != 2)
    {
        puts ("please enter an input file argument.");
        return 1;
    }
    FILE *fin = fopen (argv [1], "r");
    fscanf (fin, "%d\n%d", &W, &N);
    for (T = 0; N - T > 0; T++)
    {
        fscanf (fin, "\n%d", &w [3]);
        if (w [0] + w [1] + w [2] + w [3] > W)
            break;
        w [0] = w [1];
        w [1] = w [2];
        w [2] = w [3];
    }
    printf ("%d", T);
    return 0;
}
