/* РК1 Кононенко Сергей 1 вариант */

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define INPUT_ERR -1

int reverser(int a)
{
	int reversed_a, absolute_a;
	
	absolute_a = abs(a);
	reversed_a = 0;
	
	while(absolute_a)
	{
		reversed_a = reversed_a * 10 + absolute_a % 10;
		absolute_a /= 10;
	}
	
	return reversed_a;
}

int main()
{
	int n, reversed_n, rc;
	
	rc = scanf("%d", &n);
	
	if (rc == 1)
	{
		reversed_n = reverser(n);
	
		printf("%d", reversed_n);
	
		return OK;
	}
	else
		return INPUT_ERR;
}