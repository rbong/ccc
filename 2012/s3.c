#include <stdio.h>
int main (int argc, const char *argv [])
{
    int i;
    int sensors, f1, f2;
    int reading [1001];
    if (argc != 2)
    {
        puts ("please enter an input file argument.");
        return 1;
    }
    for (i = 0; i < 1001; i++)
        reading [i] = 0;
    FILE *fin = fopen (argv [1],  "r");
    fscanf (fin, "%d", &sensors);
    f1 = f2 = 0;
    while (sensors--)
    {
        int n;
        fscanf (fin, "\n%d", &n);
        reading [n]++;
        if (reading [n] > reading [f1] ||
                (reading [n] == reading [f1] && n > f1))
        {
            if (reading [f1] > reading [f2] ||
                    (reading [f1] == reading [f2] && f1 < f2))
                f2 = f1;
            f1 = n;
        }
        else if (reading [n] > reading [f2] ||
                (reading [n] == reading [f2] && n < f2))
            f2 = n;
    }
    printf ("%d\n", f1 - f2);
    fclose (fin);
    return 0;
}
