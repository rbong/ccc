#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
typedef struct Num
{
    unsigned int n : 23;
    unsigned int steps : 6;
} Num;
int main (int argc, const char *argv [])
{
    int i, j, k;
    int ops, digits, quelen, values;
    int digit [10];
    FILE *fin;
    if (argc != 2)
    {
        puts ("please enter an input file argument.");
        return 1;
    }
    fin = fopen (argv [1], "r");
    fscanf (fin, "%d%d", &ops, &digits);
    for (i = 0; i < digits; i++)
        fscanf (fin, "%d", &(digit [i]));
    fscanf (fin, "%d", &values);
    for (i = 0; i < values; i++)
    {
        int value;
        Num **que;
        Num *qued;
        fscanf (fin, "%d", &value);
        que = malloc (sizeof (Num *) * (digits + 1));
        for (quelen = 0; quelen < digits; quelen++)
        {
            que [quelen] = malloc (sizeof (Num));
            que [quelen]->n = digit [quelen];
            que [quelen]->steps = 0;
        }
        qued = NULL;
        while (quelen > 0)
        {
            qued = que [--quelen];
            if (qued->n == value && qued->steps == ops)
                break;
            if (qued->steps < ops && qued->n < value)
                for (j = 0; j < digits; j++)
                {
                    int n;
                    Num *num1, *num2;
                    n = digit [j];
                    num1 = malloc (sizeof (Num));
                    num1->n = qued->n + n;
                    num2 = malloc (sizeof (Num));
                    num2->n = qued->n * n;
                    num1->steps = qued->steps + 1;
                    num2->steps = num1->steps;
                    quelen += 2;
                    Num **temp = realloc (que, sizeof (Num *) * quelen + 1);
                    que = temp;
                    que [quelen - 2] = num1;
                    que [quelen - 1] = num2;
                }
            free (qued);
            qued = NULL;
        }
        if (qued != NULL)
            puts ("Y");
        else
            puts ("N");
    }
    return 0;
}
