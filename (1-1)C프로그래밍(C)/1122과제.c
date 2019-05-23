#include <stdio.h>
#include <string.h>

char reverse_1(char b[]);
char reverse_2(char *p);
char reverse_3(char *p);

int main()
{
	char A[] = "Hello World";
	char *q;

	reverse_1(A);
	reverse_2(A);
	reverse_3(A);
	printf("%s", A);
	

	return 0;
}

char reverse_1(char b[])
{
	for (int i = strlen(b); i >= 0; i--)
	{
		printf("%c", b[i]);
	}
	printf("\n");
}

char reverse_2(char *p)
{
	for (int i = strlen(p); i >= 0; i--)
	{
		printf("%c", p[i]);
	}
	printf("\n");
}

char reverse_3(char *p)
{
	char swap;

	for (int i = 0; i < strlen(p); i++)
	{
		if (i == strlen(p) / 2 +1)
		{
			break;
		}
		else
		{
			swap = p[i];
			p[i] = p[strlen(p)-i-1];
			p[strlen(p)-i-1] = swap;
		}

	}
}