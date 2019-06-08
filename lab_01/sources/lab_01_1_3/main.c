#include <stdio.h>

#define OK 0

int main()
{
    double v1, v2, t1, t2;
    double v0, t0;

    printf("Input V1, t1, V2, t2: ");
    scanf("%lf%lf%lf%lf", &v1, &t1, &v2, &t2);

    v0 = v1 + v2;
    t0 = (v1 * t1 + v2 * t2) / (v1 + v2);

    printf("Total value: %12.5f litres; "
        "total temperature: %12.5f dg. C", v0, t0);

    return 0;
}
