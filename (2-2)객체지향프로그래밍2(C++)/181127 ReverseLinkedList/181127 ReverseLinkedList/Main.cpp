#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SinglyLinkedList.h"
#include "ReverseLinkedList.h"
#include "IntStack.h"
#include "Sort.h"


int main()
{
	/*List list;
	list.head = NULL;
	add(&list, 1);
	add(&list, 2);
	add(&list, 9);
	add(&list, 11);


	reverseList(&list, list.head);

	printForward(list.head);

	printf("\n\n");

	printReverse(list.head);*/

	int arr[10]{ 2,4,5,6,1,7,10,3,0,9 };

	//bubbleSort(arr, 10);
	
	//selectionSort(arr, 10);

	//insertionSort(arr, 10);

	quickSort(arr, 0, 9);

	for (int i = 0; i < 10; i++)
		printf("arr[%d] : %d\n", i, arr[i]);

	return 0;
}