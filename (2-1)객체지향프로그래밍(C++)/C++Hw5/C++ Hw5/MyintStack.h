#pragma once


class MyIntStack {
	int p[10]; // �ִ� 10���� ���� ���� 
	int tos; // ������ ����⸦ ����Ű�� �ε��� 

public:
	MyIntStack();
	bool push(int n); // ���� n Ǫ��, �� �� ������ false, �ƴϸ� true ���� 
	bool pop(int& n); // ���Ͽ� n�� ����, ������ ��� ������ false, �ƴϸ� true ���� 
};

MyIntStack::MyIntStack() :tos(0)
{

}

bool MyIntStack::push(int n)
{
	if (tos!=10)
	{
		p[tos] = n;
		tos++;
		return true;
	}
	else
		return false;
}

bool MyIntStack::pop(int&n)
{
	if (tos != 0)
	{
		tos--;
		n = p[tos];
		p[tos] = NULL;
		
		return true;
	}
	else
		return false;
}