/* Dynamic Student Record System 
Design a struct Student with fields: roll_no (int), name (char[20]), marks (float).
Write a C program that:
a. Asks the user for n (number of students), and dynamically allocates an array of n Student structures using malloc.
b. Reads all n records from the user.
c. Computes and prints the average marks, and the record of the student with the highest marks, using a pointer to traverse the array (not array-indexing — use pointer arithmetic, e.g. (ptr + i)).
d. Frees the allocated memory before exiting.
e. If n changes at runtime (ask the user if they want to add 2 more students), use realloc to grow the array without losing existing data*/




#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int roll_no;
    char name[20];
    float marks;
};

int main()
{
    struct Student *ptr, *temp;
    int n, i;
    float sum = 0, average;
    int topper = 0;
    char choice;
    printf("Enter number of students: ");
    scanf("%d", &n);

    ptr = (struct Student *)malloc(n * sizeof(struct Student));

    if (ptr == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f",
              &(ptr + i)->roll_no,
              (ptr + i)->name,
              &(ptr + i)->marks);
    }

    for (i = 0; i < n; i++)
    {
        sum += (ptr + i)->marks;

        if ((ptr + i)->marks > (ptr + topper)->marks)
        {
            topper = i;
        }
    }

    average = sum / n;

    printf("\nAverage marks: %.2f\n", average);

    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           (ptr + topper)->name,
           (ptr + topper)->roll_no,
           (ptr + topper)->marks);

    printf("\nAdd 2 more students? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y')
    {
        temp = (struct Student *)realloc(
            ptr, (n + 2) * sizeof(struct Student));

        if (temp == NULL)
        {
            printf("Memory reallocation failed!\n");
            free(ptr);
            return 1;
        }

        ptr = temp;

        for (i = n; i < n + 2; i++)
        {
            printf("Enter roll, name, marks: ");
            scanf("%d %19s %f",
                  &(ptr + i)->roll_no,
                  (ptr + i)->name,
                  &(ptr + i)->marks);
        }

        n = n + 2;

        sum = 0;
        topper = 0;

        for (i = 0; i < n; i++)
        {
            sum += (ptr + i)->marks;

            if ((ptr + i)->marks > (ptr + topper)->marks)
            {
                topper = i;
            }
        }

        average = sum / n;

        printf("\nUpdated average marks: %.2f\n", average);

        printf("Updated topper: %s (Roll %d, Marks %.2f)\n",
               (ptr + topper)->name,
               (ptr + topper)->roll_no,
               (ptr + topper)->marks);
    }

    free(ptr);

    return 0;
}
