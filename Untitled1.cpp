#include <TXLib.h>
#include <math.h>

const double EPS = 0.001;

enum Compare
{
    EQUAL_TO_ZERO = 0,
    GREATER_THAN_ZERO = 1,
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
    Coeffs coeffs;
    double x1_expected;
    double x2_expected;
    int nRoots_expected;
};

void OutputSolution (Roots solution);

void InputCoeffs (Coeffs* coeffs);

void SolveSquare (Coeffs coeffs, Roots* solution);

int CheckCoeffs (Coeffs coeffs);

int CompareOnZero (double compare);

void LineSolution (Coeffs coeffs, Roots* solution);

void SquareSolution (Coeffs coeffs, Roots* solution);

void Test (int TestNumber, Roots* solution, ExpectedSol* expected);

void AllTest ();

bool NAN_OR_INF (double check);

int main()
{
    //Coeffs coeffs = {.a = 1,.b = 2,.c = 1};
    //Roots solution = {};
    //ExpectedSol_1 expected = {1,1,NAN,1};

    //InputCoeffs(&coeffs);
    //SolveSquare (*expected_2);
    AllTest ();
    //Test (coeffs, &solution, &expected);
    //OutputSolution(solution);

    return 0;
}

void SolveSquare(Coeffs coeffs, Roots* solution)
{
    assert (solution );

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
            printf("Нет решений\n");
            break;
        case ONE_ROOTS:
            printf("x = %lg", solution.x1);
            break;
        case TWO_ROOTS:
            printf("x1 = %lg\nx2 = %lg", solution.x1, solution.x2);
            break;
        case INF_ROOTS:
            printf("Любое число");
            break;
        default:
            printf("error %d", solution.nRoots);
            break;

    }
}

void InputCoeffs(Coeffs* coeffs)
{
    assert (coeffs);

    while (true){
        printf("Введите коффиценты:\n");

        if (scanf("%lg %lg %lg", &coeffs->a, &coeffs->b, &coeffs->c) != 3)
        {
            while (getchar() != '\n') {};
            printf("Неверные коэффиценты\n");
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
    if (!isfinite(coeffs.a) || !isfinite(coeffs.b) || !isfinite(coeffs.c))
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
        return GREATER_THAN_ZERO;
    }
    // (compare < -EPS)

    return LOWER_THAN_ZERO;
}

void LineSolution (Coeffs coeffs, Roots* solution)
{
    assert (solution);

        if (CompareOnZero(coeffs.b) == 0)
        {
            if (CompareOnZero(coeffs.c) == 0)
            {
                  solution->nRoots = INF_ROOTS;
            }
            else
            {
                solution->nRoots = NO_ROOTS;
                solution->x1 = NAN;
                solution->x2 = NAN;
            }
        }
        else
        {
            solution->x1 = -coeffs.c/coeffs.b;
            solution->x2 = NAN;
            solution->nRoots = ONE_ROOTS;
        }
}

void SquareSolution (Coeffs coeffs, Roots* solution)
{
    double d = coeffs.b * coeffs.b - 4 * coeffs.a * coeffs. c;

    if (CompareOnZero(d) == GREATER_THAN_ZERO)
    {
        solution->x1 = (-(coeffs.b) - sqrt(d))/(2*coeffs.a);
        solution->x2 = (-(coeffs.b) + sqrt(d))/(2*coeffs.a);
        solution->nRoots = TWO_ROOTS;
    }
    else if (CompareOnZero(d) == EQUAL_TO_ZERO)
    {
        solution->x1 = (-coeffs.b)/(2*coeffs.a);
        solution->x2 = NAN;
        solution->nRoots = ONE_ROOTS;
    }
    else if (CompareOnZero(d) == LOWER_THAN_ZERO)
    {
        solution->nRoots = NO_ROOTS;
        solution->x1 = NAN;
        solution->x2 = NAN;
    }
}

void Test (int TestNumber, Roots* solution, ExpectedSol* expected )
{
    SolveSquare (expected->coeffs, solution);
    double delta_x1 = 0, delta_x2 = 0;

    if (NAN_OR_INF(solution->x1) == 0)
    {
        if(NAN_OR_INF(expected->x1_expected) == 0)
        {
            delta_x1 = 0;
        }
    }
    else
    {
        delta_x1 = fabs(solution->x1 - expected->x1_expected);
    }

    if (NAN_OR_INF(solution->x2) == 0)
    {
        if(NAN_OR_INF(expected->x2_expected) == 0)
        {
            delta_x2 = 0;
        }
    }
    else
    {
        delta_x2 = fabs(solution->x2 - expected->x2_expected);
    }
      if ((*solution).nRoots != (*expected).nRoots_expected || CompareOnZero(delta_x1) != EQUAL_TO_ZERO || CompareOnZero(delta_x2) != EQUAL_TO_ZERO)
    {
        printf("\nError: Test %d\n  a = %lg b = %lg c = %lg\n  x1 = %lg x2 = %lg nRoots = %d\n"
               "Expected:\n  x1 = %lg x2 = %lg nRoots = %d\n",
               TestNumber + 1, expected->coeffs.a, expected->coeffs.b, expected->coeffs.c, (*solution).x1, (*solution).x2, (*solution).nRoots,
               (*expected).x1_expected, (*expected).x2_expected, (*expected).nRoots_expected);
    }
    else
    {
        printf ("Test %d Completed Succesfull\n",TestNumber + 1);
    }
}

void AllTest ()
{
    const int AmountOfTest = 11;
    Roots solution = {};
    ExpectedSol expected [AmountOfTest] = {{{0, 0, 0}, NAN, NAN, INF_ROOTS},
                                           {{0, 0, 1}, NAN, NAN, 0},
                                           {{0, 1, 0}, 0, NAN, 1},
                                           {{1, 0, 0}, 0, NAN, 1},
                                           {{0, 1, 1}, -1, NAN, 1},
                                           {{1, 0, 1}, NAN, NAN, 0},
                                           {{1, 1, 0}, -1, 0, 2},
                                           {{1, 1, -12}, -4, 3, 2},
                                           {{1, 1, 0.25}, -0.5, NAN, 1},
                                           {{4, -3, 2}, NAN, NAN, 0},
                                           {{2, 6, -3}, -3.43649, 0.436492,2}};

    for (int TestNumber = 0; TestNumber < AmountOfTest; TestNumber++)
    {
        printf("Starts test %d\n", TestNumber + 1);
        Test (TestNumber, &solution, expected + TestNumber);

    }
}

bool NAN_OR_INF (double check)
{
    if (!isfinite(check))
    {
        return 0;    // NAN or INF
    }
    else
    {
        return 1;
    }
}
