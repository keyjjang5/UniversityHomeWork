#include <stdio.h>

int main()
{
	FILE *fp;

	int index;
	int data;

	fp = fopen("Log.txt", "a");

	fprintf(fp, "로그 제작중..\n");

	fclose(fp);

	return 0;

}