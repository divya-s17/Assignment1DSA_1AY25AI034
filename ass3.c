/* B3. Polynomial Addition using the Array-of-Coefficients Representation
Write a C program that:
a. Reads two polynomials from the user as (degree, list of coefficients), using the representation from class:
   typedef struct {
       int   degree;
       float coef[101];   /* coef[i] = coefficient of x^(degree-i) */  /*
   } polynomial;o
b. Implements a function polynomial add(polynomial a, polynomial b) that adds them term by term (matching exponents), without using any built-in polynomial library.
c. Implements a function void display(polynomial p) that prints the polynomial in the form 3x^4 + 2x^2 + 1 (skip terms whose coefficient is 0, and handle the constant term without printing x^0).
d. Test your program on:
•	A(x) = 3x4 + 2x² + 1 and B(x) = 5x³ - 2x² + 4 ? expected output: 3x^4 + 5x^3 + 5
•	A case where the sum of two matching terms becomes exactly 0 
(make sure your output correctly omits that term).  */


#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

polynomial add(polynomial a, polynomial b)
{
    polynomial c;
    int i, max;

    max = (a.degree > b.degree) ? a.degree : b.degree;
    c.degree = max;

    for (i = 0; i <= max; i++)
    {
        float ca = (i >= max - a.degree) ? a.coef[i - (max - a.degree)] : 0;

        float cb = (i >= max - b.degree)? b.coef[i - (max - b.degree)] : 0;

        c.coef[i] = ca + cb;
    }

    return c;
}

void display(polynomial p)
{
    int i, exp, printed = 0;

    for (i = 0; i <= p.degree; i++)
    {
        float c = p.coef[i];
        exp = p.degree - i;

        if (c == 0)
            continue;

        if (printed && c > 0)
            printf(" + ");
        else if (printed && c < 0)
            printf(" - ");
        else if (c < 0)
            printf("-");

        if (c < 0)
            c = -c;

        printf("%.0f", c);

        if (exp > 1)
            printf("x^%d", exp);
        else if (exp == 1)
            printf("x");

        printed = 1;
    }

    if (!printed)
        printf("0");

    printf("\n");
}

int main()
{
    polynomial a, b, c;
    int i;

    printf("Enter degree of first polynomial: ");
    scanf("%d", &a.degree);

    printf("Enter coefficients of first polynomial "
           "from highest degree to constant:\n");

    for (i = 0; i <= a.degree; i++)
        scanf("%f", &a.coef[i]);

    printf("Enter degree of second polynomial: ");
    scanf("%d", &b.degree);

    printf("Enter coefficients of second polynomial "
           "from highest degree to constant:\n");

    for (i = 0; i <= b.degree; i++)
        scanf("%f", &b.coef[i]);

    c = add(a, b);

    printf("First polynomial: ");
    display(a);

    printf("Second polynomial: ");
    display(b);

    printf("Sum: ");
    display(c);

    return 0;
}
