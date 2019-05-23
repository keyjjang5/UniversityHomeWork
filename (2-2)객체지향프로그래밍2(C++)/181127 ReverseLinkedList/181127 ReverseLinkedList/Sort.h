#pragma once


void swap(int arr[], int v1, int v2)
{
	int temp = arr[v1];
	arr[v1] = arr[v2];
	arr[v2] = temp;
}

void bubbleSort(int arr[], int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1 - i; j++)
			if (arr[j] > arr[j + 1])
			{
				swap(arr, j, j + 1);
			}
}

void selectionSort(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < size; j++)
			if (arr[minIndex] > arr[j])
				minIndex = j;
		swap(arr, i, minIndex);
	}
}

void insertionSort(int arr[], int size)
{
	for (int i = 1; i < size; i++)
		for (int j = i; j > 0; j--)
			if (arr[j] < arr[j - 1])
				swap(arr, j, j - 1);
}

int partition(int arr[], int start, int end)
{
	int pivot = arr[end];
	int index = start;
	for (int i = index; i < end; i++)
		if (arr[i] < pivot)
		{
			swap(arr, i, index);
			index++;
		}
	swap(arr, index, end);

	return index;
}

void quickSort(int arr[], int start, int end)
{
	if (start >= end)
		return;
	int pIndex = partition(arr, start, end);

	quickSort(arr, start, pIndex - 1);
	quickSort(arr, pIndex + 1, end);
}