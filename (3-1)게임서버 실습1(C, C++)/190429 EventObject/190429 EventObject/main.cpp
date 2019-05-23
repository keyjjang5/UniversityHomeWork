#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

HANDLE hWriteEvent1;
HANDLE hWriteEvent2;

int sum = 0;
int input[10];

DWORD WINAPI WriteThread1(LPVOID arg)
{
	DWORD retval;

	for (int i = 0; i < 3; i++)
	{
		cin >> input[i];
		sum += input[i];
	}

	SetEvent(hWriteEvent1);

	return 0;
}

DWORD WINAPI WriteThread2(LPVOID arg)
{
	DWORD retval;

	while (1)
	{
		retval = WaitForSingleObject(hWriteEvent1, INFINITE);
		if (retval == WAIT_OBJECT_0) break;
	}

	for (int i = 3; i < 6; i++)
	{
		cin >> input[i];
		sum += input[i];
	}

	SetEvent(hWriteEvent2);

	return 0;
}

DWORD WINAPI WriteThread3(LPVOID arg)
{
	DWORD retval;

	while (1)
	{
		retval = WaitForSingleObject(hWriteEvent2, INFINITE);
		if (retval == WAIT_OBJECT_0) break;
	}

	for (int i = 6; i < 10; i++)
	{
		cin >> input[i];
		sum += input[i];
	}

	return 0;
}

int main(int argc, char *argv[])
{
	hWriteEvent1 = CreateEvent(NULL, FALSE, FALSE, NULL); // 자동 비신호
	if (hWriteEvent1 == NULL) return 1;
	hWriteEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL); // 자동 비신호
	if (hWriteEvent1 == NULL) return 1;

	cout << "10 개의 숫자를 입력해주십시오." << endl;

	HANDLE hThread[3];
	hThread[0] = CreateThread(NULL, 0, WriteThread1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, WriteThread2, NULL, 0, NULL);
	hThread[2] = CreateThread(NULL, 0, WriteThread3, NULL, 0, NULL);

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	CloseHandle(hWriteEvent1);
	CloseHandle(hWriteEvent2);

	cout << "\n입력값 : ";

	for (int i = 0; i < 10; i++)
	{
		cout << input[i] << ", ";
	}

	cout << endl;

	printf("\n합 = %d\n", sum);

	system("PAUSE");

	return 0;
}