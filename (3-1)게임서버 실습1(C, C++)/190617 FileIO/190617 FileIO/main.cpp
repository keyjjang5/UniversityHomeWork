#include <stdio.h>

int main()
{
	FILE *fp;

	int index;
	int data;

	fp = fopen("Log.txt", "a");

	fprintf(fp, "�α� ������..\n");

	fclose(fp);

	return 0;

}