#include <stdio.h>

#define OK 0
#define SIZE_INPUT_ERR -1
#define CLEAR_INPUT_ERR -2
#define ELEMENT_INPUT_ERR -3
#define ARG_COUNT_ERR -4
#define INPUT_ERR -5

#define ORDERED 1
#define NOT_ORDERED 0

#define N 10

int read_matrix(int a[N][N], int *const n, int *const m)
{
    int rc, matrix_el;
    int arg_count = 0;

    rc = scanf("%d%d", n, m);

    if (rc == 2)
    {
        if (*n > N || *n < 1 || *m > N || *m < 1)
        {
            printf("Matrix size input error");

            return SIZE_INPUT_ERR;
        }
        else
        {
            for (int i = 0; i < *n; ++i)
            {
                for (int j = 0; j < *m; j++)
                {
                    rc = scanf("%d", &matrix_el);
                    if (rc == 1)
                    {
                        a[i][j] = matrix_el;
                        arg_count++;
                    }
                    else
                    {
                        printf("Array element input error");

                        return ELEMENT_INPUT_ERR;
                    }
                }
            }

            if (arg_count != (*n) * (*m))
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
    {
        printf("%d ", a[i]);
    }
}

int array_from_matrix(int a[N][N], int *const b, const int n, const int m)
{
    int is_ordered_up, is_ordered_down;

    if (m == 1)
    {
        for (int i = 0; i < n; ++i)
            b[i] = NOT_ORDERED;
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            is_ordered_up = 1;
            is_ordered_down = 1;

            for (int j = 0; j < m - 1; ++j)
                if (a[i][j] <= a[i][j + 1])
                    is_ordered_up++;

            for (int j = 0; j < m - 1; ++j)
                if (a[i][j] >= a[i][j + 1])
                    is_ordered_down++;

            if (is_ordered_up == m || is_ordered_down == m)
                b[i] = ORDERED;
            else
                b[i] = NOT_ORDERED;
        }
    }

    return OK;
}

int main()
{
    int a[N][N], n, m;
    int b[N];

    if (read_matrix(a, &n, &m) != OK)
        return INPUT_ERR;
    else
    {
        array_from_matrix(a, b, n, m);

        print_array(b, n);

        return OK;
    }
}