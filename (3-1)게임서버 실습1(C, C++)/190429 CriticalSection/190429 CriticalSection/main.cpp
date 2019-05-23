#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int sum = 0;
int input[10];
CRITICAL_SECTION cs;

DWORD WINAPI MyThread1(LPVOID arg)
{
	for (int i = 0; i < 3; i++)
	{
		cin >> input[i];
		EnterCriticalSection(&cs);
		sum += input[i];
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD WINAPI MyThread2(LPVOID arg)
{
	for (int i = 3; i < 6; i++)
	{
		cin >> input[i];
		EnterCriticalSection(&cs);
		sum += input[i];
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD WINAPI MyThread3(LPVOID arg)
{
	for (int i = 6; i < 10; i++)
	{
		cin >> input[i];
		EnterCriticalSection(&cs);
		sum += input[i];
		LeaveCriticalSection(&cs);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	InitializeCriticalSection(&cs);

	cout << "10 개의 숫자를 입력해주십시오." << endl;

	HANDLE hThread[3];
	hThread[0] = CreateThread(NULL, 0, MyThread1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, MyThread2, NULL, 0, NULL);
	hThread[2] = CreateThread(NULL, 0, MyThread3, NULL, 0, NULL);

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	DeleteCriticalSection(&cs);

	cout << "\n입력값 : ";

	for (int i = 0; i < 10; i++)
	{
		cout << input[i] << ", " ;
	}
	cout << endl;

	printf("\n합 = %d\n", sum);

	return 0;
}
