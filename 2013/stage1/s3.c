// brute force copy pasted loop method
#include <stdio.h>
#include <stdlib.h>
int main (int argc, const char *argv [])
{
    int i, j, k, l, m, n, o;
    int team, games, wins;
    int played [4] [4] = { {  0, -1, -1, -1 }, { -1,  0, -1, -1 },
                           { -1, -1,  0, -1 }, { -1, -1, -1,  0 } };
    int outcome [2] [3] = { { 1, 0, 3 }, { 1, 3, 0 } };
    int score [4] = { 0, 0, 0, 0 };
    if (argc != 2)
    {
        puts ("please enter an input file argument.");
        return 1;
    }
    FILE *fin = fopen (argv [1], "r");
    fscanf (fin, "%d\n%d", &team, &games);
    team--;
    wins = 0;
    for (i = 0; i < games; i++)
    {
        int A, B, SA, SB;
        fscanf (fin, "\n%d %d %d %d", &A, &B, &SA, &SB);
        A--;
        B--;
        if (SA == SB)
        {
            score [A] += 1;
            score [B] += 1;
            played [A] [B] = played [B] [A] = 1;
        }
        if (SA < SB)
        {
            score [B] += 3;
            played [A] [B] = 0;
            played [B] [A] = 3;
        }
        else
        {
            score [A] += 3;
            played [A] [B] = 3;
            played [B] [A] = 0;
        }
    }
    for (i = 0; i < 3; i++)
    {
        if (played [0] [1] == -1)
        {
            score [0] += outcome [0] [i];
            score [1] += outcome [1] [i];
        }
        else if (outcome [0] [i] != played [0] [1])
            continue;
        for (j = 0; j < 3; j++)
        {
            if (played [0] [2] == -1)
            {
                score [0] += outcome [0] [j];
                score [2] += outcome [1] [j];
            }
            else if (outcome [0] [j] != played [0] [2])
                continue;
            for (k = 0; k < 3; k++)
            {
                if (played [0] [3] == -1)
                {
                    score [0] += outcome [0] [k];
                    score [3] += outcome [1] [k];
                }
                else if (outcome [0] [k] != played [0] [3])
                    continue;
                for (l = 0; l < 3; l++)
                {
                    if (played [1] [2] == -1)
                    {
                        score [1] += outcome [0] [l];
                        score [2] += outcome [1] [l];
                    }
                    else if (outcome [0] [l] != played [1] [2])
                        continue;
                    for (m = 0; m < 3; m++)
                    {
                        if (played [1] [3] == -1)
                        {
                            score [1] += outcome [0] [m];
                            score [3] += outcome [1] [m];
                        }
                        else if (outcome [0] [m] != played [1] [3])
                            continue;
                        for (n = 0; n < 3; n++)
                        {
                            if (played [2] [3] == -1)
                            {
                                score [2] += outcome [0] [n];
                                score [3] += outcome [1] [n];
                            }
                            else if (outcome [0] [n] != played [2] [3])
                                continue;
                            for (o = 0; o < 4; o++)
                                if (o != team && score [team] <= score [o])
                                    break;
                            if (o == 4)
                                wins++;
                            if (played [2] [3] == -1)
                            {
                                score [2] -= outcome [0] [n];
                                score [3] -= outcome [1] [n];
                            }
                        }
                        if (played [1] [3] == -1)
                        {
                            score [1] -= outcome [0] [m];
                            score [3] -= outcome [1] [m];
                        }
                    }
                    if (played [1] [2] == -1)
                    {
                        score [1] -= outcome [0] [l];
                        score [2] -= outcome [1] [l];
                    }
                }
                if (played [0] [3] == -1)
                {
                    score [0] -= outcome [0] [k];
                    score [3] -= outcome [1] [k];
                }
            }
            if (played [0] [2] == -1)
            {
                score [0] -= outcome [0] [j];
                score [2] -= outcome [1] [j];
            }
        }
        if (played [0] [1] == -1)
        {
            score [0] -= outcome [0] [i];
            score [1] -= outcome [1] [i];
        }
    }
    printf ("%d\n", wins);
    fclose (fin);
    return 0;
}
