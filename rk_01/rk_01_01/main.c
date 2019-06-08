/* РК1 Кононенко Сергей 3 вариант */

#include <stdio.h>

#define OK 0
#define INPUT_ERR -1

#define N 100

int read_array(int *a, int *n)
{
	int rc, array_el;
	int arg_count = 0;
	
	rc = scanf("%d", n);
	
	if (rc == 1)
	{
		if (*n < 1 || *n > N)
			return INPUT_ERR;
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
					return INPUT_ERR;
			}
		}
		if (arg_count != *n)
			return INPUT_ERR;
		else
			return OK;
	}
	else
		return INPUT_ERR;
}

void create_array(int *a, int *b, int n, int *m)
{
	if (!(n % 2))
	{
		*m = n / 2;
		for (int i = 0; i < *m; ++i)
			b[i] = a[i] * a[n - i - 1];
	}
	else
	{
		*m = n / 2 + 1;
		for (int i = 0; i < *m; ++i)
			b[i] = a[i] * a[n - i - 1];
		b[*m - 1] = a[*m - 1];
	}
}

void print_array(int *a, int n)
{
	for (int i = 0; i < n; ++i)
		printf("%d ", a[i]);
}

int main()
{
	int a[N], b[(N / 2) + 1], n, m;
	
	if (read_array(a, &n) == INPUT_ERR)
		return INPUT_ERR;
	else
	{
		create_array(a, b, n, &m);
		print_array(b, m);
		
		return OK;
	}
}