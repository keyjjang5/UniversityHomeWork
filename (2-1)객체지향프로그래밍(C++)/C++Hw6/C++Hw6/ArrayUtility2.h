#pragma once

class ArrayUtility2
{

public:
	static int* concat(int s1[], int s2[], int size);
	static int* remove(int s1[], int s2[], int size, int& retSize);
};

int* ArrayUtility2::concat(int s1[], int s2[], int size)
{
	int* concatP = new int[size];
	int k = 0;
	for (int i = 0; i < sizeof(s1)+1; i++)
	{
		concatP[k] = s1[i];
		k++;
	}
	for (int i = 0; i < sizeof(s2)+1; i++)
	{
		concatP[k] = s2[i];
		k++;
	}

	return concatP;
}

int* ArrayUtility2::remove(int s1[], int s2[], int size, int& retSize)
{
	for (int i = 0; i < size; i++)
	{
		if (s1[i] == NULL && s2[i] == NULL)
			break;
		for (int j = 0; j < size; j++)
		{
			if (s2[j] == NULL)
				break;
			if (s1[i] == s2[j])
			{
				s1[i] = NULL;
				break;
			}
		}
	}
	int count = 0;
	int test[100];
	for (int i = 0; i < size; i++)
		test[i] = s1[i];

	for (int i = 0; i < sizeof(s1); i++)
	{
		if (s1[i] == NULL)
		{
			int limit = 0;
			for (int j = i; j < sizeof(s1); j++)
			{
				if (s1[j] == NULL)
				{
					limit++;
					if (limit > sizeof(s1) - j - 1)
					{
						i++;
						limit = 0;
						break;
					}
				}
				int temp = s1[j];
				s1[j] = s1[j + 1];
				s1[j + 1] = temp;
			}
			i--;
			continue;
		}
		
		count++;
	}

	if (count == 0)
		retSize = NULL;
	else 
		retSize = count;
	int* removeP = new int[count];
	for (int i = 0; i < count; i++)
	{
		removeP[i] = s1[i];
	}

	return removeP;
}