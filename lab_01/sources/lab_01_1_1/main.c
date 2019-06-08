#include <stdio.h>
#include <math.h>

#define PI 3.14159265
#define PI_DEG 180

#define OK 0

int main()
{
    double a, b, alpha;
    double square;
    double h, p;

    printf("Input a, b, alpha: ");
    scanf("%lf%lf%lf", &a, &b, &alpha);

    p = fabs(a - b) / 2;
    h = p * tan(alpha * PI / PI_DEG);
    square = (a + b) / 2 * h;

    printf("Total square of shape: S = %-12.5f", square);

    return OK;
}