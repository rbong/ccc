// needs cleaning desperately
#include <stdio.h>
#include <stdlib.h>
int s, qued;
typedef struct Student
{
    struct Student **shorter; // vector
    int visited;
    int n;
    int shortn;
} Student;
Student **vector;
Student **que;
Student *new_student (int n)
{
    Student *student = malloc (sizeof (Student));
    student->shorter = malloc (sizeof (Student *));
    student->n = n;
    student->visited = 0;
    student->shortn = 0;
    return student;
}
void insert_student (Student *shorter, Student *student)
{
    int i = ++(student->shortn);
    void *temp = realloc (student->shorter, sizeof (Student *) * i);
    student->shorter = temp;
    student->shorter [i-1] = shorter;
}
int enque (Student *student)
{
    int result = -1;
    int i, j;
    void *temp;
    qued += student->shortn;
    temp = realloc (que, sizeof (Student *) * qued);
    que = temp;
    for (i = qued - student->shortn, j = 0; i < qued; i++, j++)
    {
        que [i] = student->shorter [j];
    }
    student->visited = 1;
    return result;
}
int search (Student *student)
{
    int i;
    qued = 1;
    que = malloc (sizeof (Student *));
    que [0] = student;
    for (i = 0; i < qued; i++)
    {
        if (que [i] == vector [s])
            break;
        else if (! que [i]->visited)
            enque (que [i]);
    }
    free (que);
    if (i == qued)
        return 0;
    else
        return 1;
}
int main (int argc, const char *argv [])
{
    int i;
    int students, comparisons, s1, s2;
    if (argc != 2)
    {
        puts ("please enter an input file argument.");
        return 1;
    }
    FILE *fin = fopen (argv [1], "r");
    fscanf (fin, "%d %d", &students, &comparisons);
    vector = malloc (sizeof (Student *) * students);
    for (i = 0; i < students; i++)
        vector [i] = NULL;
    for (i = 0; i < comparisons; i++)
    {
        int x, y;
        fscanf (fin, "\n%d %d", &x, &y);
        x--;
        y--;
        if (vector [x] == NULL)
            vector [x] = new_student (x);
        if (vector [y] == NULL)
            vector [y] = new_student (y);
        insert_student (vector [y], vector [x]);
    }
    fscanf (fin, "\n%d %d", &s1, &s2);
    s1--;
    s2--;
    fclose (fin);
    if (vector [s1] == NULL || vector [s2] == NULL)
        puts ("unknown");
    else
    {
        s = s2;
        if (search (vector [s1]))
            puts ("yes");
        else
        {
            s = s1;
            for (i = 0; i < students; i++)
            {
                if (vector [i] != NULL)
                    vector [i]->visited = 0;
            }
            if (search (vector [s2]))
                puts ("no");
            else
                puts ("unknown");
        }
    }
}
