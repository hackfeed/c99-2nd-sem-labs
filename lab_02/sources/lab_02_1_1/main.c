#include <stdio.h>

#define OK 0
#define IN_ERR 1
#define LOGIC_ERR 2

int div_num(int a, int d)
{
    int div_part = 0;
    while (a >= d)
    {
        a -= d;
        div_part += 1;
    }

    return div_part;
}

int mod_num(int a, int d)
{
    int div_part = 0;
    while (a >= d)
    {
        a -= d;
        div_part += 1;
    }

    return a;
}

int main()
{
    int a, d, rc;

    rc = scanf("%d%d", &a, &d);
    if (rc == 2)
    {
        if (a > 0 && d > 0)
        {
            printf("%d %d", div_num(a, d), mod_num(a, d));

            return OK;
        }
        else
        {
            printf("Logic error");

            return LOGIC_ERR;
        }
    }
    else
    {
        printf("Input error");

        return IN_ERR;
    }
}