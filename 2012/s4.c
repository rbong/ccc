// CCC 2012 question 4
/******************************************************************************
our array of previously taken paths is made up of 8bit ints because C has no
smaller datatype. we use basic bit fiddling to use one bit per check. there is
also a pointer que that could be dynamic, but does not need to be because the
maximum possible length of the que is not that long. The struct used to save
coin states uses 3 bits per coin & 6 bits for steps.
    completion time-
    s4.1.in finishes almost immediately
    s4.2.in finishes almost immediately
    s4.3.in finishes almost immediately
    s4.4.in < 1 second
    s4.5.in < 1 second
    worst case (reverse sorted) < 1 second
    correct in all cases
******************************************************************************/
#include <stdio.h>
#include <stdlib.h> // malloc
#include <math.h>   // pow, floor
#include <stdint.h> // uint8_t
#define SIZE 823543  // 7^7
typedef struct Set
{
    unsigned int n : 21;
    unsigned int steps : 7; // generous estimate of how much we'll need
} Set;
void set_pos (Set *set, int coin, int pos)
{
    unsigned int mask;
    mask = 7 << (3 * coin);
    pos <<= 3 * coin;
    set->n &= ~mask;
    set->n |= pos;
}
int get_pos (Set *set, int coin)
{
    unsigned int n;
    n = set->n >> (3 * coin);
    n &= 7;
    return n;
}
Set *move (Set *set, int coin, int shift)
{
    Set *new;
    new = malloc (sizeof (Set));
    new->steps = set->steps + 1;
    new->n = set->n;
    set_pos (new, coin, get_pos (set, coin) + shift);
    return new;
}
void mark (uint8_t (*map) [], int n)
{
    int index, bit;
    index = floor (n / 8.0);
    bit   = pow (2, n % 8);
    (*map) [index] |= bit;
}
int check (uint8_t (*map) [], int n)
{
    int index, bit;
    index = floor (n / 8.0);
    bit   = pow (2, n % 8);
    int result = (*map) [index] & bit;
    return result;
}
int main (int argc, const char *argv [])
{
    int coins;
    FILE *fin;
    if (argc != 2)
    {
        puts ("please enter an input file argument.");
        return 1;
    }
    fin = fopen (argv [1],  "r");
    while (fscanf (fin, "%d", &coins) > 0 && coins > 0)
    {
        int i, j;
        int quelen;
        uint8_t map [SIZE] = { 0 };
        Set **que; // vector
        Set *qued;
        que = malloc (sizeof (Set *) * SIZE);
        que [0] = malloc (sizeof (Set));
        que [0]->n = que [0]->steps = 0;
        for (i = 0; i < coins; i++)
        {
            int coin;
            fscanf (fin, "%d", &coin);
            coin--;
            set_pos (que [0], coin, i);
        }
        quelen = 1;
        for (i = 0; i < quelen; i++)
        {
            int found;
            int low [7] = { 9, 9, 9, 9, 9, 9, 9 };
            found = 0;
            qued = que [i];
            for (j = 0; j < coins; j++)
            {
                int pos;
                pos = get_pos (qued, j);
                if (low [pos] > j)
                    low [pos] = j;
                if (pos != j)
                    found = 1;
            }
            if (found == 0)
                break;
            for (j = 0; j < coins; j++)
            {
                if (j != 0 && low [j] < low [j-1])
                {
                    Set *set = move (qued, low [j], -1);
                    if (! check (&map, set->n))
                    {
                        que [quelen++] = set;
                        mark (&map, set->n);
                    }
                    else
                    {
                        free (set);
                    }
                }
                if (j != coins - 1 && low [j] < low [j+1])
                {
                    Set *set = move (qued, low [j], 1);
                    if (! check (&map, set->n))
                    {
                        que [quelen++] = set;
                        mark (&map, set->n);
                    }
                    else
                    {
                        free (set);
                    }
                }
            }
            free (qued);
            qued = NULL;
        }
        if (qued != NULL)
        {
            printf ("%d\n", qued->steps);
        }
        else
            puts ("IMPOSSIBLE");
        free (que);
    }
    return 0;
}
