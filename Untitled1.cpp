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
    INF_ROOTS = -1,
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
  double x1 = NAN;
  double x2 = NAN;
  int nRoots = NAN;
};
struct ExpectedSol
{
    double x1_expected;
    double x2_expected;
    int nRoots_expected;
    int nTest;
};

void OutputSolution (Roots solution);

void InputCoeffs (Coeffs* coeffs);

void SolveSquare (Coeffs coeffs, Roots* solution);

int CheckCoeffs (Coeffs coeffs);

int CompareOnZero (double compare);

void LineSolution (Coeffs coeffs, Roots* solution);

void SquareSolution (Coeffs coeffs, Roots* solution);

int Test (Coeffs coeffs,Roots* solution, ExpectedSol* expected);

int main()
{
    Coeffs coeffs = {.a = 1,.b = 2,.c = 1};

    Roots solution = {};

    ExpectedSol expected = {-1,-1,1,1};

    //InputCoeffs(&coeffs);
    SolveSquare(coeffs,  &solution);
    Test (coeffs, &solution, &expected);
    //OutputSolution(solution);

    return 0;
}

void SolveSquare(Coeffs coeffs, Roots* solution)

{
    assert (solution != NULL);

    if (CompareOnZero(coeffs.a) == 0)
    {
          LineSolution (coeffs, solution);

    }
    else
    {
         SquareSolution (coeffs, solution);
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
        case INF_ROOTS:
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
    if (fabs(compare) < EPS)
    {
        return EQUAL_TO_ZERO;
    }
    else if (compare > EPS)
    {
        return GREATER_THEN_ZERO;
    }
    // (compare < -EPS)

    return LOWER_THAN_ZERO;
}

void LineSolution (Coeffs coeffs, Roots* solution)
{

        if (CompareOnZero(coeffs.b) == 0)
        {
            if (CompareOnZero(coeffs.c) == 0)
            {
                  solution->nRoots = INF_ROOTS;
            }
            else
            {
                solution->nRoots = NO_ROOTS;
            }
        }
        else
        {
            solution->x1 = -coeffs.c/coeffs.b;
            solution->nRoots = ONE_ROOTS;
        }


}

void SquareSolution (Coeffs coeffs, Roots* solution)
{
    double d = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs. c;

    if (CompareOnZero(d) == 1)
    {
        solution->x1 = (-(coeffs.b) + sqrt(d))/(2*coeffs.a);
        solution->x2 = (-(coeffs.b) - sqrt(d))/(2*coeffs.a);
        solution->nRoots = TWO_ROOTS;
    }
    else if (CompareOnZero(d) == 0)
    {
        solution->x1 = solution->x2 = (-coeffs.b)/(2*coeffs.a);
        solution->nRoots = ONE_ROOTS;
    }
    else if (CompareOnZero(d) == -1)
    {
        solution->nRoots = NO_ROOTS;
    }
}

int Test (Coeffs coeffs,Roots* solution, ExpectedSol* expected )
{
    double delta_x1 = fabs((*solution).x1 - (*expected).x1_expected);
    double delta_x2 = fabs((*solution).x2 - (*expected).x2_expected);
    if ((*solution).nRoots != (*expected).nRoots_expected||CompareOnZero(delta_x1) != 0||CompareOnZero(delta_x2) != 0)
    {
        printf("Error: Test %d\n  a = %lg b = %lg c = %lg\n  x1 = %lg x2 = %lg nRoots = %d\n"
               "Expected: x1 = %lg x2 = %lg nRoots = %d",
               (*expected).nTest, coeffs.a, coeffs.b, coeffs.c, (*solution).x1, (*solution).x2, (*solution).nRoots,
               (*expected).x1_expected, (*expected).x2_expected, (*expected).nRoots_expected);
    }
    else
    {
        printf ("Test %d Completed Succesfull",(*expected).nTest);
    }
}

