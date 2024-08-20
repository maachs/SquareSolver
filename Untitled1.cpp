#include <TXLib.h>
#include <stdio.h>
#include <math.h>

const int INF = -1;
int output (int nRoots, double x1, double x2);
int input (double* a, double* b, double* c);
int SolveSquare(double a, double b, double c, double* x1, double* x2);

int main()
{
    double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    input(&a, &b, &c);
    assert (isfinite(a));
    assert (isfinite(b));
    assert (isfinite(c));

    int nRoots = SolveSquare(a, b, c, &x1, &x2);
     output (nRoots, x1 ,x2);




}

int SolveSquare(double a, double b, double c, double* x1, double* x2)

{

    if (a == 0){
        if (b == 0){
            return (c == 0)? INF : 0;
        }
        *x1 = -c/b;
        return 1;
    } else {

        double d = b * b - 4 * a *c;
        if (d > 0){
            *x1 = (-b + sqrt(d))/(2*a);
            *x2 = (-b - sqrt(d))/(2*a);
            }
            else {
            return 0;
            }
        return 2;
    }
}
int output (int nRoots, double x1, double x2)
{
switch (nRoots)
    {
        case 0:
            printf("Нет решений");
            break;
        case 1:
            printf("x = %lg", x1);
            break;
        case 2:
            printf("x1 = %lg\nx2 = %lg", x1, x2);
            break;
        case INF:
            printf("любое число");
            break;
        default:
            printf("error %d", nRoots);
            break;
            return 1;
    }
}

int input (double* a, double* b, double* c)
{

    scanf("%lg %lg %lg", a, b, c);

}

