#include <stdio.h>

#define OK 0
#define SIZE_INPUT_ERR -1
#define CLEAR_INPUT_ERR -2
#define ELEMENT_INPUT_ERR -3
#define ARG_COUNT_ERR -4
#define INPUT_ERR -5

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

int reverter(int n)
{
    int current_dig, reverted_int = 0;

    while (n > 0)
    {
        current_dig = n % 10;
        reverted_int = reverted_int * 10 + current_dig;
        n /= 10;
    }

    return reverted_int;
}

void form_reverted_array(int *const a, int *n)
{
    for (int i = 0; i < *n; ++i)
    {
        if (a[i] > 0)
        {
            (*n)++;
            for (int j = *n - 1; j > i + 1; --j)
                a[j] = a[j - 1];
            a[i + 1] = reverter(a[i]);
            i++;
        }
    }

    print_array(a, *n);
}

int main()
{
    int a[2 * N] = { 0 }, n = 0;

    if (read_array(a, &n) != OK)
        return INPUT_ERR;
    else
    {
        form_reverted_array(a, &n);

        return OK;
    }
}
