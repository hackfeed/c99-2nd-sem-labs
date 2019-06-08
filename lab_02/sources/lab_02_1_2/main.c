#include <stdio.h>
#include <math.h>

#define OK 0
#define IN_ERR 1
#define LOGIC_ERR 2

float square_estimate(float a, float b, float c)
{
    float half_p = (a + b + c) / 2;
    float square = sqrtf(half_p * (half_p - a) * (half_p - b) * (half_p - c));

    return square;
}

float own_hypotf(float a, float b)
{
    float res;

    res = sqrtf(a * a + b * b);

    return res;
}

int main()
{
    int rc;
    float x1, y1, x2, y2, x3, y3;
    float a, b, c;

    rc = scanf("%f%f%f%f%f%f", &x1, &y1, &x2, &y2, &x3, &y3);

    if (rc == 6)
    {
        a = own_hypotf((x1 - x2), (y1 - y2));
        b = own_hypotf((x1 - x3), (y1 - y3));
        c = own_hypotf((x2 - x3), (y2 - y3));

        if (!square_estimate(a, b, c))
        {
            printf("Triangle is not exist");

            return LOGIC_ERR;
        }
        else
        {
            printf("%f", square_estimate(a, b, c));

            return OK;
        }
    }
    else
    {
        printf("Input error");

        return IN_ERR;
    }
}