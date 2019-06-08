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

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void gnome_sort(int *const a, const int n)
{
    for (int i = 0; i + 1 < n; ++i)
    {
        if (a[i] > a[i + 1])
        {
            swap(&a[i], &a[i + 1]);
            if (i != 0)
                i -= 2;
        }
    }
}

int main()
{
    int a[2 * N] = { 0 }, n = 0;

    if (read_array(a, &n) != OK)
        return INPUT_ERR;
    else
    {
        gnome_sort(a, n);

        print_array(a, n);

        return OK;
    }
}
