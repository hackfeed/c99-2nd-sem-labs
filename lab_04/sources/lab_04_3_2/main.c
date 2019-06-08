#include <stdio.h>
#include <math.h>

#define OK 0
#define SIZE_INPUT_ERR -1
#define CLEAR_INPUT_ERR -2
#define ELEMENT_INPUT_ERR -3
#define ARG_COUNT_ERR -4
#define LOGIC_ERR -5
#define INPUT_ERR -6

#define IS_ARMSTRONG 1
#define IS_NOT_ARMSTRONG 0

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

void print_array(const int *const a, const int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]);
}

int is_armstrong_digit(int n)
{
    int current_dig, digits_sum = 0, digits_count = 0;
    int m = n;
    int k = n;

    while (m > 0)
    {
        digits_count++;
        m /= 10;
    }

    while (n > 0)
    {
        current_dig = n % 10;
        digits_sum += pow(current_dig, digits_count);
        n /= 10;
    }

    if (digits_sum == k)
        return IS_ARMSTRONG;
    else
        return IS_NOT_ARMSTRONG;
}

int form_armstrong_array(const int *const a, int *b, const int n)
{
    int m = 0;

    for (int i = 0; i < n; ++i)
    {
        if (a[i] > 0 && is_armstrong_digit(a[i]))
        {
            b[m] = a[i];
            m++;
        }
    }

    if (m == 0)
    {
        printf("No Armstrong digits in array");

        return LOGIC_ERR;
    }
    else
    {
        if (m == n)
        {
            printf("All digits are Armstrong digits");

            return LOGIC_ERR;
        }
        else
        {
            print_array(b, m);

            return OK;
        }
    }
}

int main()
{
    int a[N] = { 0 }, b[N] = { 0 }, n = 0;

    if (read_array(a, &n) != OK)
        return INPUT_ERR;
    else
    {
        if (form_armstrong_array(a, b, n) != OK)
            return LOGIC_ERR;
        else
            return OK;
    }
}
