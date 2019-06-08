#include <stdio.h>
#include <math.h>

#define OK 0
#define SIZE_INPUT_ERR -1
#define CLEAR_INPUT_ERR -2
#define ELEMENT_INPUT_ERR -3
#define ARG_COUNT_ERR -4
#define LOGIC_ERR -5
#define INPUT_ERR -6

#define N 10

int read_array(int *const a, int *n)
{
    int rc, array_el;
    int arg_count = 0;

    rc = scanf("%d", n);

    if (rc == 1)
    {
        if (*n > N || *n < 1)
        {
            printf("Array size input error");

            return SIZE_INPUT_ERR;
        }
        else
        {
            for (int i = 0; i < *n; ++i)
            {
                rc = scanf("%d", &array_el);
                if (rc == 1)
                {
                    a[i] = array_el;
                    arg_count++;
                }
                else
                {
                    printf("Array element input error");

                    return ELEMENT_INPUT_ERR;
                }
            }

            if (arg_count != *n)
            {
                printf("Arguments' count error");

                return ARG_COUNT_ERR;
            }
            else
                return OK;
        }
    }
    else
    {
        printf("Input clearance error");

        return CLEAR_INPUT_ERR;
    }
}

float average_geo_finder(const int *const a, const int n)
{
    float average = 0;
    int positive_counter = 0, positive_mul = 1;

    for (int i = 0; i < n; ++i)
    {
        if (a[i] > 0)
        {
            positive_counter++;
            positive_mul *= a[i];
        }
    }

    if (positive_counter == 0)
    {
        printf("No positive digits");

        average = LOGIC_ERR;
    }
    else
        average = powf(positive_mul, 1.0 / positive_counter);

    return average;
}

int main()
{
    int a[N] = { 0 }, n = 0;

    if (read_array(a, &n) != OK)
        return INPUT_ERR;
    else
    {
        const float average = average_geo_finder(a, n);

        if (average == LOGIC_ERR)
            return LOGIC_ERR;
        else
        {
            printf("%.5f", average);

            return OK;
        }
    }
}
