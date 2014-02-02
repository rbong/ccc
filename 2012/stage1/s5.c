// simple pascal-like problem
#include <stdio.h>
#include <stdlib.h>
int main (int argc, const char *argv [])
{
    int i, x, y;
    FILE *fin;
    int rows, cols, cats;
    int paths [25] [25] = { 0 };
    int cc = 0;
    if (argc != 2)
    {
        puts ("please enter an input file argument");
        return 1;
    }
    fin = fopen (argv [1], "r");
    fscanf (fin, "%d%d%d", &rows, &cols, &cats);
    for (i = 0; i < cats; i++)
    {
        int catx, caty;
        fscanf (fin, "%d%d", &caty, &catx);
        caty--;
        catx--;
        paths [caty] [catx] = -1;
    }
    paths [0] [0] = 1;
    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < cols; x++)
        {
            if (paths [y] [x] == -1)
            {
                paths [y] [x] = 0;
                cc++;
                continue;
            }
            if (y == 0 && x == 0)
            {
                continue;
            }
            paths [y] [x] = 0;
            paths [y] [x] += (y == 0) ? 0 : paths [y - 1] [x];
            paths [y] [x] += (x == 0) ? 0 : paths [y] [x - 1];
        }
    }
    printf ("%d\n", paths [rows - 1] [cols - 1]);
    return 0;
}
