#include <stdio.h>
#include <math.h>

#define OK 0
#define IN_ERR 1
#define LOGIC_ERR 2

float series_estimate(float x, float eps)
{
    float series_part = x;
    float series_sum = x;
    int n = 3;

    while (fabsf(series_part) > eps)
    {
        series_part *= -1 * x * x / (n - 1) / n;
        series_sum += series_part;
        n += 2;
    }

    return series_sum;
}

int main()
{
    int rc;
    float x, eps;
    float s_x, f_x, abs_err, rel_err;

    rc = scanf("%f%f", &x, &eps);

    if (rc == 2)
    {
        if (eps > 1 || eps <= 0)
        {
            printf("Epsilon error");

            return LOGIC_ERR;
        }
        else
        {
            s_x = series_estimate(x, eps);
            f_x = sinf(x);
            abs_err = fabsf(f_x - s_x);
            rel_err = fabsf((f_x - s_x) / f_x);

            printf("%f %f %f %f", s_x, f_x, abs_err, rel_err);

            return OK;
        }
    }
    else
    {
        printf("Input error");

        return IN_ERR;
    }
}