#include <stdio.h>

#define OK 0
#define SIZE_INPUT_ERR -1
#define CLEAR_INPUT_ERR -2
#define ELEMENT_INPUT_ERR -3
#define ARG_COUNT_ERR -4
#define INPUT_ERR -5

#define N 10

int read_matrix(int a[N][N + 1], int *const n, int *const m)
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

void swap(int *const a, int *const b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void print_matrix(int a[N][N + 1], const int n, const int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            printf("%d ", a[i][j]);
    }
}

void matrix_sort(int a[N][N + 1], const int n, const int m)
{
    int row_min;

    for (int i = 0; i < n; ++i)
    {
        row_min = a[i][0];

        for (int j = 1; j < m; ++j)
        {
            if (a[i][j] < row_min)
                row_min = a[i][j];
        }

        a[i][m] = row_min;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (a[i][m] > a[j][m])
            {
                for (int k = 0; k <= m; ++k)
                    swap(&a[i][k], &a[j][k]);
            }
        }
    }
}

int main()
{
    int a[N][N + 1], n, m;

    if (read_matrix(a, &n, &m) != OK)
        return INPUT_ERR;
    else
    {
        matrix_sort(a, n, m);
        print_matrix(a, n, m);

        return OK;
    }
}
