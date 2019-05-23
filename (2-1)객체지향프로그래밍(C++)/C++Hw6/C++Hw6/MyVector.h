#pragma once

class MyVector {
	int* mem;
	int size;
public:
	MyVector(int n, int val);
	~MyVector();
	void getMember();
};

MyVector::MyVector(int n = 100, int val = 0)
{
	mem = new int[n];
	size = n;
	for (int i = 0; i < size; i++)
		mem[i] = val;
}

MyVector::~MyVector()
{
	delete[] mem;
}

void MyVector::getMember()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << mem[i] << std::endl;
	}
	std::cout << size << std::endl;
}