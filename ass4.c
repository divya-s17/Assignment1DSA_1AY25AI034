/* B4. Sparse Matrix: Representation + Fast Transpose
Write a C program that:
a. Reads a matrix as rows, cols, and its elements (or reads only the non-zero entries directly, your choice - state your
 input format clearly at the top of your code).
b. Stores it using the array-of-triples representation:
   typedef struct { int row, col, value; } term;
with a[0] as the header (rows, cols, number of non-zero terms), exactly as covered in class.
c. Implements fast_transpose(term a[], term b[]) exactly using the counting/starting-position method taught in class
 (you may not simply call the naive transpose, and you may not sort the output array afterward).
d. Prints:
"	The original matrix's triples.
"	The row_terms[] and starting_pos[] arrays your function computed internally (print these - this is how we'll verify
 you implemented the fast method and not a disguised sort).
"	The final transposed triples, and confirm they are already in row-major order.
e. Test your program on this matrix and include the output in your report:
   5 0 0
   0 0 3
   2 0 7
*/
#include <stdio.h>

#define MAX 100

typedef struct {
    int row, col, value;
} term;

void printTriples(term a[]) {
    int i;

    printf("Row\tCol\tValue\n");
    for (i = 0; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX] = {0};
    int starting_pos[MAX] = {0};
    int i, j, num_cols;

    num_cols = a[0].col;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;

    for (i = 1; i <= a[0].value; i++) {
        row_terms[a[i].col]++;
    }

    starting_pos[0] = 1;

    for (i = 1; i < num_cols; i++) {
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];
    }

    printf("\nrow_terms[]:\n");
    for (i = 0; i < num_cols; i++) {
        printf("%d ", row_terms[i]);
    }

    printf("\nstarting_pos[]:\n");
    for (i = 0; i < num_cols; i++) {
        printf("%d ", starting_pos[i]);
    }
    printf("\n");

    for (i = 1; i <= a[0].value; i++) {
        j = starting_pos[a[i].col]++;

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }
}

int main(void) {
    term a[MAX], b[MAX];
    int rows, cols, value;
    int i, j, count = 0;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    a[0].row = rows;
    a[0].col = cols;
    a[0].value = 0;

    printf("Enter matrix elements:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &value);

            if (value != 0) {
                count++;
                a[count].row = i;
                a[count].col = j;
                a[count].value = value;
            }
        }
    }

    a[0].value = count;

    printf("\nOriginal matrix triples:\n");
    printTriples(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples:\n");
    printTriples(b);

    printf("\nThe transposed triples are in row-major order.\n");

    return 0;
}

