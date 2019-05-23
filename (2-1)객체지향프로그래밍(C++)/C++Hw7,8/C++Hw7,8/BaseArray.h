#pragma once

class BaseArray {
private:
	int capacity; // 배열의 크기 
	int *mem; // 정수 배열을 만들기 위한 메모리의 포인터 
public:
	BaseArray(int capacity = 100) : capacity(capacity), mem(new int[capacity]) {}
	~BaseArray() { delete[] mem; }

	void put(int index, int val) 
	{ mem[index] = val; }
	int get(int index) 
	{ return mem[index]; }
	int getCapacity() 
	{ return capacity; }
};

class MyQueue : public BaseArray
{
	int index;
public:
	MyQueue(int capacity);
	void enqueue(int n);
	int capacity();
	int length();
	int dequeue();
};

MyQueue::MyQueue(int capacity) : BaseArray(capacity), index(0)
{

}

void MyQueue::enqueue(int n)
{
	put(index, n);
	index++;
}

int MyQueue::capacity()
{
	return getCapacity();
}

int MyQueue::length()
{
	return index;
}

int MyQueue::dequeue()
{
	int save = get(0);
	put(0, 0);
	for (int i = 0; i < index-1; i++)
	{
		int temp = get(i);
		put(i, get(i + 1));
		put(i + 1, temp);
	}
	index--;

	return save;
}