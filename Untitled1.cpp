#include <TXLib.h>
#include <stdio.h>
#include <math.h>

const double EPS = 0.001;

enum Compare
{
    EQUAL_TO_ZERO = 0,
    GREATER_THEN_ZERO = 1,
    LOWER_THAN_ZERO = -1,
};

enum KolvoResh
{
    INF = -1,
    ONE_ROOTS = 1,
    NO_ROOTS = 0,
    TWO_ROOTS = 2,
};

struct Coeffs
{
    double a;
    double b;
    double c;
};

struct Roots
{
  double x1;
  double x2;
  int nRoots;
};

void OutputSolution (Roots solution);

void InputCoeffs (Coeffs* coeffs);

int SolveSquare (Coeffs coeffs, Roots* solution);

int RT (double a, double b, double c, double x1e, double x2e, int nRootsE, int nTest);

int CheckCoeffs (Coeffs coeffs);

int CompareOnZero (double compare);

int main()
{
    Coeffs coeffs;
    Roots solution;

    InputCoeffs(&coeffs);
    //RT(a, b, c, x1e, x2e, nRootsE, nTest
    solution.nRoots = SolveSquare(coeffs,  &solution);
    OutputSolution(solution);

    return 0;
}

int SolveSquare(Coeffs coeffs, Roots* solution)

{
    assert (solution != NULL);

    if (CompareOnZero(coeffs.a) == 0)
    {
        if (CompareOnZero(coeffs.b) == 0)
        {
            return (CompareOnZero(coeffs.c) == 0)? INF : 0;
        }
        else
        {
        solution->x1 = -coeffs.c/coeffs.b;
        return ONE_ROOTS;
        }
    }
    else
    {
        double d = coeffs.b * coeffs.b - 4 * coeffs.a *coeffs.c;
        if (d < EPS||d > (-EPS))
        {
            solution->x1 = -coeffs.b/(2*coeffs.a);

            return ONE_ROOTS;
        }
        else if (d > EPS)
        {
            solution->x1 = (-(coeffs.b) + sqrt(d))/(2*coeffs.a);
            solution->x2 = (-(coeffs.b) - sqrt(d))/(2*coeffs.a);

             return TWO_ROOTS;
        }
        else if (d < -EPS)
        {
            return NO_ROOTS;
        }
    }
}

void OutputSolution (Roots solution)
{
    switch (solution.nRoots)
    {
        case NO_ROOTS:
            printf("Нет решений");
            break;
        case ONE_ROOTS:
            printf("x = %lg", solution.x1);
            break;
        case TWO_ROOTS:
            printf("x1 = %lg\nx2 = %lg", solution.x1, solution.x2);
            break;
        case INF:
            printf("любое число");
            break;
        default:
            printf("error %d", solution.nRoots);
            break;

    }
}

void InputCoeffs(Coeffs* coeffs)
{
    assert (coeffs != NULL);
    while (true){
        printf("Введите коэффиценты:\n");

        if (scanf("%lg %lg %lg", &coeffs->a, &coeffs->b, &coeffs->c) != 3)
        {

            while (getchar() != '\n'){};
            printf("Неверное значение\n");
            continue;
        }

        if ( CheckCoeffs (*coeffs) == 1)
        {
            continue;
        }

        break;
    }
}

int CheckCoeffs (Coeffs coeffs)
{
    if (!isfinite(coeffs.a)||!isfinite(coeffs.b)||!isfinite(coeffs.c))
    {
        return 1;
    }

    return 0;
}

int CompareOnZero (double compare)
{
    if (compare < EPS && compare >(-EPS))
    {
        return EQUAL_TO_ZERO;
    }
    else if (compare > EPS)
    {
        return GREATER_THEN_ZERO;
    }
    else if (compare < EPS)
    {
        return LOWER_THAN_ZERO;
    }
}
